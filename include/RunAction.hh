#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh" // G4String
#include <fstream>

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    // Çıktı dosyasını dışarıdan erişilebilir yapmak için
    std::ofstream& GetOutputFile();

  private:
    std::ofstream fOutput; // Çıktı dosyası akışı
};

#endif