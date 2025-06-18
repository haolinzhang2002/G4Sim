#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
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
#include "G4StateManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  // Material
  G4NistManager* man = G4NistManager::Instance();
  fWorldMaterial = man->FindOrBuildMaterial("G4_AIR");
  fDetectorMaterial = man->FindOrBuildMaterial("G4_Si");

  // World
  G4double half_x = 20 * cm, half_y = 20 * cm, half_z = 20 * cm;
  fSolidWorld = new G4Box("World", half_x, half_y, half_z);
  fLogicalWorld = new G4LogicalVolume(fSolidWorld, fWorldMaterial, "World");
  fPhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicalWorld, "World",
                                     0, false, 0);

  // Detector
  fSolidDetector = new G4Box("Detector", 6 * cm, 6 * cm, 6 * cm);
  fLogicalDetector =
      new G4LogicalVolume(fSolidDetector, fDetectorMaterial, "Detector");
  fPhysicalDetector =
      new G4PVPlacement(0, G4ThreeVector(0, 0, -15 * cm), fLogicalDetector,
                        "Detector", fLogicalWorld, false, 0);

  return fPhysicalWorld;
}
