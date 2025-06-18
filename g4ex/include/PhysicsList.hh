#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsList : public G4VModularPhysicsList {
 public:
  PhysicsList();
  virtual ~PhysicsList();

  virtual void SetCuts();
};

#endif
