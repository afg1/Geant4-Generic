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
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent* )
{
    
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    histogram->Fill(aStep->GetTrack()->GetPosition(), aStep->GetTotalEnergyDeposit());
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
    histogram->Add(*SDi->histogram);
}


void SensitiveDetector::AddHistogram(G4String)
{
    histogram = new LMHist();// Use default constructor and then set things
}
void SensitiveDetector::SetHistogramDimension(int D)
{
    histogram->SetDimension(D);
}
void SensitiveDetector::SetHistogramMax3(G4ThreeVector Ma3)
{
    histogram->SetMax3(Ma3);
}
void SensitiveDetector::SetHistogramMin3(G4ThreeVector Mi3)
{
    histogram->SetMin3(Mi3);
}
void SensitiveDetector::SetHistogramMax2(G4double Ma2)
{
    histogram->SetMax2(Ma2);
}
void SensitiveDetector::SetHistogramMin2(G4double Mi2)
{
    histogram->SetMin2(Mi2);
}
void SensitiveDetector::SetHistogramMax1(G4double Ma1)
{
    histogram->SetMax1(Ma1);
}
void SensitiveDetector::SetHistogramMin1(G4double Mi1)
{
    histogram->SetMin1(Mi1);
}

void SensitiveDetector::SetHistogramAxis(G4String ax)
{
    histogram->SetAxis(ax);
}

void SensitiveDetector::SetHistogramBins1D(int B1)
{
    histogram->SetBins1(B1);
}

void SensitiveDetector::SetHistogramBins2D(int B2)
{
    histogram->SetBins2(B2);
}

void SensitiveDetector::SetHistogramBins3D(G4ThreeVector B3)
{
    histogram->SetBins3(B3.x(), B3.y(), B3.z());
}

void SensitiveDetector::SetHistogramCentre(G4ThreeVector C)
{
    histogram->SetCentre(C);
}

void SensitiveDetector::FinalizeHist()
{
    histogram->Finalize();
}








