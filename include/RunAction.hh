#ifndef RUNACTION_HH
#define RUNACTION_HH 1

#include "G4UserRunAction.hh"
#include "SensitiveDetector.hh"
//#include <string>

class RunAction : public G4UserRunAction
{
    public:
        RunAction();
        ~RunAction();
        G4Run* GenerateRun();
        void BeginOfRunAction(const G4Run*);
        void EndOfRunAction(const G4Run*);
    private:

};

#endif