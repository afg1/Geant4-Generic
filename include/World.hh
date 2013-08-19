#ifndef WORLD_SPEC_H
#define WORLD_SPEC_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4EllipticalTube.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include <string>

#include "SensitiveDetector.hh"


class G4LogicalVolume;
class G4PhysicalVolume;

class World : public G4VUserDetectorConstruction
{
    public:
        World(std::string);
        ~World();
        G4VPhysicalVolume* Construct();
        
    
    private:
        // A load of volumes I'll need...
        G4LogicalVolume* worldLog;
        G4VPhysicalVolume* worldPhys;// The world volumes
    
        G4LogicalVolume* waterLog;
        G4VPhysicalVolume* waterPhys;
    
        G4LogicalVolume* plane1Log;
        G4VPhysicalVolume* plane1Phys;
    
        G4LogicalVolume* plane2Log;
        G4VPhysicalVolume* plane2Phys;
    
        G4LogicalVolume* plane3Log;
        G4VPhysicalVolume* plane3Phys;

//        G4LogicalVolume* plane4Log;
//        G4VPhysicalVolume* plane4Phys;
//    
//        G4LogicalVolume* plane5Log;
//        G4VPhysicalVolume* plane5Phys;
//    
//        G4LogicalVolume* plane6Log;
//        G4VPhysicalVolume* plane6Phys;
//    
//        G4LogicalVolume* plane7Log;
//        G4VPhysicalVolume* plane7Phys;
    
        G4double worldSize;// Assume cube
        G4double planeThickness;
        G4double planeWidth;// Dump will be cuboid
        G4double planeHeight;
        G4ThreeVector waterCentre;

    
        // Shapes for things
        G4Box* worldBox;
        G4Box* planeBox;
        G4Box* outerplaneBox;
        G4EllipticalTube* theWater;
    
        // Materials needed in the spectrometer
        G4Material* VAC;
        G4Material* H2O;
    
        // Utilities...
        G4NistManager* nistMan;
        G4SDManager* sdMan;
    
        void UpdateGeometry();
        void SetCentre(G4ThreeVector);
    
        // SD output
        std::string outloc;
        SensitiveDetector* SD1;
};


#endif
