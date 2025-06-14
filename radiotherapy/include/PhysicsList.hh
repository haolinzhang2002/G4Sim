#ifndef PHYLSICSIST_H
#define PHYSICSLIST_H 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class PhysicsList : public G4VModularPhysicsList
{
public:

  PhysicsList();

  ~PhysicsList()=default;

  // copy constructor and hide assignment operator
  PhysicsList(const PhysicsList &)=delete;
  PhysicsList & operator=(const PhysicsList &right)=delete;

  void SetCuts();
};

#endif
