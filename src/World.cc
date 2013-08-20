#include "World.hh"
#include "G4RunManager.hh"
#include "G4RegionStore.hh"
#include "GeometryMessenger.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include <cmath>
#include <utility>

World::World(std::string out) : outloc(out)
{
    worldSize = 100.0*cm;
    
    planeThickness = 15.0*cm;
    planeWidth = 15.0*cm;
    planeHeight = 15.0*cm;

    nistMan = G4NistManager::Instance();
    sdMan = G4SDManager::GetSDMpointer();
    
    VAC = nistMan->FindOrBuildMaterial("G4_Galactic");
    H2O = nistMan->FindOrBuildMaterial("G4_WATER");
    geomMess = new GeometryMessenger(this);
    
    worldLog = NULL;
    
    
}

World::~World()
{
    SD1->WriteData(20*cm);
    delete worldBox;
    delete planeBox;
    delete theWater;
    delete VAC;
    delete H2O;
//    delete SD;
}


G4VPhysicalVolume* World::Construct()
{

    G4cout << "Building the shapes..." << G4endl;
    worldBox = new G4Box("World", worldSize, worldSize, worldSize);
    planeBox = new G4Box("Plane", planeWidth, 10*um, planeThickness);
    outerplaneBox = new G4Box("OuterPlane", 2*planeWidth, 10*um,  2*planeThickness);
    
    theWater = new G4EllipticalTube("Water", 44*cm, 23*cm, 20*cm);

    worldLog = new G4LogicalVolume(worldBox, VAC, "WorldLog");
    worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldPhys", 0, false, 0);
    
    waterLog = new G4LogicalVolume(theWater, H2O, "WaterLog");
    waterPhys = new G4PVPlacement(0, waterCentre, waterLog, "WaterPhys", worldLog, false, 0);
    
    plane1Log = new G4LogicalVolume(planeBox, VAC, "planeLog1");
    plane1Phys = new G4PVPlacement(0, G4ThreeVector(0, 40*cm, 0), plane1Log, "plane1Phys", worldLog, false, 0);
    
    plane2Log = new G4LogicalVolume(planeBox, VAC, "planeLog2");
    plane2Phys = new G4PVPlacement(0, G4ThreeVector(0, -40*cm, 0), plane2Log, "plane2Phys", worldLog, false, 0);
    
    plane3Log = new G4LogicalVolume(planeBox, VAC, "planeLog3");
    plane3Phys = new G4PVPlacement(0, G4ThreeVector(0, -60*cm, 0), plane3Log, "plane3Phys", worldLog, false, 0);
    
    SD1 = new SensitiveDetector("SD1", outloc, "WaterHits1");


    sdMan->AddNewDetector(SD1);


    plane1Log->SetSensitiveDetector(SD1);
    plane2Log->SetSensitiveDetector(SD1);
    plane3Log->SetSensitiveDetector(SD1);
    
    
    return worldPhys;
//    return ConstructForReconstruct();
}


G4VPhysicalVolume* World::ConstructForReconstruct()
{
    G4cout << "Reconstruct called..." <<G4endl;
    if(!waterPhys)
    {
        delete waterLog;
        delete waterPhys;
    }


    G4cout << "Reconstruct called, about to instantiate the world..." << G4endl;
    worldLog = new G4LogicalVolume(worldBox, VAC, "WorldLog");
    worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldPhys", 0, false, 0);

    G4cout << "Reconstruct called, about to instantiate the water..." << G4endl;
    waterLog = new G4LogicalVolume(theWater, H2O, "WaterLog");
    waterPhys = new G4PVPlacement(0, waterCentre, waterLog, "WaterPhys", worldLog, false, 0);
    
    G4cout << "Reconstruct called, about to instantiate plane1..." << G4endl;
    plane1Log = new G4LogicalVolume(planeBox, VAC, "planeLog1");
    plane1Phys = new G4PVPlacement(0, G4ThreeVector(0, 50*cm, 0), plane1Log, "plane1Phys", worldLog, false, 0);
    
    G4cout << "Reconstruct called, about to instantiate plane2..." << G4endl;
    plane2Log = new G4LogicalVolume(planeBox, VAC, "planeLog2");
    plane2Phys = new G4PVPlacement(0, G4ThreeVector(0, -50*cm, 0), plane2Log, "plane2Phys", worldLog, false, 0);
    
    G4cout << "Reconstruct called, about to instantiate plane3..." << G4endl;
    plane3Log = new G4LogicalVolume(planeBox, VAC, "planeLog3");
    plane3Phys = new G4PVPlacement(0, G4ThreeVector(0, -60*cm, 0), plane3Log, "plane3Phys", worldLog, false, 0);
    
    G4cout << "Reconstruct called, about to test SD1..." << G4endl;
    if(!SD1)
    {
        G4cout << "SD1 being constructed" << G4endl;
        SD1 = new SensitiveDetector("SD1", outloc, "WaterHits1");
        sdMan->AddNewDetector(SD1);
    }
    
    G4cout << "Reconstruct called, about to attach detectors..." << G4endl;
    plane1Log->SetSensitiveDetector(SD1);
    plane2Log->SetSensitiveDetector(SD1);
    plane3Log->SetSensitiveDetector(SD1);
    
    G4cout << "worldPhys = " << worldPhys << G4endl;
    
    G4cout << worldPhys->GetLogicalVolume()->GetName() << G4endl;
    return worldPhys;
}

void World::UpdateGeometry()
{
    G4cout << "Updating Geometry..." << G4endl;
//    G4GeometryManager::GetInstance()->OpenGeometry();
//
//    G4PhysicalVolumeStore::GetInstance()->Clean();
//    G4LogicalVolumeStore::GetInstance()->Clean();
//    G4SolidStore::GetInstance()->Clean();
    
    G4cout << "Geometry cleaned..." << G4endl;
  
    ConstructForReconstruct();
    G4cout << "Reconstruct returned okay" << G4endl;
    G4RunManager::GetRunManager()->DefineWorldVolume(worldPhys);
    G4cout << "After the runmanager line..." << G4endl;
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4cout << "After the physics modified line" << G4endl;
    G4RegionStore::GetInstance()->UpdateMaterialList(worldPhys);
    
    G4cout << "Geometry Updated!" << G4endl;
}

void World::SetCentre(G4ThreeVector newCentre)
{
    waterCentre = newCentre;
}
