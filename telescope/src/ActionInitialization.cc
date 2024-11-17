#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
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

  auto stackingAction = new StackingAction;
  SetUserAction(stackingAction);

  auto eventAction = new EventAction();
  SetUserAction(eventAction);

  auto stepAction = new SteppingAction(eventAction);
  SetUserAction(stepAction);

}

