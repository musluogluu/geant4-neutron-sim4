#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
    SetUserAction(new SteppingAction(runAction));
}