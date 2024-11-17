#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4StateManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "G4UserLimits.hh"

DetectorConstruction::DetectorConstruction()
{
  // materials
  DefineMaterials();
  SetPlaneMaterial("G4_Si");

  //Messenger
  fDetectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
  delete fDetectorMessenger;
}

void DetectorConstruction::DefineMaterials()
{
  //G4-NIST materials data base
  G4NistManager* man = G4NistManager::Instance();
  fDefaultMaterial = man->FindOrBuildMaterial("G4_Si");
  fWorldMaterial = man->FindOrBuildMaterial("G4_AIR");
  man->FindOrBuildMaterial("G4_Ag");
  man->FindOrBuildMaterial("G4_Au");

  //Print
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructTelescope();
}


G4VPhysicalVolume* DetectorConstruction::ConstructTelescope()
{
  //Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();	
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  //Construct Telescope
  fSolidWorld = new G4Box("World", 40*mm, 40*mm, 300*mm);
  fLogicWorld = new G4LogicalVolume(fSolidWorld, fWorldMaterial, "World");                                      
  fPhysiWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "World", 0, false, 0, checkOverlaps);

                             
  fSolidP1 = new G4Box("Plane1", 7.04*mm, 14.08*mm, fPlaneThickness/2*um);
  fLogicP1 = new G4LogicalVolume(fSolidP1, fDefaultMaterial, "Plane1");
  fPhysiP1 = new G4PVPlacement(0, G4ThreeVector(0, 0, 30*mm), fLogicP1, "Plane1", fLogicWorld, false, 0, checkOverlaps);
  
  fSolidP2 = new G4Box("Plane2", 7.04*mm, 14.08*mm, fPlaneThickness/2*um);
  fLogicP2 = new G4LogicalVolume(fSolidP2, fDefaultMaterial, "Plane2");
  fPhysiP2 = new G4PVPlacement(0, G4ThreeVector(0, 0, 60*mm), fLogicP2, "Plane2", fLogicWorld, false, 0, checkOverlaps);  
  
  fSolidP3 = new G4Box("Plane3", 7.04*mm, 14.08*mm, fPlaneThickness/2*um);
  fLogicP3 = new G4LogicalVolume(fSolidP3, fDefaultMaterial, "Plane3");
  fPhysiP3 = new G4PVPlacement(0, G4ThreeVector(0, 0, 90*mm), fLogicP3, "Plane3", fLogicWorld, false, 0, checkOverlaps);
  
  fSolidP4 = new G4Box("Plane4", 7.04*mm, 14.08*mm, 0.5*um);
  fLogicP4 = new G4LogicalVolume(fSolidP4, fDefaultMaterial, "Plane4");
  fPhysiP4 = new G4PVPlacement(0, G4ThreeVector(0, 0, 105*mm), fLogicP4, "Plane4", fLogicWorld, false, 0, checkOverlaps);

  fSolidP5 = new G4Box("Plane5", 7.04*mm, 14.08*mm, fPlaneThickness/2*um);
  fLogicP5 = new G4LogicalVolume(fSolidP5, fDefaultMaterial, "Plane5");
  fPhysiP5 = new G4PVPlacement(0, G4ThreeVector(0, 0, 120*mm), fLogicP5, "Plane5", fLogicWorld, false, 0, checkOverlaps);
  
  fSolidP6 = new G4Box("Plane6", 7.04*mm, 14.08*mm, fPlaneThickness/2*um);
  fLogicP6 = new G4LogicalVolume(fSolidP6, fDefaultMaterial, "Plane6");
  fPhysiP6 = new G4PVPlacement(0, G4ThreeVector(0, 0, 150*mm), fLogicP6, "Plane6", fLogicWorld, false, 0, checkOverlaps);

  fSolidP7 = new G4Box("Plane7", 7.04*mm, 14.08*mm, fPlaneThickness/2*um);
  fLogicP7 = new G4LogicalVolume(fSolidP7, fDefaultMaterial, "Plane7");
  fPhysiP7 = new G4PVPlacement(0, G4ThreeVector(0, 0, 180*mm), fLogicP6, "Plane6", fLogicWorld, false, 0, checkOverlaps);

  return fPhysiWorld;
}

void DetectorConstruction::SetPlaneMaterial(const G4String& materialChoice)
{
  // search the material by its name
  auto material = G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
  if (material != nullptr)
  {
    fPlaneMaterial = material;
    if ((fLogicP1 != nullptr) && (fLogicP2 != nullptr) && (fLogicP3 != nullptr) && (fLogicP4 != nullptr) && (fLogicP5 != nullptr) && (fLogicP6 != nullptr))
    {
      fLogicP1->SetMaterial(fPlaneMaterial);
      fLogicP2->SetMaterial(fPlaneMaterial);
      fLogicP3->SetMaterial(fPlaneMaterial);
      fLogicP4->SetMaterial(fPlaneMaterial);
      fLogicP5->SetMaterial(fPlaneMaterial);
      fLogicP6->SetMaterial(fPlaneMaterial);
      fLogicP7->SetMaterial(fPlaneMaterial);
      G4cout << " ***** Plane Material Setting *****" << G4endl;
      G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
  }
}

void DetectorConstruction::SetPlaneThickness(G4double value)
{
  // Change thickness
  fPlaneThickness = value;
  if ( G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit ) 
  {
    G4RunManager::GetRunManager()->ReinitializeGeometry();
    G4cout << " ***** Plane Thickness Setting *****" << G4endl;
  }
}

void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
  G4cout << " ***** Max Step Setting *****" << G4endl;
}

