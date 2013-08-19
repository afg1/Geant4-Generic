#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Hit.hh"
#include "G4ThreeVector.hh"

#include <fstream>
#include <string>
#include "G4SDManager.hh"
#include <iomanip>
#include <cmath>


SensitiveDetector::SensitiveDetector(G4String name, std::string out, G4String HCname) : G4VSensitiveDetector(name), outloc(out){
    collectionName.insert(HCname);
    dose = 0;
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{
    collection = new G4HitCollection(SensitiveDetectorName, collectionName[0]);
    static G4int HCID = -1;
    if(HCID < 0)
    {
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    HCE->AddHitsCollection(HCID, collection);
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    if(aStep->GetTrack()->GetParentID() == 0)
    {
        G4double edep = aStep->GetTotalEnergyDeposit();
        G4ThreeVector pos =  aStep->GetTrack()->GetPosition();
        G4double E = aStep->GetTrack()->GetKineticEnergy();
        WaterHit* newHit = new WaterHit();
        newHit->SetPosition(pos);
        newHit->SetEdep(edep);
        newHit->SetEne(E);
        collection->insert(newHit);
        dose += newHit->GetEdep();
    }
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* CHC)
{
    int id(-1);
    id = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    G4HitsCollection* HC = 0;
    G4ThreeVector pos;
    G4double E(0);
    HC = (G4HitsCollection*)CHC->GetHC(id);
    int n_hits(0);
    n_hits = HC->GetSize();
    
    for(int i=0; i< n_hits; i++)
    {
        
        WaterHit* hit = (WaterHit*)HC->GetHit(i);
        pos = hit->GetPosition();
        E = hit->GetEne();

        x.push_back(pos[0]);
        y.push_back(pos[1]);
        z.push_back(pos[2]);
        Es.push_back(E);

    }
}

void SensitiveDetector::WriteData(double D)
{
    G4double outdata[4] = {0.0, 0.0, 0.0, 0.0};
    // Write out the hits to a binary file

    std::ofstream output;
    if(fexists(outloc.c_str()))
    {
        output.open(outloc.c_str(), std::ios::app|std::ios::binary);
    }
    else
    {
        output.open(outloc.c_str(), std::ios::binary);
        output.write((char*)&D, sizeof(D));
        output.write((char*)&dose, sizeof(dose));
    }
    if(output.is_open())
    {
        for(size_t n=0; n<x.size(); n++)
        {
            outdata[0] = x[n];
            outdata[1] = y[n];
            outdata[2] = z[n];
            outdata[3] = Es[n];
            output.write((char*)&outdata, sizeof(outdata));
        }
    }
}

        


bool SensitiveDetector::fexists(const char* fname)// Handy function I wrote to check for the existence of the output file
{
    std::ifstream ifile(fname);
    return ifile;
}
