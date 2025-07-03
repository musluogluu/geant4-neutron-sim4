#include "SteppingAction.hh"
#include "g4analysis.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction()
: G4UserSteppingAction(),
  fAnalysisManager(G4AnalysisManager::Instance())
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

        fAnalysisManager->FillNtupleIColumn(0, 0, aStep->GetTrack()->GetCurrentEvent()->GetEventID());
        fAnalysisManager->FillNtupleSColumn(0, 1, track->GetDefinition()->GetParticleName());
        fAnalysisManager->FillNtupleIColumn(0, 2, track->GetTrackID());
        fAnalysisManager->FillNtupleIColumn(0, 3, track->GetParentID());
        fAnalysisManager->FillNtupleDColumn(0, 4, track->GetKineticEnergy());
        fAnalysisManager->FillNtupleDColumn(0, 5, aStep->GetTotalEnergyDeposit());
        fAnalysisManager->FillNtupleDColumn(0, 6, track->GetGlobalTime());
        fAnalysisManager->FillNtupleDColumn(0, 7, track->GetLocalTime());
        fAnalysisManager->FillNtupleDColumn(0, 8, aStep->GetStepLength());
        fAnalysisManager->FillNtupleDColumn(0, 9, track->GetPosition().x());
        fAnalysisManager->FillNtupleDColumn(0, 10, track->GetPosition().y());
        fAnalysisManager->FillNtupleDColumn(0, 11, track->GetPosition().z());
        fAnalysisManager->FillNtupleSColumn(0, 12, volume->GetName());

        fAnalysisManager->AddNtupleRow(0);
    }
}