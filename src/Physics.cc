#include "Physics.hh"

#include<iostream>
#include "G4EmDNAPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmProcessOptions.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4HadronInelasticQLHEP.hh"
#include "HadronPhysicsQGSP_BIC.hh"
#include "G4ProcessManager.hh"
#include "G4DecayPhysics.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
Physics::Physics(): G4VUserPhysicsList()
{
    defaultCutValue = 0.01*mm;//1*nanometer;// Changed this in the hope of speeding up the simulation a bit
    cutForGamma = defaultCutValue;
    cutForElectron = defaultCutValue;
    cutForPositron = defaultCutValue;
    cutForProton = defaultCutValue;//1e-6*mm;// Chosen to roughly correspond to the NIST data shortest range

    emPhysicsList = new G4EmStandardPhysics();
    hadrPhysicsList = new HadronPhysicsQGSP_BIC("hadronphys");//, ver, false, false, true, false);
    decayPhys = new G4DecayPhysics("decays");
}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
Physics::~Physics()
{
    delete emPhysicsList;
    delete hadrPhysicsList;
    delete decayPhys;

    emPhysicsList = NULL;
    hadrPhysicsList = NULL;
    decayPhys = NULL;
}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
void Physics::ConstructParticle()
{
    emPhysicsList->ConstructParticle();
    hadrPhysicsList->ConstructParticle();
    decayPhys->ConstructParticle();

}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
void Physics::ConstructProcess()
{
    AddTransportation();
    emPhysicsList->ConstructProcess();
    hadrPhysicsList->ConstructProcess();
    decayPhys->ConstructProcess();

}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
void Physics::SetCuts()
{
    SetCutsWithDefault();
}

void Physics::SetCutsForRegion(G4double aCut, const G4String& rname)
{
    SetCutValue(aCut, "gamma", rname);
    SetCutValue(aCut, "e-", rname);
    SetCutValue(aCut, "e+", rname);
    SetCutValue(aCut, "proton", rname);
}
//

