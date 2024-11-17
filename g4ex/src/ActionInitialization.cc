#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include <fstream>

void ActionInitialization::BuildForMaster() const
{
  auto runAction = new RunAction;
  SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);
  
  auto runAction = new RunAction;
  SetUserAction(runAction);

  auto eventAction = new EventAction();
  SetUserAction(eventAction);

  auto stepAction = new SteppingAction(eventAction);
  SetUserAction(stepAction);

}

