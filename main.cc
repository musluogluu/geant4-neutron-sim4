#include "G4RunManagerFactory.hh"
#include "G4PhysListFactory.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

int main(int argc, char** argv)
{
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

    runManager->SetUserInitialization(new DetectorConstruction());

    G4PhysListFactory physListFactory;
    runManager->SetUserInitialization(physListFactory.GetPhysicsList("FTFP_BERT")); // GetPhysicsList düzeltmesi burada önemli

    runManager->SetUserInitialization(new ActionInitialization());

    runManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        ui->SessionStart();
        delete ui;
    } else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    delete runManager;

    return 0;
}