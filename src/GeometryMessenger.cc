#include "GeometryMessenger.hh"
#include "World.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

GeometryMessenger::GeometryMessenger(World* theWorld): worldPtr(theWorld)
{
    GeomMessDir = new G4UIdirectory("/geometryMessenger/");
    GeomMessDir->SetGuidance("Messenger for the geometry.");
    
    shiftWater = new G4UIcmdWith3VectorAndUnit("/geometryMessenger/shiftWater", this);
    shiftWater->SetGuidance("Move the water block in 3d. Don't forget the unit!");
    
    rotateWaterX = new G4UIcmdWithADoubleAndUnit("/geometryMessenger/rotateWaterX", this);
    rotateWaterX->SetGuidance("Rotate the water block in X. Don't forget the unit!");
    
    rotateWaterY = new G4UIcmdWithADoubleAndUnit("/geometryMessenger/rotateWaterY", this);
    rotateWaterY->SetGuidance("Rotate the water block in Y. Don't forget the unit!");
    
    rotateWaterZ = new G4UIcmdWithADoubleAndUnit("/geometryMessenger/rotateWaterZ", this);
    rotateWaterZ->SetGuidance("Rotate the water block in Z. Don't forget the unit!");
    
    updateGeom = new G4UIcmdWithoutParameter("/geometryMessenger/update", this);
    updateGeom->SetGuidance("Update the geometry. MUST be called after changing with the commands in this messenger!");
    
}

GeometryMessenger::~GeometryMessenger()
{
    delete updateGeom;
    delete shiftWater;
    delete rotateWaterX;
    delete rotateWaterY;
    delete rotateWaterZ;
    delete GeomMessDir;
}

void GeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
    if(cmd == shiftWater)
    {
        worldPtr->SetCentre(shiftWater->GetNew3VectorValue(newValue));
    }
    
    if(cmd == updateGeom)
    {
        worldPtr->UpdateGeometry();
    }
    
    if(cmd == rotateWaterX)
    {
        CLHEP::HepRotationX Xr(rotateWaterX->GetNewDoubleValue(newValue));
        worldPtr->SetRotation(Xr);
    }
    
    if(cmd == rotateWaterY)
    {
        CLHEP::HepRotationY Yr(rotateWaterY->GetNewDoubleValue(newValue));
        worldPtr->SetRotation(Yr);
    }
    
    if(cmd == rotateWaterZ)
    {
        CLHEP::HepRotationZ Zr(rotateWaterZ->GetNewDoubleValue(newValue));
        worldPtr->SetRotation(Zr);
    }
}
