#include "World.hh"
#include "G4RunManager.hh"
#include "G4RegionStore.hh"
#include <cmath>
#include <utility>

World::World(std::string out) : outloc(out)
{
    worldSize = 100.0*cm;
    
    planeThickness = 15.0*cm;
    planeWidth = 15.0*cm;
    planeHeight = 15.0*cm;
    
    worldBox = new G4Box("World", worldSize, worldSize, worldSize);
    planeBox = new G4Box("Plane", planeWidth, 10*um, planeThickness);
    outerplaneBox = new G4Box("OuterPlane", 2*planeWidth, 10*um,  2*planeThickness);
    
    theWater = new G4EllipticalTube("Water", 44*cm, 23*cm, 100*cm);

    
    nistMan = G4NistManager::Instance();
    sdMan = G4SDManager::GetSDMpointer();
    
    VAC = nistMan->FindOrBuildMaterial("G4_Galactic");
    H2O = nistMan->FindOrBuildMaterial("G4_WATER");

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
}

void World::UpdateGeometry()
{
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4RegionStore::GetInstance()->UpdateMaterialList(worldPhys);
}

void World::SetCentre(G4ThreeVector newCentre)
{
    waterCentre = newCentre;
}
