#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"

class G4VPhysicsConstructor;

class Physics: public G4VUserPhysicsList
{
    public:

        Physics();
        ~Physics();

        void SetCuts();
        void SetCutsForRegion(G4double aCut, const G4String& rname);
        void ConstructParticle();
        void ConstructProcess();

    private:

        G4double cutForGamma;
        G4double cutForElectron;
        G4double cutForPositron;
        G4double cutForProton;

        G4VPhysicsConstructor* emPhysicsList;
        G4VPhysicsConstructor* hadrPhysicsList;
        G4VPhysicsConstructor* decayPhys;

};
#endif
