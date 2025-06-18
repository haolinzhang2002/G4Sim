#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"

// Constructor: Register all required physics modules
PhysicsList::PhysicsList() : G4VModularPhysicsList() {
  // Set default tracking cut for all particles (1 mm range)
  SetDefaultCutValue(1.0 * mm);

  // Register electromagnetic physics
  RegisterPhysics(new G4EmStandardPhysics());

  // Register hadronic elastic scattering physics
  RegisterPhysics(new G4HadronElasticPhysicsXS());

  // Register hadronic inelastic scattering physics (FTFP_BERT model)
  RegisterPhysics(new G4HadronPhysicsFTFP_BERT());

  // Register particle decay physics (weak interaction)
  RegisterPhysics(new G4DecayPhysics());

  // Register radioactive decay physics (weak interaction)
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts() { G4VModularPhysicsList::SetCuts(); }
