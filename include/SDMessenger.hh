#ifndef SD_MESSENGER_H
#define SD_MESSENGER_H 1

#include "globals.hh"
#include "G4UImessenger.hh"

#include "SensitiveDetector.hh"
#include "SDMessenger.hh"

class SensitiveDetector;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;

#include <vector>


class SDMessenger: public G4UImessenger
{
    public:
        SDMessenger(SensitiveDetector* );
        ~SDMessenger();
    
        void SetNewValue(G4UIcommand*, G4String);
    
    private:
        SensitiveDetector* SDPtr;
        G4UIdirectory* SDMessDir;
    
        G4UIcmdWithAString* addHist;
    
        G4UIcmdWithAnInteger* setHistDim;// Set 1 2 or 3D
    
        G4UIcmdWith3VectorAndUnit* setMax3;
    
        G4UIcmdWith3VectorAndUnit* setMin3;
    
        G4UIcmdWithADoubleAndUnit* setMax2;
    
        G4UIcmdWithADoubleAndUnit* setMin2;
    
        G4UIcmdWithADoubleAndUnit* setMax1;
    
        G4UIcmdWithADoubleAndUnit* setMin1;
    
        G4UIcmdWith3VectorAndUnit* setCentre;
    
        G4UIcmdWithAnInteger* setBins1D;
    
        G4UIcmdWithAnInteger* setBins2D;
    
        G4UIcmdWith3Vector* setBins3D;
    
        G4UIcmdWithAString* setAxis;
    
        G4UIcmdWithAString* writeData;
    
        G4UIcmdWithoutParameter* finalize;
    
        G4UIcmdWithAnInteger* setType;
    
        int dim;
    
        bool dimSet;
        bool max3Set;
        bool max2Set;
        bool max1Set;
        bool min3Set;
        bool min2Set;
        bool min1Set;
        bool centreSet;
        bool bins1DSet;
        bool bins2DSet;
        bool bins3DSet;
        bool axisSet;
    
};

#endif
