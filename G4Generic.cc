#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "World.hh"
#include "Physics.hh"
#include "Generator.hh"
#include "CommandLineParser.hh"
#include "Initialization.hh"


int main(int argc, char** argv)
{
    CommandLineParser* cmdl = new CommandLineParser(argc, argv);
    std::vector<std::string> commands = cmdl->Parse();
    int Nthreads(2);
    if(commands.size() > 1)
    {
        if(commands[1] == "h")
        {
            G4cout << "A help script for spotsize.cpp" << G4endl;
            G4cout << "Usage:" << G4endl;
            G4cout << argv[0] << " [macname] [Nthreads]" << G4endl;
            return 1;
        }
        else
        {
            Nthreads = std::atoi(commands[2].c_str());
        }
    }
    #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager();
    runManager->SetNumberOfThreads(Nthreads);
    #else
    G4RunManager* runManager = new G4RunManager;
    #endif
    
    World* theWorld = new World();
    runManager->SetUserInitialization(theWorld);
    G4cout << "World" << G4endl;
    G4VUserPhysicsList* phys = new Physics();
    runManager->SetUserInitialization(phys);
    G4cout << "Physics" << G4endl;
    #ifdef G4MULTITHREADED
    Initialization* init = new Initialization();
    runManager->SetUserInitialization(init);
    #else
    G4VUserPrimaryGeneratorAction* gen = new Generator;
    runManager->SetUserAction(gen);
    #endif
    G4cout << "Generator" << G4endl;
    runManager->Initialize();
    G4cout << "Init" << G4endl;
    
    #ifdef G4VIS_USE
    G4VisManager* visMan = new G4VisExecutive;
    visMan->Initialize();
    #endif
    
    #ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    if(argc == 1)// This means we want to run in interactive mode
    {
        ui->SessionStart();
    }
    #endif
    
    if(commands.size() > 1)
    {
        G4cout << "UI" << G4endl;
        G4UImanager* UI = G4UImanager::GetUIpointer();
        UI->ApplyCommand("/control/execute " + commands[1]);//Assumes we have 1 macro to run, and it's the only argument
    }
    G4cout << G4endl;
    
//    delete theWorld;
//    delete phys;
//    delete gen;
    return 0;
}