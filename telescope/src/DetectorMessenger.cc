#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det): fDetector(Det)
{
  G4bool broadcast = false;
  fDetDir = new G4UIdirectory("/det/",broadcast);
  fDetDir->SetGuidance("Detector control");
  //Plane Material
  fPlaneMaterCmd = new G4UIcmdWithAString("/det/setPlaneMat",this);
  fPlaneMaterCmd->SetGuidance("Select Material of Plane");
  fPlaneMaterCmd->SetParameterName("PlaneMat",false);
  fPlaneMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //Plane Thickness
  fPlaneThickCmd = new G4UIcmdWithADoubleAndUnit("/det/setPlaneThick",this);
  fPlaneThickCmd->SetGuidance("Set Thickness of Plane");
  fPlaneThickCmd->SetParameterName("PlaneThick",false);
  fPlaneThickCmd->SetRange("PlaneThick>=0.");
  fPlaneThickCmd->SetUnitCategory("Length");
  fPlaneThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //StepMax
  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("stepMax",false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
  delete fPlaneMaterCmd;
  delete fPlaneThickCmd;
  delete fDetDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == fPlaneMaterCmd ) 
  {
    fDetector->SetPlaneMaterial(newValue);
    return;
  }
  if( command == fPlaneThickCmd ) 
  {
    fDetector->SetPlaneThickness(fPlaneThickCmd->GetNewDoubleValue(newValue));
    return;
  }
  if( command == fStepMaxCmd ) 
  {
    fDetector->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
  }
}
