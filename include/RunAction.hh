#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "g4analysis.hh" // Geant4'ün genel analiz yöneticisi başlığı (CSV için uygun)

class G4Run;
class G4AnalysisManager;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:
    G4AnalysisManager* fAnalysisManager;
};

#endif