#ifndef INITIALIZATION_H
#define INITIALIZATION_H 1

#include "G4VUserActionInitialization.hh"

#include "G4VProcess.hh"
#include "Generator.hh"
#include "G4GeneralParticleSource.hh"


class Initialization : public G4VUserActionInitialization
{
    public:
        Initialization();
        ~Initialization();
        void Build() const;
        void BuildForMaster() const;

    private:
        G4String outloc;
        G4GeneralParticleSource* masterGPS;
    
};

#endif
