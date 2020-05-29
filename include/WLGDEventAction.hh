#ifndef WLGDEventAction_h
#define WLGDEventAction_h 1

#include <vector>

#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"
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
  std::vector<G4int>&    GetHitTrackID()  { return htrid; }
  std::vector<G4int>&    GetHitParentID() { return hpaid; }
  std::vector<G4double>& GetHitEdep()     { return edep; }
  std::vector<G4double>& GetHitTime()     { return thit; }
  std::vector<G4double>& GetHitxLoc()     { return xloc; }
  std::vector<G4double>& GetHityLoc()     { return yloc; }
  std::vector<G4double>& GetHitzLoc()     { return zloc; }

  // tajectory methods
  std::vector<G4int>& GetTrjTrackID()  { return trjtid; }
  std::vector<G4int>& GetTrjParentID() { return trjpid; }

private:
  // methods
  G4THitsMap<G4int>*         GetIntHitsCollection(G4int hcID, const G4Event* event) const;
  G4THitsMap<G4double>*      GetHitsCollection(G4int hcID, const G4Event* event) const;
  G4THitsMap<G4ThreeVector>* GetVecHitsCollection(G4int hcID, const G4Event* event) const;

  // data members
  G4int                 fTidID  = -1;
  G4int                 fPidID  = -1;
  G4int                 fLocID  = -1;
  G4int                 fTimeID = -1;
  G4int                 fEdepID = -1;
  std::vector<G4int>    htrid;
  std::vector<G4int>    hpaid;
  std::vector<G4double> edep;
  std::vector<G4double> thit;
  std::vector<G4double> xloc;
  std::vector<G4double> yloc;
  std::vector<G4double> zloc;

  std::vector<G4int>    trjtid;
  std::vector<G4int>    trjpid;
};

#endif
