#ifndef WLGDRunAction_h
#define WLGDRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class WLGDEventAction;
class G4Run;

/// Run action class
///

class WLGDRunAction : public G4UserRunAction
{
public:
    WLGDRunAction(WLGDEventAction* eventAction, G4String name);
    virtual ~WLGDRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    WLGDEventAction* fEventAction;  // have event information for run
    G4String         fout;          // output file name
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
