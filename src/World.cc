#include "World.hh"
#include "G4RunManager.hh"
#include "G4RegionStore.hh"
#include "GeometryMessenger.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"

#include <cmath>
#include <utility>

World::World()
{
    worldSize = 100.0*cm;
    
    waterThickness = 60.0*cm;
    waterWidth = 60.0*cm;
    waterHeight = 60.0*cm;

    nistMan = G4NistManager::Instance();
    sdMan = G4SDManager::GetSDMpointer();
    
    VAC = nistMan->FindOrBuildMaterial("G4_Galactic");
    H2O = nistMan->FindOrBuildMaterial("G4_WATER");
    geomMess = new GeometryMessenger(this);
    
    worldLog = NULL;
    
    
}

World::~World()
{
    G4ThreeVector temp = plane3Phys->GetTranslation() + plane2Phys->GetTranslation();
    delete worldBox;
    delete waterBox;
    delete VAC;
    delete H2O;
//    delete SD;
}


G4VPhysicalVolume* World::Construct()
{

    worldBox = new G4Box("World", worldSize, worldSize, worldSize);
    

    worldLog = new G4LogicalVolume(worldBox, VAC, "WorldLog");
    worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldPhys", 0, false, 0);
    
    
    waterBox = new G4Box("Water", waterThickness, waterWidth, waterHeight);
    waterLog = new G4LogicalVolume(waterBox, H2O, "WaterLog");
    waterRot = new G4RotationMatrix();
    waterPhys = new G4PVPlacement(waterRot, waterCentre, waterLog, "waterPhys", worldLog, 0, false, 0);
    
    
    
    return worldPhys;
//    return ConstructForReconstruct();
}

void World::ConstructSDandField()
{
    G4String name = "MainDetector";
    SensitiveDetector* SD = new SensitiveDetector(name, outloc);
    SetSensitiveDetector(waterLog, SD);
}


G4VPhysicalVolume* World::ConstructForReconstruct()
{
    delete worldLog;
    delete worldPhys;
    delete waterBox;
    delete waterLog;
    delete waterPhys;

    worldLog = new G4LogicalVolume(worldBox, VAC, "WorldLog");
    worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldPhys", 0, false, 0);
    
    
    waterBox = new G4Box("Water", waterThickness, waterWidth, waterHeight);
    waterLog = new G4LogicalVolume(waterBox, H2O, "WaterLog");
    waterPhys = new G4PVPlacement(waterRot, waterCentre, waterLog, "waterPhys", worldLog, 0, false, 0);
    
    return worldPhys;
}

void World::UpdateGeometry()
{
//    G4GeometryManager::GetInstance()->OpenGeometry();
//
//    G4PhysicalVolumeStore::GetInstance()->Clean();
//    G4LogicalVolumeStore::GetInstance()->Clean();
//    G4SolidStore::GetInstance()->Clean();
    
  
    ConstructForReconstruct();
    G4RunManager::GetRunManager()->DefineWorldVolume(worldPhys);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4RegionStore::GetInstance()->UpdateMaterialList(worldPhys);
    G4cout << "Geometry Updated!" << G4endl;
}

void World::SetCentre(G4ThreeVector newCentre)
{
    waterCentre = newCentre;
}

void World::SetRotation(G4RotationMatrix newRot)
{
    delete waterRot;
    waterRot = new G4RotationMatrix(newRot);
}
