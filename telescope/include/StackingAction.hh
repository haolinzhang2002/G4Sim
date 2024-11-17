#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

class StackingAction : public G4UserStackingAction
{
  public:
    StackingAction() = default;
    ~StackingAction() override = default;

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
};

#endif
