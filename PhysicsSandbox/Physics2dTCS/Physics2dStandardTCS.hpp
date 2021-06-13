#pragma once

#include "Common/CommonStandard.hpp"

namespace SandboxGeometry
{

class Ray2d;
class RayResult2d;

}//SandboxBroadphase2d

namespace Physics2dCore
{

class RigidBody2d;
class Collider2d;
class PropertyChangedEvent;
class Collider2dPair;
class ContactManifold2d;

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

using RigidBody2d = Physics2dCore::RigidBody2d;
using Collider2d = Physics2dCore::Collider2d;
using PropertyChangedEvent = Physics2dCore::PropertyChangedEvent;
class PhysicsSpace2dTCS;
class RigidBody2dTCS;
class Collider2dTCS;

}//namespace Physics2dTCS