#include "DetectorConstruction.hh"

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
  SetShapeMaterial("G4_Au");
}

DetectorConstruction::~DetectorConstruction()
{
}

void DetectorConstruction::DefineMaterials()
{
  //G4-NIST materials data base
  G4NistManager* man = G4NistManager::Instance();
  fDefaultMaterial = man->FindOrBuildMaterial("G4_Al");
  fWorldMaterial = man->FindOrBuildMaterial("G4_AIR");
  man->FindOrBuildMaterial("G4_Ag");
  man->FindOrBuildMaterial("G4_Au");

  //Print
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructDetector();
}


G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{
  //Construct Detector
  fSolidWorld = new G4Box("World", 40*cm, 40*cm, 60*cm);
  fLogicWorld = new G4LogicalVolume(fSolidWorld, fWorldMaterial, "World");                                      
  fPhysiWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "World", 0, false, 0);

                             
  fSolidS1 = new G4Box("Shape1", 6*cm, 6*cm, 6*cm);
  fLogicS1 = new G4LogicalVolume(fSolidS1, fDefaultMaterial, "Shape1");
  fPhysiS1 = new G4PVPlacement(0, G4ThreeVector(0, 0, -15*cm), fLogicS1, "Shape1", fLogicWorld, false, 0);
  
  return fPhysiWorld;
}

void DetectorConstruction::SetShapeMaterial(const G4String& materialChoice)
{
  // search the material by its name
  auto material = G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
  if (material != nullptr)
  {
    fShapeMaterial = material;
    if (fLogicS1 != nullptr)
    {
      fLogicS1->SetMaterial(fShapeMaterial);
      G4cout << " *** Materil Setting *** " << G4endl;
      G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
  }
}
