#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {}

void RunAction::EndOfRunAction(const G4Run*) {}
