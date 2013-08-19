#include "G4RunManager.hh"
#include "G4UIManager.hh"

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


int main(int argc, char** argv)
{
    CommandLineParser* cmdl = new CommandLineParser(argc, argv);
    std::vector<std::string> commands = cmdl->Parse();
    std::string outloc;
    if(commands.size() > 1)
    {
        if(commands[1] == "h")
        {
            G4cout << "A help script for spotsize.cpp" << G4endl;
            G4cout << "Usage:" << G4endl;
            G4cout << "./spot [macname] [ouput location]" << G4endl;
            return 1;
        }
        else
        {
            outloc = commands[2];
            G4cout << outloc << G4endl;
        }
    }
    G4RunManager* runMan = new G4RunManager;
    
    World* theWorld = new World(outloc);
    runMan->SetUserInitialization(theWorld);
    G4cout << "World" << G4endl;
    G4VUserPhysicsList* phys = new Physics();
    runMan->SetUserInitialization(phys);
    G4cout << "Physics" << G4endl;
    G4VUserPrimaryGeneratorAction* gen = new Generator();
    runMan->SetUserAction(gen);
    G4cout << "Generator" << G4endl;
    runMan->Initialize();
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
    
    delete theWorld;
//    delete phys;
//    delete gen;
    return 0;
}