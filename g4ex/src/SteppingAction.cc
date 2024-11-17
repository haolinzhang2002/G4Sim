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
{}
