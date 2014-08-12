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
}

Generator::~Generator()
{
    delete gun;
}


void Generator::GeneratePrimaries(G4Event* anEvent)
{
    gun->GeneratePrimaryVertex(anEvent);
}
