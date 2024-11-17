#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class DetectorMessenger;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;
    
    void SetShapeMaterial(const G4String&);
  private:
    //Detector
    G4VPhysicalVolume* ConstructDetector();

    //Material
    void DefineMaterials();
    G4Material* fDefaultMaterial = nullptr;
    G4Material* fWorldMaterial = nullptr;
    G4Material* fShapeMaterial = nullptr;

    //World
    G4Box* fSolidWorld = nullptr;                
    G4LogicalVolume* fLogicWorld = nullptr;      
    G4VPhysicalVolume* fPhysiWorld = nullptr;    
    
	//Shape1						 
    G4Box* fSolidS1 = nullptr;                   
    G4LogicalVolume* fLogicS1 = nullptr;         
    G4VPhysicalVolume* fPhysiS1 = nullptr;       
};

#endif
