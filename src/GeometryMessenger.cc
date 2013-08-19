#include "GeometryMessenger.hh"
#include "World.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

GeometryMessenger::GeometryMessenger(World* theWorld): worldPtr(theWorld)
{
    GeomMessDir = new G4UIdirectory("/geometryMessenger/");
    GeomMessDir->Setguidance("Messenger for my geometry.");
    
    shiftWater = new G4UIcmdWith3VectorAndUnit("/geometryMessenger/shiftWater", this);
    shiftWater->SetGuidance("Move the water block in 3d. Don't forget the unit!");
    
    updateGeom = new G4UIcmdWithoutParameter("/geometryMessenger/update", this);
    updateGeom->SetGuidance("Update the geometry. MUST be called after changing with the commands in this messenger!");
    
}

GeometryMessenger::~GeometryMessenger()
{
    delete updateGeom;
    delete shiftWater;
    delete GeomMessDir;
}

void GeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
    if(cmd == shiftWater)
    {
        worldPtr->SetCentre(cmd->GetNew3VectorValue(newValue));
    }
    
    if(cmd == updateGeom)
    {
        worldPtr->UpdateGeometry();
    }
}