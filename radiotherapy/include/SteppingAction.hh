#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;
class EventAction;

class SteppingAction : public G4UserSteppingAction {
 public:
  SteppingAction(EventAction* eventAction);
  ~SteppingAction() override = default;
  virtual void UserSteppingAction(const G4Step*);

 private:
  EventAction* fEventAction = nullptr;
};

#endif
