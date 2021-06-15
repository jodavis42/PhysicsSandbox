#include "Precompiled.hpp"

#include "NSquaredBroadphase2d.hpp"

#include "SpatialPartitions2d/NSquared2d.hpp"

namespace SandboxBroadphase2d
{

//-------------------------------------------------------------------NSquaredBroadphase2d
NSquaredBroadphase2d::NSquaredBroadphase2d()
{

}

BroadphaseKey NSquaredBroadphase2d::Insert(const BroadphaseData& data)
{
  return mSpatialPartition.Insert(data);
}

void NSquaredBroadphase2d::Update(const BroadphaseData& data, BroadphaseKey& key)
{
  mSpatialPartition.Update(data, key);
}

void NSquaredBroadphase2d::Remove(BroadphaseKey& key)
{
  mSpatialPartition.Remove(key);
}

void NSquaredBroadphase2d::Raycast(const Ray2d& ray, CastResults& results)
{
  auto range = mSpatialPartition.Raycast(ray);
  results.AddRange(range);
}

void NSquaredBroadphase2d::SelfQuery(SelfQueryResults& results)
{
  auto range = mSpatialPartition.SelfQuery();
  results.AddRange(range);
}

} //namespace SandboxBroadphase2d
