// ********************************************************************
// warwick-legend project
#include "G4Types.hh"

#ifdef G4MULTITHREADED
#    include "G4MTRunManager.hh"
#else
#    include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#    include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#    include "G4UIExecutive.hh"
#endif

// standard
#include <algorithm>
#include <string>

// Geant4
#include "G4GenericBiasingPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4Threading.hh"
#include "G4UImanager.hh"
#include "Shielding.hh"

// us
#include "CLI11.hpp"  // c++17 safe; https://github.com/CLIUtils/CLI11
#include "WLGDActionInitialization.hh"
#include "WLGDDetectorConstruction.hh"

int main(int argc, char** argv)
{
    // command line interface
    CLI::App    app{ "Muon Simulation for Legend" };
    int         nthreads = 4;
    std::string outputFileName("lg.root");
    std::string macroName;

    app.add_option("-m,--macro", macroName, "<Geant4 macro filename> Default: None");
    app.add_option("-o,--outputFile", outputFileName,
                   "<FULL PATH ROOT FILENAME> Default: lg.root");
    app.add_option("-t, --nthreads", nthreads, "<number of threads to use> Default: 4");

    CLI11_PARSE(app, argc, argv);

    // GEANT4 code
    // -- Construct the run manager : MT or sequential one
#ifdef G4MULTITHREADED
    nthreads =
        std::min(nthreads, G4Threading::G4GetNumberOfCores());  // limit thread number to
                                                                // max on machine

    G4MTRunManager* runManager = new G4MTRunManager;
    G4cout << "      ********* Run Manager constructed in MT mode: " << nthreads
           << " threads ***** " << G4endl;
    runManager->SetNumberOfThreads(nthreads);

#else

    G4RunManager* runManager = new G4RunManager;
    G4cout << "      ********** Run Manager constructed in sequential mode ************ "
           << G4endl;

#endif

    // -- Set mandatory initialization classes
    auto detector = new WLGDDetectorConstruction;
    runManager->SetUserInitialization(detector);

    // -- set user physics list
    auto physicsList = new Shielding;
    physicsList->RegisterPhysics(new G4NeutronTrackingCut()); // allow G4UserLimits

    // - Setup biasing, first for neutrons, again for muons
    G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();

    G4String              pname = "nCapture";  // neutron capture process name
    std::vector<G4String> pvec;                // required vector,
    pvec.push_back(pname);                     // here with single data member
    biasingPhysics->Bias("neutron", pvec);     // bias particle and process

    pvec.clear();
    pname = "muonNuclear";
    pvec.push_back(pname);
    biasingPhysics->Bias("mu-", pvec);  // bias particle and process

    physicsList->RegisterPhysics(biasingPhysics);
    runManager->SetUserInitialization(physicsList);

    // -- Set user action initialization class, forward random seed
    auto actions = new WLGDActionInitialization(detector, outputFileName);
    runManager->SetUserInitialization(actions);

    // Initialize G4 kernel
    //
    runManager->Initialize();

#ifdef G4VIS_USE
    // Visualization manager
    //
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

    // Get the pointer to the User Interface manager
    //
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if(macroName.empty())  // Define UI session for interactive mode
    {
#ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#    ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute vis.mac");
#    endif
        ui->SessionStart();
        delete ui;
#endif
    }
    else  // Batch mode
    {
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macroName);
    }

#ifdef G4VIS_USE
    delete visManager;
#endif
    delete runManager;

    return 0;
}
