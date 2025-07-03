#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class RunAction; // RunAction
class G4Step;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(RunAction* runAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    RunAction* fRunAction; // RunAction
};

#endif