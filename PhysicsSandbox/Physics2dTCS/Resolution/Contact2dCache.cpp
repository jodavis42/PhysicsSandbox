#include "Precompiled.hpp"

#include "Contact2dCache.hpp"

#include "Physics2dCore/Detection/ContactManifold2d.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/ContactConstraint2dManifold.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------Contact2dCache
Contact2dCache::~Contact2dCache()
{
  if(!mCachedContacts.Empty())
    mLastFrameContacts.Splice(mLastFrameContacts.End(), mCachedContacts);
  while(!mLastFrameContacts.Empty())
  {
    CachedContactConstraint2d* cachedContactConstraint = &mLastFrameContacts.Front();
    mLastFrameContacts.PopFront();
    delete cachedContactConstraint;
  }
}

void Contact2dCache::BeginFrame()
{
  // Put all old contacts into the last frame list. Anything left in here didn't persist
  mLastFrameContacts.Swap(mCachedContacts);
}

void Contact2dCache::Add(Physics2dCore::ContactManifold2d& contactManifold)
{
  CachedContactConstraint2d* cachedContact = Find(contactManifold);
  // If the contact didn't already exist then create a new one
  if(cachedContact == nullptr)
  {
    cachedContact = Create(contactManifold);
    auto&& pair = GetPair(contactManifold.mColliders);
    mLookupMap.Insert(pair, cachedContact);
  }
  // Otherwise update the old one
  else
  {
    CachedContactConstraint2dList::Unlink(cachedContact);
    Update(contactManifold, *cachedContact);
  }

  mCachedContacts.PushBack(cachedContact);
}

void Contact2dCache::EndFrame()
{
  // Delete any contacts that didn't persist this frame
  while(!mLastFrameContacts.Empty())
  {
    CachedContactConstraint2d* cachedContactConstraint = &mLastFrameContacts.Front();
    mLastFrameContacts.PopFront();

    auto&& pair = GetPair(cachedContactConstraint->mManifold.mColliders);
    mLookupMap.Erase(pair);
    delete cachedContactConstraint;
  }
}

Contact2dCache::ContactRange Contact2dCache::GetContacts()
{
  return mCachedContacts.All();
}

CachedContactConstraint2d* Contact2dCache::Find(Physics2dCore::ContactManifold2d& contactManifold)
{
  auto&& pair = GetPair(contactManifold.mColliders);
  return mLookupMap.FindValue(pair, nullptr);
}

CachedContactConstraint2d* Contact2dCache::Create(Physics2dCore::ContactManifold2d& contactManifold)
{
  CachedContactConstraint2d* cachedContactConstraint = new CachedContactConstraint2d();
  cachedContactConstraint->LoadManifold(contactManifold);
  return cachedContactConstraint;
}

void Contact2dCache::Update(Physics2dCore::ContactManifold2d& contactManifold, CachedContactConstraint2d& cachedContactConstraint)
{
  // This is slow and could be updated...
  HashSet<size_t> cachedPoints;

  // Find any point where the world position is very close to the old one and it has the same feature id
  auto&& FindPoint = [&cachedPoints](size_t featureId, SandboxGeometry::ManifoldPoint2d& point, CachedContactConstraint2d& cachedContactConstraint) -> Physics2dCore::ContactConstraint2dPoint*
  {
    for(size_t i = 0; i < cachedContactConstraint.mManifold.Size(); ++i)
    {
      if(cachedPoints.Contains(i))
        continue;

      auto&& cachedPoint = cachedContactConstraint.mManifold[i];
      if(cachedPoint.mFeatureId != featureId)
        continue;

      float distanceSq = Math::DistanceSq(point.mPoints[0], cachedPoint.mPoints[0]);
      if(distanceSq < 0.05f)
        return &cachedPoint;
    }
    return nullptr;
  };

  // Create the new manifold
  Physics2dCore::ContactConstraint2dManifold newPoints;
  newPoints.Load(contactManifold);
  for(size_t i = 0; i < newPoints.Size(); ++i)
  {
    auto&& newPoint = newPoints[i];
    // If we can find an old point that matched then cache the accumulated impulse
    Physics2dCore::ContactConstraint2dPoint* cachedContactPoint = FindPoint(newPoint.mFeatureId, newPoint, cachedContactConstraint);
    if(cachedContactPoint != nullptr)
      newPoint.mAccumulatedImpulse = cachedContactPoint->mAccumulatedImpulse;
  }
  // Load into the old constraint
  cachedContactConstraint.LoadManifold(newPoints);
}

Contact2dCache::HashColliderPair Contact2dCache::GetPair(const Physics2dCore::Collider2dPair& colliderPair)
{
  // Build a consistent ordering
  if(colliderPair[0] < colliderPair[1])
    return HashColliderPair(colliderPair[0], colliderPair[1]);
  return HashColliderPair(colliderPair[1], colliderPair[0]);
}

}//namespace Physics2dTCS
