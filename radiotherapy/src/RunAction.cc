#include "RunAction.hh"

#include "DetectorConstruction.hh"
#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "PrimaryGeneratorAction.hh"

RunAction::RunAction() {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2);

  // Creating ntuple
  //
  // fNtuple1ID = analysisManager->CreateNtuple("Ntuple1", "RadiotherapyROOT");
  // fNtuple2ID = analysisManager->CreateNtuple("Ntuple2", "RunResult");
  analysisManager->CreateNtuple("Ntuple1", "RadiotherapyROOT");

  analysisManager->CreateNtupleDColumn("edepStep");    // Column0
  analysisManager->CreateNtupleDColumn("Position_X");  // Column1
  analysisManager->CreateNtupleDColumn("Position_Y");  // Column2
  analysisManager->CreateNtupleDColumn("Position_Z");  // Column3
  analysisManager->CreateNtupleDColumn("dose");        // Column4
  analysisManager->CreateNtupleDColumn("rmsDoswe");

  // Volume
  analysisManager->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run* run) {
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "radiotherapy_output.root";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* run) {
  auto analysisManager = G4AnalysisManager::Instance();

  G4cout << "Run finished. Data saved to radiotherapy_output.root" << G4endl;
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute dose = total energy deposit in a run and its variance
  //
  G4double edep = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();

  G4double rms = edep2 - edep * edep / nofEvents;
  if (rms > 0.)
    rms = std::sqrt(rms);
  else
    rms = 0.;

  const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double mass = detConstruction->GetScoringVolume()->GetMass();
  G4double dose = edep / mass;
  G4double rmsDose = rms / mass;
  analysisManager->FillNtupleDColumn(0, 4, dose);
  analysisManager->FillNtupleDColumn(0, 5, rmsDose);
  analysisManager->AddNtupleRow();

  analysisManager->Write();
  analysisManager->CloseFile();
}

void RunAction::AddEdep(G4double edep) {
  fEdep += edep;
  fEdep2 += edep * edep;
}
