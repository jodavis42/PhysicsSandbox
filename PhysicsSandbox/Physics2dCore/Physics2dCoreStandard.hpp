#pragma once

#include "Common/CommonStandard.hpp"

namespace SandboxGeometry
{

class Ray2d;
class RayResult2d;
class Manifold2d;

}//SandboxGeometry2d

namespace Physics2dCore
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
class Physics2dMaterial;
class Collider2d;
class BoxCollider2d;
class CircleCollider2d;
class RigidBody2d;

}//namespace Physics2dCore
