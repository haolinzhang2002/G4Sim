#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction() {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Ntuple1", "RadiotherapyROOT");

  // Energy and ProcessName
  analysisManager->CreateNtupleDColumn("edepStep");  // Column0

  // Position
  analysisManager->CreateNtupleDColumn("Position_X");  // Column1
  analysisManager->CreateNtupleDColumn("Position_Y");  // Column2
  analysisManager->CreateNtupleDColumn("Position_Z");  // Column3

  // Volume
  analysisManager->CreateNtupleSColumn("Volume");  // Column4

  analysisManager->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run*) {
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "radiotherapy_output.root";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run*) {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "Run finished. Data saved to radiotherapy_output.root" << G4endl;
}
