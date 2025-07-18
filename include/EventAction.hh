#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

  private:
    // Analiz yöneticisi yok, doğrudan çıktı yok
};

#endif