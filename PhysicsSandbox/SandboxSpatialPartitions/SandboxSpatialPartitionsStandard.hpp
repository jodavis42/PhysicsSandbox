#pragma once

#include "Common/CommonStandard.hpp"
#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

class Aabb2d;
class Circle2d;
class Ray2d;

}//namespace SandboxGeometry


namespace SandboxSpatialPartition2d
{

using Math::Vector2;
using Math::Vector3;
using Math::Vector4;
using Math::Matrix2;
using Math::Matrix3;
using Math::Matrix4;
using Math::Quaternion;

using Aabb2d = SandboxGeometry::Aabb2d;
using Circle2d = SandboxGeometry::Circle2d;
using Ray2d = SandboxGeometry::Ray2d;

}//namespace SandboxSpatialPartition2d

namespace SandboxBroadphase2d
{

using Math::Vector2;
using Math::Vector3;
using Math::Vector4;
using Math::Matrix2;
using Math::Matrix3;
using Math::Matrix4;
using Math::Quaternion;

using Aabb2d = SandboxGeometry::Aabb2d;
using Circle2d = SandboxGeometry::Circle2d;
using Ray2d = SandboxGeometry::Ray2d;

}//namespace SandboxBroadphase2d
