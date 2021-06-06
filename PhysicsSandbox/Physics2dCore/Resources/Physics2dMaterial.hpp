#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//---------------------------------------------------------- Physics2dMaterial
class Physics2dMaterial : public Zero::DataResource
{
public:
  ZilchDeclareType(Physics2dMaterial, TypeCopyMode::ReferenceType);

  Physics2dMaterial();

  //-------------------------------------------------------------------Resource Interface
  void Serialize(Zero::Serializer& stream) override;
  void ResourceModified() override;

  /// Creates a PhysicsMaterial for run-time modifications.
  static HandleOf<Physics2dMaterial> CreateRuntime();
  HandleOf<Zero::Resource> Clone() override;
  /// Creates a clone of this material for run-time modifications.
  HandleOf<Physics2dMaterial> RuntimeClone();

  //-------------------------------------------------------------------Properties
  float GetFriction();
  void SetFriction(float friction);

  float GetDensity();
  void SetDensity(float density);

  //-------------------------------------------------------------------Internal
  void CopyTo(Physics2dMaterial* destination);
  /// After modifying this resource, notify anyone using it to update
  /// now instead of at the next physics update.
  void UpdateAndNotifyIfModified();
  void SetDensityInternal(float density, bool markModified = true);

  /// How much an object will bounce during a collision. Values should be in the
  /// range [0,1] where 0 is an inelastic collision and 1 is a fully elastic collision.
  /// Restitution is computed as the max of the two objects.
  /// Note: due to solving constraints with baumgarte, energy will not be perfectly
  /// conserved with a restitution 1.
  float mRestitution = 0.5f;
  float mStaticFriction = 0.5f;
  float mDynamicFriction = 0.5f;
  float mDensity = 1.0f;

  /// Determines which object's restitution should be used. If object A's restitution
  /// importance value is larger than object B's then object A's restitution will be used.
  /// If both importance values are the same then the default combination logic will be used
  /// (see the description of Restitution for details).
  float mRestitutionImportance = 0.0f;
  /// Determines which object's friction should be used. If object A's friction
  /// importance value is larger than object B's then object A's friction will be used.
  /// If both importance values are the same then the default combination logic will be used
  /// (see the description of Friction for details).
  float mFrictionImportance = 0.0f;

  bool mModified = false;
};

}//namespace Physics2dCore
