#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RotationMatrix.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  fParticleGun  = new G4ParticleGun(1);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particle);
  G4double randomAngle = G4UniformRand() * 0.649 * degree;
  G4double vtxx = std::cos(90 * degree - randomAngle);
  G4double vtxy = std::cos(90 * degree - randomAngle);
  G4double vtxz = std::cos(randomAngle);
  std::cout << vtxz << std::endl;
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vtxx, vtxy, vtxz));
  fParticleGun->SetParticleEnergy(4*GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Generate random numbers from Gaussian distributions
  G4double sigmaX = 3.04*mm;
  G4double sigmaY = 3.04*mm;
  G4double sigmaT = 1.52*ns;

  G4double x0 = G4RandGauss::shoot(0., sigmaX);
  G4double y0 = G4RandGauss::shoot(0., sigmaY);
  G4double t0 = G4RandGauss::shoot(0., sigmaT);

  // Set particle position and time
  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, 0.));
  fParticleGun->SetParticleTime(t0);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
