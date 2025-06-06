#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Ellipsoid.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SolidStore.hh"
#include "G4Sphere.hh"
#include "G4StateManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction() {
  // materials
  DefineMaterials();
}

DetectorConstruction::~DetectorConstruction() {}

void DetectorConstruction::DefineMaterials() {
  // G4-NIST materials data base
  G4NistManager* man = G4NistManager::Instance();
  fDefaultMaterial = man->FindOrBuildMaterial("G4_AIR");
  fWorldMaterial = man->FindOrBuildMaterial("G4_AIR");
  fTumorMaterial = man->FindOrBuildMaterial("G4_A-150_TISSUE");
  fBodyMaterial = man->FindOrBuildMaterial("G4_A-150_TISSUE");

  // Print
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  return ConstructDetector();
}

G4VPhysicalVolume* DetectorConstruction::ConstructDetector() {
  // Construct Detector
  fSolidWorld = new G4Box("World", 120 * cm, 120 * cm, 240 * cm);
  fLogicWorld = new G4LogicalVolume(fSolidWorld, fWorldMaterial, "World");
  fPhysiWorld =
      new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "World", 0, false, 0);

  // Head
  fSolidHead =
      new G4Sphere("Head", 0 * mm, 90 * mm, 0, 360 * deg, 0, 180 * deg);
  fLogicHead = new G4LogicalVolume(fSolidHead, fBodyMaterial, "Head");
  fPhysiHead = new G4PVPlacement(0, G4ThreeVector(0, -80 * mm, 420 * mm),
                                 fLogicHead, "Head", fLogicWorld, false, 0);

  // Neck
  fSolidNeck = new G4Tubs("Neck", 0., 50 * mm, 45 * mm, 0. * deg, 360. * deg);
  fLogicNeck = new G4LogicalVolume(fSolidNeck, fBodyMaterial, "Neck");
  fPhysiNeck = new G4PVPlacement(0, G4ThreeVector(0, -80 * mm, 295 * mm),
                                 fLogicNeck, "Neck", fLogicWorld, false, 0);

  // Leg
  fSolidLeftLeg =
      new G4Tubs("LeftLeg", 0., 55 * mm, 410 * mm, 0. * deg, 360. * deg);
  fLogicLeftLeg = new G4LogicalVolume(fSolidLeftLeg, fBodyMaterial, "LeftLeg");
  fPhysiLeftLeg =
      new G4PVPlacement(0, G4ThreeVector(0, 0, -66 * cm), fLogicLeftLeg,
                        "LeftLeg", fLogicWorld, false, 0);
  fSolidRightLeg =
      new G4Tubs("RightLeg", 0., 55 * mm, 410 * mm, 0. * deg, 360. * deg);
  fLogicRightLeg =
      new G4LogicalVolume(fSolidRightLeg, fBodyMaterial, "RightLeg");
  fPhysiRightLeg =
      new G4PVPlacement(0, G4ThreeVector(0, -155 * mm, -66 * cm),
                        fLogicRightLeg, "RightLeg", fLogicWorld, false, 0);

  // Tumor
  fSolidTumor = new G4Ellipsoid("Tumor", 2 * cm, 1 * cm, 3 * cm);
  fLogicTumor = new G4LogicalVolume(fSolidTumor, fTumorMaterial, "Tumor");
  fPhysiTumor = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), fLogicTumor,
                                  "Tumor", fLogicWorld, false, 0);

  // Body
  fSolidBody = new G4Box("Body", 60 * mm, 130 * mm, 250 * mm);
  G4ThreeVector transition(0, 80 * mm, 0);
  G4SubtractionSolid* fSolidBody_subtraction = new G4SubtractionSolid(
      "SolidBody", fSolidBody, fSolidTumor, 0, transition);
  fLogicBody =
      new G4LogicalVolume(fSolidBody_subtraction, fBodyMaterial, "Body");
  fPhysiBody = new G4PVPlacement(0, G4ThreeVector(0, -80 * mm, -0), fLogicBody,
                                 "Body", fLogicWorld, false, 0);

  return fPhysiWorld;
}
