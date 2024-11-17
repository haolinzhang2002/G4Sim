#ifndef DetectorMessenger_h
#define DetectorMessenger_h

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;

class DetectorMessenger : public G4UImessenger
{
public:
  DetectorMessenger(DetectorConstruction* );
  ~DetectorMessenger() override;

  void SetNewValue(G4UIcommand*, G4String) override;

private:
  DetectorConstruction* fDetector = nullptr;

  G4UIdirectory*             fDetDir = nullptr;
  G4UIcmdWithAString*        fPlaneMaterCmd = nullptr;
  G4UIcmdWithADoubleAndUnit* fPlaneThickCmd = nullptr;
  
  G4UIcmdWithADoubleAndUnit* fStepMaxCmd = nullptr;
};

#endif
