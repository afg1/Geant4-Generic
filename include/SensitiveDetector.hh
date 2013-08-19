/*
This class implements the sensitive detector, which also handles file output
*/
#ifndef SENSITIVE_DETECTOR_H
#define SENSITIVE_DETECTOR_H

#include "G4VSensitiveDetector.hh"
#include "Hit.hh"
#include <string>

class G4Step;

class SensitiveDetector : public G4VSensitiveDetector
{
    public:
        SensitiveDetector(G4String, std::string, G4String HCname);
        ~SensitiveDetector();

        void Initialize(G4HCofThisEvent*);
        G4bool ProcessHits(G4Step*, G4TouchableHistory*);
        void EndOfEvent(G4HCofThisEvent*);
        void WriteData(double D);
    private:
        G4HitCollection* collection;
        std::string outloc;
        int selflag;
        bool fexists(const char* fname);
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> z;
        std::vector<double> Es;
        double dose;
        
        


};

#endif
