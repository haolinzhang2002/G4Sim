#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4DecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4StoppingPhysics.hh"

#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4IonPhysicsPHP.hh"
#include "G4IonElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "PhysicsList.hh"

PhysicsList::PhysicsList(){
  SetVerboseLevel(1);

  // EM Physics
  RegisterPhysics( new G4EmLivermorePhysics() );

  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4RadioactiveDecayPhysics() );

  // Decays
  RegisterPhysics( new G4DecayPhysics() );

  // Hadron Physics
  RegisterPhysics( new G4HadronElasticPhysicsHP());

  RegisterPhysics( new G4StoppingPhysics());

  RegisterPhysics( new G4IonPhysicsPHP());

  //RegisterPhysics( new G4IonElasticPhysics() );

  RegisterPhysics( new G4HadronPhysicsQGSP_BERT_HP());

  // Neutron tracking cut
  //RegisterPhysics( new G4NeutronTrackingCut() );
}

void PhysicsList::SetCuts(){
  G4VUserPhysicsList::SetCuts();
  SetCutValue(1.*mm,"gamma");
  SetCutValue(0.1*mm,"e-");
  SetCutValue(0.1*mm,"e+");
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250*eV, 100*TeV);
}
