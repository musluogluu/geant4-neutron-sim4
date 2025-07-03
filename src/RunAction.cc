#include "RunAction.hh"
#include "g4analysis.hh" // G4CsvAnalysisManager'ı içerir

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
: G4UserRunAction(),
  fAnalysisManager(nullptr)
{
    fAnalysisManager = G4AnalysisManager::Instance();
    fAnalysisManager->SetVerboseLevel(1);
    fAnalysisManager->SetFileName("simulation_results"); // .csv uzantısı otomatik eklenir
    fAnalysisManager->SetNtupleMerging(true);

    fAnalysisManager->CreateNtuple("Hits", "Particle Hits in Lead Cylinder");
    fAnalysisManager->CreateNtupleIColumn(0, "EventID");
    fAnalysisManager->CreateNtupleSColumn(0, "ParticleName");
    fAnalysisManager->CreateNtupleIColumn(0, "TrackID");
    fAnalysisManager->CreateNtupleIColumn(0, "ParentID");
    fAnalysisManager->CreateNtupleDColumn(0, "KineticEnergy");
    fAnalysisManager->CreateNtupleDColumn(0, "DepositedEnergy");
    fAnalysisManager->CreateNtupleDColumn(0, "GlobalTime");
    fAnalysisManager->CreateNtupleDColumn(0, "LocalTime");
    fAnalysisManager->CreateNtupleDColumn(0, "StepLength");
    fAnalysisManager->CreateNtupleDColumn(0, "PosX");
    fAnalysisManager->CreateNtupleDColumn(0, "PosY");
    fAnalysisManager->CreateNtupleDColumn(0, "PosZ");
    fAnalysisManager->CreateNtupleSColumn(0, "VolumeName");
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
    G4cout << "### Run " << G4Run::GetRunID() << " ends. Data saved to CSV file." << G4endl;
}