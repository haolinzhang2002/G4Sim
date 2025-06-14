#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction) {}

void EventAction::BeginOfEventAction(const G4Event*) { fEdep = 0; }

void EventAction::EndOfEventAction(const G4Event*) {
  fRunAction->AddEdep(fEdep);
}
