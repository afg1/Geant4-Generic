/*
 This class is the concrete implementation of a hit, which is the way Geant4 stored its data, this implementation stores data about protons which stopped in whatever volume the sensitive
 detector is attached to, in this case, the water phantom
*/
#ifndef HIT_H
#define HIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class WaterHit : public G4VHit
{
    public:
        WaterHit();
        ~WaterHit();
        WaterHit(const WaterHit&);
        const WaterHit& operator=(const WaterHit&);
        G4int operator==(const WaterHit&) const;

//        inline void* operator new(size_t);
//        inline void operator delete(void*);

        void Draw();
        void Print();

        void SetEdep(G4double de){edep = de;}
        G4double GetEdep(){return edep;}

        void SetPosition(const G4ThreeVector ipos){pos = ipos;}
        G4ThreeVector GetPosition(){return pos;}

        void SetEne(const G4double E){ene = E;}
        G4double GetEne(){return ene;}
    
        void SetTrackID(G4int T){TrackID = T;}
        G4int GetTrackID(){return TrackID;}
    
        void SetPlaneID(G4int P){planeID = P;}
        G4int GetPlaneID(){return planeID;}
    
        void SetVelocity(G4ThreeVector v){vel = v;}
        G4ThreeVector GetVelocity(){return vel;}

    private:
        G4double edep;
        G4ThreeVector pos;
        G4ThreeVector vel;
        G4double ene;
        G4int planeID;
        G4int TrackID;

};

typedef G4THitsCollection<WaterHit> G4HitCollection;// Used in SensitiveDetector.cc to make a hit collection with the right type of hit

#endif
