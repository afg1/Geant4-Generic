#include "SDMessenger.hh"
#include "globals.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"

SDMessenger::SDMessenger(SensitiveDetector* SD): SDPtr(SD)
{
    SDMessDir = new G4UIdirectory("/SDMessenger/");
    SDMessDir->SetGuidance("Messenger for the SD.");
    
    addHist = new G4UIcmdWithAString("/SDMessenger/addHist", this);
    addHist->SetGuidance("Adds a histogram of your specified name");
    
    setHistDim = new G4UIcmdWithAnInteger("/SDMessenger/setHistDim", this);
    setHistDim->SetGuidance("Specify the dimensionality of the histogram, 1, 2 or 3D. Must have already created a histogram.");
    
    setMax3 = new G4UIcmdWith3VectorAndUnit("/SDMessenger/setMax3", this);
    setMax3->SetGuidance("Specify the maximum extent in 3D for the histogram. Only used for 3D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMin3 ");

    setMin3 = new G4UIcmdWith3VectorAndUnit("/SDMessenger/setMin3", this);
    setMin3->SetGuidance("Specify the maximum extent in 3D for the histogram. Only used for 3D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMax3 ");
    
    setMax2 = new G4UIcmdWithADoubleAndUnit("/SDMessenger/setMax2", this);
    setMax2->SetGuidance("Specify the maximum extent in 2D for the histogram. Only used for 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMin2 ");
    
    setMin2 = new G4UIcmdWithADoubleAndUnit("/SDMessenger/setMin2", this);
    setMin2->SetGuidance("Specify the maximum extent in 2D for the histogram. Only used for 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMax2 ");
    
    setMax1 = new G4UIcmdWithADoubleAndUnit("/SDMessenger/setMax1", this);
    setMax1->SetGuidance("Specify the maximum extent in 1D for the histogram. Used for 1D and 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMin1 ");
    
    setMin1 = new G4UIcmdWithADoubleAndUnit("/SDMessenger/setMin1", this);
    setMin1->SetGuidance("Specify the maximum extent in 1D for the histogram. Used for 1D and 2D, will be ignored otherwise. Use in conjunction with /SDMessenger/setMax1 ");
    
    setCentre = new G4UIcmdWith3VectorAndUnit("/SDMessenger/setCentre", this);
    setCentre->SetGuidance("Specify the centre of the histogram. Optional, (0,0,0) will be used if not specified");
    
    setBins1D = new G4UIcmdWithAnInteger("/SDMessenger/setBins1D", this);
    setBins1D->SetGuidance("Specify the binning in 1D. Used for 1&2D histograms, ignored in 3D");
    
    setBins2D = new G4UIcmdWithAnInteger("/SDMessenger/setBins2D", this);
    setBins2D->SetGuidance("Specify the binning in 2D. Used in conjunction with /SDMessenger/setBins1D for 2D histograms only.");
    
    setBins3D = new G4UIcmdWith3Vector("/SDMessenger/setBins3D", this);
    setBins3D->SetGuidance("Specify the binning in 3D as x,y,z integers. Only used for 3D histograms");
    
    setAxis = new G4UIcmdWithAString("/SDMessenger/setAxis", this);
    setAxis->SetGuidance("Specify the axis to histogram in. Only applicable to 1 and 2D histograms");
    
    setType = new G4UIcmdWithAnInteger("/SDMessenger/setType", this);
    setType->SetGuidance("Specify the binning type. 0 for depth-dose, 1 for LET, 2 for penumbra-dose and 3 for penumbra-LET");
    
    writeData = new G4UIcmdWithAString("/SDMessenger/writeData", this);
    writeData->SetGuidance("Writes out the SD tracking data to wherever you tell it to");
    
    finalize = new G4UIcmdWithoutParameter("/SDMessenger/finalize", this);
    finalize->SetGuidance("Locks the histogram and makes sure everything is ready, call just before beamOn");
}

SDMessenger::~SDMessenger()
{
    delete SDMessDir;
    delete addHist;
   
}

void SDMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
    if(cmd == addHist)
    {
        if(!dimSet)
        {
            G4Exception("SDMessenger", "DIM01", FatalErrorInArgument , "Must Set dimension before adding histogram.");
        }
        else if(!(max3Set || (max2Set && dim == 2 ) || (max1Set && dim == 1) ))
        {
            G4Exception("SDMessenger", "MAX", FatalErrorInArgument , "Must set Extents before adding histogram.");
        }
        else if(!(min3Set || (min2Set && dim == 2 ) || (min1Set && dim == 1) ))
        {
            G4Exception("SDMessenger", "MIN", FatalErrorInArgument , "Must set Extents before adding histogram.");
        }
        else if(!centreSet)
        {
            G4Exception("SDMessenger", "CENTER", FatalErrorInArgument , "Must set Centre before adding histogram.");
        }
        else if((!bins1DSet) && dim == 1)
        {
            G4Exception("SDMessenger", "BINS1D", FatalErrorInArgument , "Must set Bins before adding histogram.");
        }
        else if((!bins2DSet) && dim == 2)
        {
            G4Exception("SDMessenger", "BINS2D", FatalErrorInArgument , "Must set Bins before adding histogram.");
        }
        else if((!bins3DSet) && dim == 3)
        {
            G4Exception("SDMessenger", "BINS3D", FatalErrorInArgument , "Must set Bins before adding histogram.");
        }
        else if(!axisSet)
        {
            G4Exception("SDMessenger", "AXIS", FatalErrorInArgument , "Must set Axis before adding histogram.");
        }
        
        SDPtr->AddHistogram();// Only get here if everything went well!
    }
    
    if(cmd == setHistDim)
    {
        SDPtr->SetHistogramDimension(setHistDim->GetNewIntValue(newValue));
        dim = setHistDim->GetNewIntValue(newValue);
        dimSet = true;
    }
    
    if(cmd == setMax3)
    {
            SDPtr->SetHistogramMax3(setMax3->GetNew3VectorValue(newValue));
            max3Set = true;
    }
    
    if(cmd == setMin3)
    {
        SDPtr->SetHistogramMin3(setMin3->GetNew3VectorValue(newValue));
        min3Set = true;
    }
    
    if(cmd == setMax2)
    {
        SDPtr->SetHistogramMax2(setMax2->GetNewDoubleValue(newValue));
        max2Set = true;
    }
    
    if(cmd == setMin2)
    {
        SDPtr->SetHistogramMin2(setMin2->GetNewDoubleValue(newValue));
        min2Set = true;
    }
    
    if(cmd == setMax1)
    {
        SDPtr->SetHistogramMax1(setMax1->GetNewDoubleValue(newValue));
        max1Set = true;
    }
    
    if(cmd == setMin1)
    {
        SDPtr->SetHistogramMin1(setMin1->GetNewDoubleValue(newValue));
        min1Set = true;
    }
    
    if(cmd == setCentre)
    {
        SDPtr->SetHistogramCentre(setCentre->GetNew3VectorValue(newValue));
        centreSet = true;
    }
    
    if(cmd == setBins1D)
    {
        SDPtr->SetHistogramBins1D(setBins1D->GetNewIntValue(newValue));
        bins1DSet = true;
    }
    
    if(cmd == setBins2D)
    {
        SDPtr->SetHistogramBins2D(setBins2D->GetNewIntValue(newValue));
        bins2DSet = true;
    }
    
    if(cmd == setBins3D)
    {
        SDPtr->SetHistogramBins3D(setBins3D->GetNew3VectorValue(newValue));
        bins3DSet = true;
    }
    
    if(cmd == setAxis)
    {
        SDPtr->SetHistogramAxis(newValue);
        axisSet = true;
    }
    
    if(cmd == setType)
    {
        SDPtr->SetHistogramType(setType->GetNewIntValue(newValue));
        axisSet = true;
    }
    
    if(cmd == writeData)
    {
        SDPtr->WriteData(newValue);
    }
    
//    if(cmd == finalize)
//    {
//        if(histexists)
//        {
//            SDPtr->FinalizeHist();
//        }
//    }
}
