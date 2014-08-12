#ifndef RUN_HH
#define RUN_HH 1

#include "G4Run.hh"
#include "SensitiveDetector.hh"

class Run : public G4Run
{
    public:
        Run();
        virtual ~Run();
        virtual void RecordEvent(const G4Event*);
        virtual void Merge(const G4Run*);
    
        SensitiveDetector* GetSD() const {return SD;}
    
    private:
        SensitiveDetector* SD;
};
#endif
