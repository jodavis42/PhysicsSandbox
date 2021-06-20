#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Physics2dCore/Resolution/Constraints/ContactConstraint2d.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------CachedContactConstraint2d
class CachedContactConstraint2d : public Physics2dCore::ContactConstraint2d
{
public:
  Zero::Link<CachedContactConstraint2d> mLink;
};

//-------------------------------------------------------------------Contact2dCache
class Contact2dCache
{
public:
  using HashColliderPair = Zero::Pair<const Physics2dCore::Collider2d*, const Physics2dCore::Collider2d*>;
  using CachedContactConstraint2dList = Zero::InList<CachedContactConstraint2d, &CachedContactConstraint2d::mLink>;
  using ContactRange = CachedContactConstraint2dList::range;

  ~Contact2dCache();

  void BeginFrame();
  void Add(Physics2dCore::ContactManifold2d& contactManifold);
  void EndFrame();

  ContactRange GetContacts();

private:
  CachedContactConstraint2d* Find(Physics2dCore::ContactManifold2d& contactManifold);
  CachedContactConstraint2d* Create(Physics2dCore::ContactManifold2d& contactManifold);
  void Update(Physics2dCore::ContactManifold2d& contactManifold, CachedContactConstraint2d& cachedContactConstraint);
  HashColliderPair GetPair(const Physics2dCore::Collider2dPair& colliderPair);

  CachedContactConstraint2dList mCachedContacts;
  CachedContactConstraint2dList mLastFrameContacts;
  Zero::HashMap<HashColliderPair, CachedContactConstraint2d*> mLookupMap;
};

}//namespace Physics2dTCS
