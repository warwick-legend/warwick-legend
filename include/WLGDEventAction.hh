#ifndef WLGDEventAction_h
#define WLGDEventAction_h 1

#include <vector>

#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"
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
  std::vector<G4int>& GetHitTrackID()  { return htrid; }
  std::vector<G4int>& GetHitParentID() { return hpaid; }
  std::vector<G4int>& GetTrjTrackID()  { return trjtid; }
  std::vector<G4int>& GetTrjParentID() { return trjpid; }

private:
  // methods
  G4THitsMap<G4int>* GetIntHitsCollection(G4int hcID, const G4Event* event) const;

  // data members
  G4int                 fTidID = -1;
  G4int                 fPidID = -1;
  std::vector<G4int>    htrid;
  std::vector<G4int>    hpaid;
  std::vector<G4int>    trjtid;
  std::vector<G4int>    trjpid;
};

#endif
