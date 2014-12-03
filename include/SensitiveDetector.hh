/*
This class implements the sensitive detector, which also handles file output
*/
#ifndef SENSITIVE_DETECTOR_H
#define SENSITIVE_DETECTOR_H

#include "G4VSensitiveDetector.hh"
#include "Hit.hh"
#include <string>

#include "Histogramming.hh"
#include "SDMessenger.hh"

class SDMessenger;
class G4Step;

class SensitiveDetector : public G4VSensitiveDetector
{
    public:
        SensitiveDetector(G4String, G4String HCname);
        ~SensitiveDetector();

        void Initialize(G4HCofThisEvent*);
        G4bool ProcessHits(G4Step*, G4TouchableHistory*);
        void EndOfEvent(G4HCofThisEvent*);
        void WriteData(G4String);//double D, double bp);
        void Merge(SensitiveDetector* SDi);
    
        void AddHistogram(G4String);
        void SetHistogramDimension(int);
        void SetHistogramMax3(G4ThreeVector);
        void SetHistogramMin3(G4ThreeVector);
        void SetHistogramMax2(G4double);
        void SetHistogramMin2(G4double);
        void SetHistogramMax1(G4double);
        void SetHistogramMin1(G4double);
    
        void SetHistogramAxis(G4String);
        void SetHistogramBins1D(int);
        void SetHistogramBins2D(int);
        void SetHistogramBins3D(G4ThreeVector);
        void SetHistogramCentre(G4ThreeVector);
        void SetHistogramName(G4String);
        void SetHistogramType(G4int t){type = t;}
    
//        void FinalizeHist();
    
    private:
        G4HitCollection* collection;
        std::vector<Histogram*> multiHist;
        Histogram* histogram;
        SDMessenger* SDM;
    
    private:
        // Variables considered volatile - used to add histograms
        G4ThreeVector bins;
        G4ThreeVector ext;
        G4ThreeVector ext_max;
        G4ThreeVector ext_min;
        G4ThreeVector centre;
        G4String hist_name;
        double max2;
        double min2;
        double max1;
        double min1;
        short int dim;
        int type;
        int bins1;
        int bins2;
    
        short int bindim1;
        short int bindim2;
    
        double binwidth;
    
    
        
        


};

#endif
