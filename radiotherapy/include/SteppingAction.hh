#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;
class EventAction;

class SteppingAction : public G4UserSteppingAction {
 public:
  SteppingAction(EventAction* eventAction);
  ~SteppingAction() override = default;
  virtual void UserSteppingAction(const G4Step*);

  G4double GetEdepTumor() const;
  G4double GetEdepNonTumor() const;

 private:
  G4int fNtuple1ID;
  G4int fNtuple2ID;

  EventAction* fEventAction = nullptr;
  G4LogicalVolume* fScoringVolume = nullptr;
};

#endif
