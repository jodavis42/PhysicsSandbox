#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/IBroadphase2d.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/NSquared2d.hpp"

namespace SandboxBroadphase2d
{

//-------------------------------------------------------------------NSquaredBroadphase2d
class NSquaredBroadphase2d : public IBroadphase2d
{
public:
  NSquaredBroadphase2d();

  BroadphaseKey Insert(const BroadphaseData& data) override;
  void Update(const BroadphaseData& data, BroadphaseKey& key) override;
  void Remove(BroadphaseKey& key) override;

  void Raycast(const Ray2d& ray, CastResults& results) override;
  void SelfQuery(SelfQueryResults& results) override;

private:
  SandboxSpatialPartition2d::NSquared2d<ClientDataType> mSpatialPartition;
};

}//namespace SandboxBroadphase2d
