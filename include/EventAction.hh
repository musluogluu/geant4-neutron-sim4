#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "g4analysis.hh" // Geant4 analiz yöneticisi başlığı

class G4AnalysisManager;

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

  private:
    G4AnalysisManager* fAnalysisManager;
};

#endif