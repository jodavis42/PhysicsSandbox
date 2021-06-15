#include "Precompiled.hpp"

#include "NSquaredAabbBroadphase2d.hpp"

#include "SpatialPartitions2d/NSquared2d.hpp"

namespace SandboxBroadphase2d
{

//-------------------------------------------------------------------NSquaredAabbBroadphase2d
NSquaredAabbBroadphase2d::NSquaredAabbBroadphase2d()
{

}

BroadphaseKey NSquaredAabbBroadphase2d::Insert(const BroadphaseData& data)
{
  return mSpatialPartition.Insert(data);
}

void NSquaredAabbBroadphase2d::Update(const BroadphaseData& data, BroadphaseKey& key)
{
  mSpatialPartition.Update(data, key);
}

void NSquaredAabbBroadphase2d::Remove(BroadphaseKey& key)
{
  mSpatialPartition.Remove(key);
}

void NSquaredAabbBroadphase2d::Raycast(const Ray2d& ray, CastResults& results)
{
  auto range = mSpatialPartition.Raycast(ray);
  results.AddRange(range);
}

void NSquaredAabbBroadphase2d::SelfQuery(SelfQueryResults& results)
{
  auto range = mSpatialPartition.SelfQuery();
  results.AddRange(range);
}

} //namespace SandboxBroadphase2d
