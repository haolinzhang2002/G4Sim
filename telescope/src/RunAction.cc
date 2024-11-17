#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Ntuple1", "BTSRoot");

  // Energy and ProcessName
  analysisManager->CreateNtupleDColumn("Energy"); //Column0
  analysisManager->CreateNtupleSColumn(0, "ProcessName"); //Column1

  // Position
  analysisManager->CreateNtupleDColumn("Position_X"); //Column2
  analysisManager->CreateNtupleDColumn("Position_Y"); //Column3
  analysisManager->CreateNtupleDColumn("Position_Z"); //Column4

  // Momentum
  analysisManager->CreateNtupleDColumn("Momentum_X"); //Column5
  analysisManager->CreateNtupleDColumn("Momentum_Y"); //Column6
  analysisManager->CreateNtupleDColumn("Momentum_Z"); //Column7

  analysisManager->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "BTS.root";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
