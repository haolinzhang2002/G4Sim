#include "PrimaryGeneratorAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
  fParticleGun = new G4ParticleGun(1);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
  // G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1, 0, 0));
  fParticleGun->SetParticleEnergy(90 * MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  G4double x0 = 10 * cm;
  G4double y, z;
  do {
    y = (G4UniformRand() * 2 - 1) * 1 * cm;
    z = (G4UniformRand() * 2 - 1) * 3 * cm;
  } while ((y * y) / (1 * cm / 1 * cm) + (z * z) / (3 * cm / 3 * cm) > 1);

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y, z));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
