#include "StackingAction.hh"

#include "G4Track.hh"
#include "G4Gamma.hh"

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* track)
{
  if (track->GetParentID() == 0) return fUrgent;
  // Kill second gamma 
  // if (track->GetDefinition() == G4Gamma::Gamma()) return fKill;
  else return fUrgent;
}
