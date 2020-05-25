#ifndef WLGDEventAction_h
#define WLGDEventAction_h 1

#include <vector>

#include "G4UserEventAction.hh"
#include "G4THitsMap.hh"
#include "globals.hh"

/// Event action class
///

class WLGDEventAction : public G4UserEventAction
{
public:
  WLGDEventAction()          = default;
  virtual ~WLGDEventAction() = default;

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);

  // to create columns for Ntuple
  std::vector<G4double>& GetEdep() { return edep; }

private:
  // methods
  G4THitsMap<G4double>*      GetHitsCollection(G4int hcID, const G4Event* event) const;

  // data members
  G4int                 fCollID   = -1;
  std::vector<G4double> edep;

};

#endif
