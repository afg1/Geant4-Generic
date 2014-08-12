#include "Initialization.hh"
#include "Generator.hh"
#include "G4GeneralParticleSource.hh"
#include "RunAction.hh"

Initialization::Initialization()
{
    masterGPS = new G4GeneralParticleSource();
}

Initialization::~Initialization()
{
    delete masterGPS;
}

void Initialization::Build() const
{
    SetUserAction(new Generator);
    SetUserAction(new RunAction());
}

void Initialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}
