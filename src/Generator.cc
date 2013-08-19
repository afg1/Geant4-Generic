#include "Generator.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"


Generator::Generator()
{
    gun = new G4GeneralParticleSource();

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    gun->SetParticleDefinition(particleTable->FindParticle(particleName="proton"));
}

Generator::~Generator()
{
    delete gun;
}


void Generator::GeneratePrimaries(G4Event* anEvent)
{
    gun->GeneratePrimaryVertex(anEvent);
}
