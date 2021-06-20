#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class ContactConstraint2dManifold;
class Constraint2dMolecule;
class Constraint2dMoleculeWalker;
class Physics2dMaterial;

//-------------------------------------------------------------------Contact2dMolecules
class Contact2dMolecules
{
public:
  static size_t Size(const ContactConstraint2dManifold& manifold);
  static void ComputeMolecules(const ContactConstraint2dManifold& manifold, Constraint2dMoleculeWalker& molecules);
  static void ComputeSurfaceInfo(const ContactConstraint2dManifold& manifold, float& restitution, float& friction);
  static float ComputeFriction(const Physics2dMaterial& material0, const Physics2dMaterial& material1);
  static float ComputeRestitution(const Physics2dMaterial& material0, const Physics2dMaterial& material1);
};

}//namespace Physics2dCore
