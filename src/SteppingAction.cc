#include "SteppingAction.hh"
#include "RunAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

SteppingAction::SteppingAction(RunAction* runAction)
: G4UserSteppingAction(),
  fRunAction(runAction)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    if (volume->GetLogicalVolume()->GetName() == "LeadCylinder") {
        G4Track* track = aStep->GetTrack();
        G4Event* currentEvent = G4EventManager::GetInstance()->GetCurrentEvent();
        std::ofstream& output = fRunAction->GetOutputFile();

        // Verileri dosyaya CSV formatında yaz
        output << currentEvent->GetEventID() << ","; // Burası düzelt
        output << track->GetDefinition()->GetParticleName() << ",";
        output << track->GetTrackID() << ",";
        output << track->GetParentID() << ",";
        output << G4BestUnit(track->GetKineticEnergy(), "Energy") << ",";
        output << G4BestUnit(aStep->GetTotalEnergyDeposit(), "Energy") << ",";
        output << G4BestUnit(track->GetGlobalTime(), "Time") << ",";
        output << G4BestUnit(track->GetLocalTime(), "Time") << ",";
        output << G4BestUnit(aStep->GetStepLength(), "Length") << ",";
        output << G4BestUnit(track->GetPosition().x(), "Length") << ",";
        output << G4BestUnit(track->GetPosition().y(), "Length") << ",";
        output << G4BestUnit(track->GetPosition().z(), "Length") << ",";
        output << volume->GetName() << "\n";
    }
}