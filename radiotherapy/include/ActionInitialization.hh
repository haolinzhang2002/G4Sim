#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include <fstream>

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
 public:
  ActionInitialization() = default;
  ~ActionInitialization() override = default;

  void BuildForMaster() const override;
  void Build() const override;

 private:
};

#endif
