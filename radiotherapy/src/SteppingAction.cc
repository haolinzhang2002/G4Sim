#include "SteppingAction.hh"

#include <iomanip>

#include "EventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
    : fEventAction(eventAction) {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
  auto analysisManager = G4AnalysisManager::Instance();

  G4Track* track = step->GetTrack();

  G4ThreeVector position = track->GetPosition();
  G4double pos_x = position.x();
  G4double pos_y = position.y();
  G4double pos_z = position.z();

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()
                                ->GetTouchableHandle()
                                ->GetVolume()
                                ->GetLogicalVolume();

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);

  G4String volume_name = volume->GetName();

  if (volume->GetName() != "World")
  // if (volume->GetName()=="Tumor")
  {
    analysisManager->FillNtupleDColumn(0, 0, edepStep);
    analysisManager->FillNtupleDColumn(0, 1, pos_x);
    analysisManager->FillNtupleDColumn(0, 2, pos_y);
    analysisManager->FillNtupleDColumn(0, 3, pos_z);
    analysisManager->FillNtupleSColumn(0, 4, volume_name);
    analysisManager->AddNtupleRow();
  }
}
