#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4SubtractionSolid.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4Ellipsoid;
class G4Tubs;
class G4Sphere;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class DetectorMessenger;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction {
 public:
  DetectorConstruction();
  ~DetectorConstruction() override;

  G4VPhysicalVolume* Construct() override;

  // void SetShapeMaterial(const G4String&);
 private:
  // Detector
  G4VPhysicalVolume* ConstructDetector();

  // Material
  void DefineMaterials();
  G4Material* fDefaultMaterial = nullptr;
  G4Material* fWorldMaterial = nullptr;
  G4Material* fShapeMaterial = nullptr;
  G4Material* fBodyMaterial = nullptr;
  G4Material* fTumorMaterial = nullptr;

  // World
  G4Box* fSolidWorld = nullptr;
  G4LogicalVolume* fLogicWorld = nullptr;
  G4VPhysicalVolume* fPhysiWorld = nullptr;

  // Head
  G4Sphere* fSolidHead = nullptr;
  G4LogicalVolume* fLogicHead = nullptr;
  G4VPhysicalVolume* fPhysiHead = nullptr;

  // Neck
  G4Tubs* fSolidNeck = nullptr;
  G4LogicalVolume* fLogicNeck = nullptr;
  G4VPhysicalVolume* fPhysiNeck = nullptr;

  // Tumor
  G4Ellipsoid* fSolidTumor = nullptr;
  G4LogicalVolume* fLogicTumor = nullptr;
  G4VPhysicalVolume* fPhysiTumor = nullptr;

  // Body
  G4SubtractionSolid* fSolidBody_substraction;
  G4Box* fSolidBody = nullptr;
  G4LogicalVolume* fLogicBody = nullptr;
  G4VPhysicalVolume* fPhysiBody = nullptr;

  // Leg
  G4Tubs* fSolidLeftLeg = nullptr;
  G4LogicalVolume* fLogicLeftLeg = nullptr;
  G4VPhysicalVolume* fPhysiLeftLeg = nullptr;
  G4Tubs* fSolidRightLeg = nullptr;
  G4LogicalVolume* fLogicRightLeg = nullptr;
  G4VPhysicalVolume* fPhysiRightLeg = nullptr;
};

#endif
