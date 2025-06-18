#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
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

 private:
  // Material
  G4Material* fWorldMaterial = nullptr;
  G4Material* fDetectorMaterial = nullptr;

  // World
  G4Box* fSolidWorld = nullptr;
  G4LogicalVolume* fLogicalWorld = nullptr;
  G4VPhysicalVolume* fPhysicalWorld = nullptr;

  // Detector
  G4Box* fSolidDetector = nullptr;
  G4LogicalVolume* fLogicalDetector = nullptr;
  G4VPhysicalVolume* fPhysicalDetector = nullptr;
};

#endif
