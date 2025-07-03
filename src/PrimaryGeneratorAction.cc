#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(new G4ParticleGun(1)),
  fEventCounter(0)
{
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    G4ParticleDefinition* pionPlus = particleTable->FindParticle("pi+");
    G4ParticleDefinition* proton   = particleTable->FindParticle("proton");

    G4double pionEnergy = 50.0 * MeV;
    G4double protonEnergy = 1.0 * GeV;

    G4ThreeVector beamDirection = G4ThreeVector(1.0, 0.0, 0.0);

    G4double cylinderRadius = 7.5 * cm;
    G4double beamStartX = -0.5 * cm;

    if (fEventCounter < 50) {
        fParticleGun->SetParticleDefinition(pionPlus);
        fParticleGun->SetParticleEnergy(pionEnergy);
    } else if (fEventCounter < 50 + 1000) {
        fParticleGun->SetParticleDefinition(proton);
        fParticleGun->SetParticleEnergy(protonEnergy);
    } else {
        fParticleGun->SetParticleDefinition(proton);
        fParticleGun->SetParticleEnergy(protonEnergy);
    }

    G4double startY = (G4UniformRand() - 0.5) * 2.0 * cylinderRadius;
    G4double startZ = (G4UniformRand() - 0.5) * 2.0 * cylinderRadius;

    while (std::sqrt(startY*startY + startZ*startZ) > cylinderRadius) {
        startY = (G4UniformRand() - 0.5) * 2.0 * cylinderRadius;
        startZ = (G4UniformRand() - 0.5) * 2.0 * cylinderRadius;
    }

    G4ThreeVector beamPosition = G4ThreeVector(beamStartX, startY, startZ);

    fParticleGun->SetParticlePosition(beamPosition);
    fParticleGun->SetParticleMomentumDirection(beamDirection);

    fParticleGun->GeneratePrimaryVertex(anEvent);

    fEventCounter++;
}