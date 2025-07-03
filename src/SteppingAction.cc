#include "SteppingAction.hh"
#include "RunAction.hh" // RunAction'ın tam tanımı gerekli

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh" // Birimler için
#include "G4Event.hh" // EventID için

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
        std::ofstream& output = fRunAction->GetOutputFile();

        output << aStep->GetTrack()->GetCurrentEvent()->GetEventID() << ",";
        output << track->GetDefinition()->GetParticleName() << ",";
        output << track->GetTrackID() << ",";
        output << track->GetParentID() << ",";
        output << G4BestUnit(track->GetKineticEnergy(), "Energy") << ","; // MeV cinsinden
        output << G4BestUnit(aStep->GetTotalEnergyDeposit(), "Energy") << ","; // MeV cinsinden
        output << G4BestUnit(track->GetGlobalTime(), "Time") << ","; // ns cinsinden
        output << G4BestUnit(track->GetLocalTime(), "Time") << ","; // ns cinsinden
        output << G4BestUnit(aStep->GetStepLength(), "Length") << ","; // mm cinsinden
        output << G4BestUnit(track->GetPosition().x(), "Length") << ","; // mm cinsinden
        output << G4BestUnit(track->GetPosition().y(), "Length") << ","; // mm cinsinden
        output << G4BestUnit(track->GetPosition().z(), "Length") << ","; // mm cinsinden
        output << volume->GetName() << "\n";
    }
}