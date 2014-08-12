#include "G4SDManager.hh"
#include "Run.hh"


Run::Run()
{
    SD = (SensitiveDetector*)G4SDManager::GetSDMpointer()->FindSensitiveDetector("MainDetector");

}

Run::~Run()
{

}

void Run::RecordEvent(const G4Event* evt)
{
    G4Run::RecordEvent(evt);
}

void Run::Merge(const G4Run* aRun)
{
    const Run* localRun = static_cast<const Run*>(aRun);
    SD->Merge(localRun->GetSD());
    G4Run::Merge(aRun);
}
