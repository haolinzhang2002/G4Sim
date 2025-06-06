#include "EventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "RunAction.hh"

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction) {}

void EventAction::BeginOfEventAction(const G4Event*) {}

void EventAction::EndOfEventAction(const G4Event*) {}
