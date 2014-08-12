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
        SDPtr->AddHistogram(newValue);
        histexists = true;
    }
    
    if(cmd == setHistDim)
    {
        if(histexists)
        {
            SDPtr->SetHistogramDimension(setHistDim->GetNewIntValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "DIM01", FatalErrorInArgument , "Must create histogram before assigning dimensions!");
        }
    }
    
    if(cmd == setMax3)
    {
        if(histexists)
        {
            SDPtr->SetHistogramMax3(setMax3->GetNew3VectorValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MAX3", FatalErrorInArgument , "Must create histogram before assigning maximum!");
        }
    }
    
    if(cmd == setMin3)
    {
        if(histexists)
        {
            SDPtr->SetHistogramMin3(setMin3->GetNew3VectorValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MIN3", FatalErrorInArgument , "Must create histogram before assigning minimum!");
        }
    }
    
    if(cmd == setMax2)
    {
        if(histexists)
        {
            SDPtr->SetHistogramMax2(setMax2->GetNewDoubleValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MAX2", FatalErrorInArgument , "Must create histogram before assigning maximum!");
        }
    }
    
    if(cmd == setMin2)
    {
        if(histexists)
        {
            SDPtr->SetHistogramMin2(setMin2->GetNewDoubleValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MIN3", FatalErrorInArgument , "Must create histogram before assigning minimum!");
        }
    }
    
    if(cmd == setMax1)
    {
        if(histexists)
        {
            SDPtr->SetHistogramMax1(setMax1->GetNewDoubleValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MAX1", FatalErrorInArgument , "Must create histogram before assigning maximum!");
        }
    }
    
    if(cmd == setMin1)
    {
        if(histexists)
        {
            SDPtr->SetHistogramMin1(setMin1->GetNewDoubleValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MIN1", FatalErrorInArgument , "Must create histogram before assigning minimum!");
        }
    }
    
    if(cmd == setCentre)
    {
        if(histexists)
        {
            SDPtr->SetHistogramCentre(setCentre->GetNew3VectorValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "MIN1", FatalErrorInArgument , "Must create histogram before assigning minimum!");
        }
    }
    
    if(cmd == setBins1D)
    {
        if(histexists)
        {
            SDPtr->SetHistogramBins1D(setBins1D->GetNewIntValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "BINS1", FatalErrorInArgument , "Must create histogram before assigning bins!");
        }
    }
    
    if(cmd == setBins2D)
    {
        if(histexists)
        {
            SDPtr->SetHistogramBins2D(setBins2D->GetNewIntValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "BINS2", FatalErrorInArgument , "Must create histogram before assigning bins!");
        }
    }
    
    if(cmd == setBins3D)
    {
        if(histexists)
        {
            SDPtr->SetHistogramBins3D(setBins3D->GetNew3VectorValue(newValue));
        }
        else
        {
            G4Exception("SDMessenger", "BINS3", FatalErrorInArgument , "Must create histogram before assigning bins!");
        }
    }
    
    if(cmd == setAxis)
    {
        if(histexists)
        {
            SDPtr->SetHistogramAxis(newValue);
        }
        else
        {
            G4Exception("SDMessenger", "AXIS1", FatalErrorInArgument , "Must create histogram before assigning axis!");
        }
    }
    
    if(cmd == writeData)
    {
        if(histexists)
        {
            SDPtr->WriteData(newValue);
        }
    }
    
    if(cmd == finalize)
    {
        if(histexists)
        {
            SDPtr->FinalizeHist();
        }
    }
}
