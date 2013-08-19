#ifndef GENERATOR_H
#define GENERATOR_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;


class Generator : public G4VUserPrimaryGeneratorAction
{
    public:
        Generator();
        ~Generator();

    public:
        void GeneratePrimaries(G4Event* anEvent);

        G4ThreeVector GetPosition();
    private:
        G4GeneralParticleSource* gun;
};
#endif
