#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/CoreStructs.hpp"

namespace SandboxBroadphase2d
{

//-------------------------------------------------------------------IBroadphase2d
class IBroadphase2d
{
public:
  IBroadphase2d();
  virtual ~IBroadphase2d() {};

  virtual BroadphaseKey Insert(const BroadphaseData& data) abstract;
  virtual void Update(const BroadphaseData& data, BroadphaseKey& key) abstract;
  virtual void Remove(BroadphaseKey& key) abstract;

  virtual void Raycast(const Ray2d& ray, CastResults& results) abstract;
  virtual void SelfQuery(SelfQueryResults& results) abstract;
};

}//namespace SandboxBroadphase2d
