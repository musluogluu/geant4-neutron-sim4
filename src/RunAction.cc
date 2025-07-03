#include "RunAction.hh"
#include "g4root.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
: G4UserRunAction(),
  fAnalysisManager(nullptr)
{
    fAnalysisManager = G4AnalysisManager::Instance();
    fAnalysisManager->SetVerboseLevel(1);
    fAnalysisManager->SetFileName("simulation_results.csv");
    fAnalysisManager->SetNtupleMerging(true);

    fAnalysisManager->CreateNtuple("Hits", "Particle Hits in Lead Cylinder");
    fAnalysisManager->CreateNtupleIColumn("EventID");
    fAnalysisManager->CreateNtupleSColumn("ParticleName");
    fAnalysisManager->CreateNtupleIColumn("TrackID");
    fAnalysisManager->CreateNtupleIColumn("ParentID");
    fAnalysisManager->CreateNtupleDColumn("KineticEnergy");
    fAnalysisManager->CreateNtupleDColumn("DepositedEnergy");
    fAnalysisManager->CreateNtupleDColumn("GlobalTime");
    fAnalysisManager->CreateNtupleDColumn("LocalTime");
    fAnalysisManager->CreateNtupleDColumn("StepLength");
    fAnalysisManager->CreateNtupleDColumn("PosX");
    fAnalysisManager->CreateNtupleDColumn("PosY");
    fAnalysisManager->CreateNtupleDColumn("PosZ");
    fAnalysisManager->CreateNtupleSColumn("VolumeName");
    fAnalysisManager->FinishNtuple(0);
}

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    fAnalysisManager->OpenFile();
    G4cout << "### Run " << G4Run::GetRunID() << " starts." << G4endl;
    G4cout << "### Output file: " << fAnalysisManager->GetFileName() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
    fAnalysisManager->Write();
    fAnalysisManager->CloseFile();
    G4cout << "### Run " << G4Run::GetRunID() << " ends. Data saved to CSV." << G4endl;
}