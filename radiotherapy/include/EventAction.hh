#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class SteppingAction;

class EventAction : public G4UserEventAction {
 public:
  EventAction(RunAction* runAction);
  ~EventAction() override = default;

  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;
  void AddEdep(G4double edep) { fEdep += edep; }

 private:
  RunAction* fRunAction = nullptr;
  G4double fEdep = 0;
};

#endif
