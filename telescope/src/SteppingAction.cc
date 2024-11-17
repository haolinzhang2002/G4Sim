#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include <iomanip>

SteppingAction::SteppingAction(EventAction* eventAction): fEventAction(eventAction)
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  G4VPhysicalVolume* volume = track->GetVolume();

  auto analysisManager = G4AnalysisManager::Instance();	

  G4int trackId = track->GetTrackID();
  G4int parentId = track->GetParentID();
  G4double energy = track->GetKineticEnergy();

  G4ThreeVector position = track->GetPosition();
  G4double pos_x = position.x();
  G4double pos_y = position.y();
  G4double pos_z = position.z();

  G4ThreeVector momentum = track->GetMomentum();
  G4double mmt_x = momentum.x();
  G4double mmt_y = momentum.y();
  G4double mmt_z = momentum.z();

  G4String particleId = track->GetParticleDefinition()->GetParticleName();
  G4String processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

if (volume->GetName()!="World")
  {
  analysisManager->FillNtupleDColumn(0, 0, energy);
  analysisManager->FillNtupleSColumn(0, 1, processName);
  
  analysisManager->FillNtupleDColumn(0, 2, pos_x);
  analysisManager->FillNtupleDColumn(0, 3, pos_y);
  analysisManager->FillNtupleDColumn(0, 4, pos_z);

  analysisManager->FillNtupleDColumn(0, 5, mmt_x);
  analysisManager->FillNtupleDColumn(0, 6, mmt_y);
  analysisManager->FillNtupleDColumn(0, 7, mmt_z);

  analysisManager->AddNtupleRow();
  }
}
