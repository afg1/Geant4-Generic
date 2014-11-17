#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Hit.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <string>
#include "G4SDManager.hh"
#include <iomanip>
#include <cmath>

#include "SDMessenger.hh"


SensitiveDetector::SensitiveDetector(G4String name, G4String HCname) : G4VSensitiveDetector(name)
{
    collectionName.insert(HCname);
    SDM = new SDMessenger(this);
    histogram = NULL;
    type = 0;
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent* )
{
    
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    if(type == 2 || type == 3)// 2 = penumbra, 3 = penumbra-LET
    {
        if(!((abs(aStep->GetTrack()->GetPosition()[2-bindim1] - centre[2-bindim1]) < binwidth) && abs(aStep->GetTrack()->GetPosition()[abs(1-bindim1)] - centre[abs(1-bindim1)]) < binwidth))
        {
            return true;
        }
        if(type == 2)
        {
            histogram->Fill(aStep->GetTrack()->GetPosition(), aStep->GetTotalEnergyDeposit());
            return true;
        }
        else if(type == 3)
        {
            double let = (aStep->GetTotalEnergyDeposit()*MeV)/(aStep->GetStepLength()*um);
//            G4cout << let << G4endl;
            histogram->Fill(aStep->GetTrack()->GetPosition(), let);
        }
    }
    if(type == 0)
    {
        histogram->Fill(aStep->GetTrack()->GetPosition(), aStep->GetTotalEnergyDeposit());
    }
    else if(type == 1)
    {
        double let = aStep->GetTotalEnergyDeposit()/aStep->GetStepLength();
//        G4cout << let << G4endl;
        histogram->Fill(aStep->GetTrack()->GetPosition(), let);
    }
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* )
{

}

void SensitiveDetector::WriteData(G4String fname)//double D, double bp)
{
    histogram->Write(fname);
}

void SensitiveDetector::Merge(SensitiveDetector* SDi)
{
    histogram->Merge(SDi->histogram);
}


void SensitiveDetector::AddHistogram()
{
    if(dim == 1)
    {
        bins = G4ThreeVector();
        bins[bindim1] = bins1;
        
        ext = G4ThreeVector();
        ext[bindim1] = (max1 - min1);
        binwidth = 2.0;
        
        histogram = new Histogram1D(hist_name, centre, ext, bins, dim, type);
        
    }
    else if(dim == 2)
    {
        bins = G4ThreeVector();
        bins[bindim1] = bins1;
        bins[bindim2] = bins2;
        
        ext = G4ThreeVector();
        ext[bindim1] = (max1 - min1);
        ext[bindim2] = (max2 - min2);
        
        histogram = new Histogram2D(hist_name, centre, ext, bins, dim, type);
    }
    else if(dim == 3)
    {
        //  Bins already set!
        
        ext = ext_max - ext_min;
        histogram = new Histogram3D(hist_name, centre, ext, bins, dim, type);
    }
    else
    {
        G4Exception("SensitiveDetector::AddHistogram", "BadDimensionError", FatalErrorInArgument , "Dimension must be either 1, 2 or 3 and must be set");
    }
}
void SensitiveDetector::SetHistogramDimension(int D)
{
    dim = static_cast<short int>(D);
}
void SensitiveDetector::SetHistogramMax3(G4ThreeVector Ma3)
{
    ext_max = Ma3;
}
void SensitiveDetector::SetHistogramMin3(G4ThreeVector Mi3)
{
    ext_min = Mi3;
}
void SensitiveDetector::SetHistogramMax2(G4double Ma2)
{
    max2 = Ma2;
}
void SensitiveDetector::SetHistogramMin2(G4double Mi2)
{
    min2 = Mi2;
}
void SensitiveDetector::SetHistogramMax1(G4double Ma1)
{
    max1 = Ma1;
}
void SensitiveDetector::SetHistogramMin1(G4double Mi1)
{
    min1 = Mi1;
}

void SensitiveDetector::SetHistogramName(G4String N)
{
    hist_name = N;
}

void SensitiveDetector::SetHistogramAxis(G4String ax)
{
    if(!strcmp(ax, "x"))
    {
        bindim1 = 0;
    }
    else if(!strcmp(ax, "y"))
    {
        bindim1 = 1;
    }
    else if(!strcmp(ax, "z"))
    {
        bindim1 = 2;
    }
    else if(!strcmp(ax, "xy"))
    {
        bindim1 = 0;
        bindim2 = 1;
    }
    else if(!strcmp(ax, "yz"))
    {
        bindim1 = 1;
        bindim2 = 2;
    }
    else if(!strcmp(ax, "zx"))
    {
        bindim1 = 2;
        bindim2 = 0;

    }
}

void SensitiveDetector::SetHistogramBins1D(int B1)
{
    bins1 = B1;
    if(bins1 > 1000)
    {
        G4Exception("SensitiveDetector::SetHistogramBins1D", "ExcessiveBinningWarning", JustWarning , "More than 1000 bins is probably a bad idea");
    }
}

void SensitiveDetector::SetHistogramBins2D(int B2)
{
    bins2 = B2;
    if(bins2 > 1000)
    {
        G4Exception("SensitiveDetector::SetHistogramBins2D", "ExcessiveBinningWarning", JustWarning , "More than 1000 bins is probably a bad idea");
    }
}

void SensitiveDetector::SetHistogramBins3D(G4ThreeVector B3)
{
    bins = B3;
    if(bins[0] > 1000 || bins[1] > 1000 || bins[2] > 1000)
    {
        G4Exception("SensitiveDetector::SetHistogramBins2D", "ExcessiveBinningWarning", JustWarning , "More than 1000 bins is probably a bad idea");
    }
}

void SensitiveDetector::SetHistogramCentre(G4ThreeVector C)
{
    centre = C;
    
}

//void SensitiveDetector::FinalizeHist()
//{
//    histogram->Finalize();
//}








