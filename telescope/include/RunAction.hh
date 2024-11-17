#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Step.hh"
#include "globals.hh"

class Run;
class G4Step;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override = default;
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
  private:
    
};

#endif

