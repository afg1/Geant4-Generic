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
#include "GeometryMessenger.hh"


class G4LogicalVolume;
class G4PhysicalVolume;


class World : public G4VUserDetectorConstruction
{
    public:
        World();
        ~World();
        G4VPhysicalVolume* Construct();
        void ConstructSDandField();
    
    
        G4VPhysicalVolume* ConstructForReconstruct();
        void UpdateGeometry();
        void SetCentre(G4ThreeVector);
        void SetRotation(G4RotationMatrix);
        void WriteData(G4String fname){SD1->WriteData(fname);}
    
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
        G4double waterThickness;
        G4double waterWidth;// Dump will be cuboid
        G4double waterHeight;
        G4ThreeVector waterCentre;
        G4RotationMatrix* waterRot;

    
        // Shapes for things
        G4Box* worldBox;
        G4Box* waterBox;
    
        // Materials needed in the spectrometer
        G4Material* VAC;
        G4Material* H2O;
    
        // Utilities...
        G4NistManager* nistMan;
        G4SDManager* sdMan;
        GeometryMessenger* geomMess;

    
        // SD output
        std::string outloc;
        SensitiveDetector* SD1;
};


#endif
