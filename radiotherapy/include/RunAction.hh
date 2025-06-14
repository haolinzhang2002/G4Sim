#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4Accumulable.hh"
#include "G4Step.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

class Run;
class G4Step;

class RunAction : public G4UserRunAction {
 public:
  RunAction();
  ~RunAction() override = default;
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
  void AddEdep(G4double edep);

 private:
  G4Accumulable<G4double> fEdep = 0.;
  G4Accumulable<G4double> fEdep2 = 0.;
};

#endif
