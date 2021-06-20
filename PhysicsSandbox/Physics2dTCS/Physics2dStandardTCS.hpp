#pragma once

#include "Common/CommonStandard.hpp"

#include "Physics2dCore/Detection/Broadphase/BroadphaseLayerType.hpp"

namespace SandboxGeometry
{

class Ray2d;
class RayResult2d;

}//SandboxBroadphase2d

namespace SandboxBroadphase2d
{

class IBroadphase2d;

}//SandboxBroadphase2d

namespace Physics2dCore
{

class RigidBody2d;
class Collider2d;
class PropertyChangedEvent;
class Collider2dPair;
class ContactManifold2d;
class IBroadphase2dManager;
class Collider2dRaycastResult;
class IConstraint2dSolver;
class SimpleConstraint2dSolver;

}//namespace Physics2dCore

namespace Physics2dTCS
{

using Math::Vector2;
using Math::Vector3;
using Math::Vector4;
using Math::Matrix2;
using Math::Matrix3;
using Math::Matrix4;
using Math::Quaternion;

using Ray2d = SandboxGeometry::Ray2d;
using RayResult2d = SandboxGeometry::RayResult2d;

using IBroadphase2d = SandboxBroadphase2d::IBroadphase2d;

using RigidBody2d = Physics2dCore::RigidBody2d;
using Collider2d = Physics2dCore::Collider2d;
using Collider2dRaycastResult = Physics2dCore::Collider2dRaycastResult;
using PropertyChangedEvent = Physics2dCore::PropertyChangedEvent;
using IBroadphase2dManager = Physics2dCore::IBroadphase2dManager;
using IConstraint2dSolver = Physics2dCore::IConstraint2dSolver;
using SimpleConstraint2dSolver = Physics2dCore::SimpleConstraint2dSolver;
namespace BroadphaseLayerType = Physics2dCore::BroadphaseLayerType;

template <typename T>
using Array = Zero::Array<T>;

class PhysicsSpace2dTCS;
class RigidBody2dTCS;
class Collider2dTCS;

}//namespace Physics2dTCS
