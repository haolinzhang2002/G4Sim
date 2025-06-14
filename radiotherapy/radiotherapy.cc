#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "PhysicsList.hh"
#include "Randomize.hh"

int main(int argc, char** argv) {
  G4UIExecutive* ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4SteppingVerbose::UseBestUnit(4);

  auto* runManager = new G4RunManager;
  runManager->SetUserInitialization(new DetectorConstruction());

  // G4VModularPhysicsList* physicsList = new QGSP_BERT;
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
	// G4VModularPhysicsList  physicsList = new PhysicsList;
	physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new ActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (!ui) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}
