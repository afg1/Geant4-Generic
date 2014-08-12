#ifndef GEOMETRY_MESSENGER_H
#define GEOMETRY_MESSENGER_H 1

#include "globals.hh"
#include "G4UImessenger.hh"

class World;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
//class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWith3VectorAndUnit;

class GeometryMessenger: public G4UImessenger
{
    public:
        GeometryMessenger(World* );
        ~GeometryMessenger();
    
        void SetNewValue(G4UIcommand*, G4String);
    
    private:
        World* worldPtr;
    
        G4UIdirectory*  GeomMessDir;
    
        G4UIcmdWith3VectorAndUnit* shiftWater;
    
        G4UIcmdWithADoubleAndUnit* rotateWaterX;
    
        G4UIcmdWithADoubleAndUnit* rotateWaterY;
    
        G4UIcmdWithADoubleAndUnit* rotateWaterZ;
    
        G4UIcmdWithAString* addHistogram;
    
    
        G4UIcmdWithoutParameter* updateGeom;
    
};

#endif
