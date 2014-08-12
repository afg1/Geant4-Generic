#include "Run.hh"
#include "RunAction.hh"
#include "G4Threading.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"

RunAction::RunAction()
{
    
}

RunAction::~RunAction()
{

}

G4Run* RunAction::GenerateRun()
{
    return new Run();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    G4UserRunAction::EndOfRunAction(aRun);
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4UserRunAction::BeginOfRunAction(aRun);
}
