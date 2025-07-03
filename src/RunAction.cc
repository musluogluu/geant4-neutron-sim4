#include "RunAction.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh" // Run ID için

RunAction::RunAction()
: G4UserRunAction()
{
    // Dosya adını ve başlıkları RunAction'ın yapıcı metodunda ayarlıyoruz
    fOutput.open("simulation_output.txt"); // veya .csv
    if (fOutput.is_open()) {
        fOutput << "EventID,ParticleName,TrackID,ParentID,KineticEnergy(MeV),DepositedEnergy(MeV),GlobalTime(ns),LocalTime(ns),StepLength(mm),PosX(mm),PosY(mm),PosZ(mm),VolumeName\n";
    } else {
        G4Exception("RunAction", "RunAction001", FatalException, "Cannot open output file!");
    }
}

RunAction::~RunAction()
{
    // Dosyayı kapat
    if (fOutput.is_open()) {
        fOutput.close();
    }
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "### Run " << run->GetRunID() << " starts." << G4endl;
    G4RunManager::GetRunManager()->SetPrintProgress(100); // Her 100 olayda bir ilerlemeyi yazdır
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4cout << "### Run " << run->GetRunID() << " ends." << G4endl;
    G4cout << "Total number of events: " << run->GetNumberOfEvent() << G4endl;
    G4cout << "Data saved to simulation_output.txt" << G4endl;
}

std::ofstream& RunAction::GetOutputFile()
{
    return fOutput;
}