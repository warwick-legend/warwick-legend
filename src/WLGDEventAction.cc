#include "WLGDEventAction.hh"
#include "WLGDTrajectory.hh"
#include "g4root.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "Randomize.hh"
#include <iomanip>
#include <vector>

G4THitsMap<G4int>* WLGDEventAction::GetIntHitsCollection(G4int          hcID,
                                                         const G4Event* event) const
{
  auto hitsCollection =
    static_cast<G4THitsMap<G4int>*>(event->GetHCofThisEvent()->GetHC(hcID));

  if(hitsCollection == nullptr)
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("WLGDEventAction::GetHitsCollection()", "MyCode0003", FatalException,
                msg);
  }

  return hitsCollection;
}

G4THitsMap<G4double>* WLGDEventAction::GetHitsCollection(G4int          hcID,
                                                         const G4Event* event) const
{
  auto hitsCollection =
    static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

  if(hitsCollection == nullptr)
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("WLGDEventAction::GetHitsCollection()", "MyCode0003", FatalException,
                msg);
  }

  return hitsCollection;
}

G4THitsMap<G4ThreeVector>* WLGDEventAction::GetVecHitsCollection(
  G4int hcID, const G4Event* event) const
{
  auto hitsCollection =
    static_cast<G4THitsMap<G4ThreeVector>*>(event->GetHCofThisEvent()->GetHC(hcID));

  if(hitsCollection == nullptr)
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("WLGDEventAction::GetVecHitsCollection()", "MyCode0003", FatalException,
                msg);
  }

  return hitsCollection;
}

void WLGDEventAction::BeginOfEventAction(const G4Event*
                                         /*event*/)
{
  edep.clear();
  htrid.clear();
  hpaid.clear();
  thit.clear();
  xloc.clear();
  yloc.clear();
  zloc.clear();
  // clear trajectory data
  trjtid.clear();
  trjpid.clear();
  trjpdg.clear();
  trjnpts.clear();
  trjxvtz.clear();
  trjyvtz.clear();
  trjzvtz.clear();
  trjxpos.clear();
  trjypos.clear();
  trjzpos.clear();
}

void WLGDEventAction::EndOfEventAction(const G4Event* event)
{
  // Get hist collections IDs
  if(fTidID < 0)
  {
    fTidID  = G4SDManager::GetSDMpointer()->GetCollectionID("Det/TrackID");
    fPidID  = G4SDManager::GetSDMpointer()->GetCollectionID("Det/ParentID");
    fLocID  = G4SDManager::GetSDMpointer()->GetCollectionID("Det/Loc");
    fEdepID = G4SDManager::GetSDMpointer()->GetCollectionID("Det/Edep");
    fTimeID = G4SDManager::GetSDMpointer()->GetCollectionID("Det/Time");
  }

  // Get entries from hits collections
  //
  G4THitsMap<G4int>*         THitsMap = GetIntHitsCollection(fTidID, event);
  G4THitsMap<G4int>*         PHitsMap = GetIntHitsCollection(fPidID, event);
  G4THitsMap<G4double>*      HitsMap  = GetHitsCollection(fEdepID, event);
  G4THitsMap<G4ThreeVector>* LocMap   = GetVecHitsCollection(fLocID, event);
  G4THitsMap<G4double>*      TimeMap  = GetHitsCollection(fTimeID, event);

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill Hits output from SD
  for(auto it : *HitsMap->GetMap())
  {
    edep.push_back((*it.second));
  }
  for(auto it : *TimeMap->GetMap())
  {
    thit.push_back((*it.second));
  }
  for(auto it : *LocMap->GetMap())
  {
    xloc.push_back((*it.second).x());
    yloc.push_back((*it.second).y());
    zloc.push_back((*it.second).z());
  }
  for(auto it : *THitsMap->GetMap())
  {
    htrid.push_back((*it.second));
  }
  for(auto it : *PHitsMap->GetMap())
  {
    hpaid.push_back((*it.second));
  }

  // fill trajectory data
  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int                  n_trajectories      = trajectoryContainer->entries();

  for(G4int i = 0; i < n_trajectories; i++)
  {
    WLGDTrajectory* trj   = (WLGDTrajectory*) ((*(event->GetTrajectoryContainer()))[i]);
    G4String        pname = trj->GetParticleName();  // filter on particle name
    G4int           Z     = trj->GetParticleDefinition()->GetAtomicNumber();
    G4int           A     = trj->GetParticleDefinition()->GetAtomicMass();
    if(pname == "neutron" || (Z == 32 && A == 77))
    {
      trjtid.push_back(trj->GetTrackID());
      trjpid.push_back(trj->GetParentID());
      trjpdg.push_back(trj->GetPDGEncoding());
      trjxvtx.push_back((trj->GetVertex()).x());
      trjyvtx.push_back((trj->GetVertex()).y());
      trjzvtx.push_back((trj->GetVertex()).z());
      trjnpts.push_back(trj->GetPointEntries());
      for(int nn = 0; nn < trj->GetPointEntries(); ++nn)
      {
        trjxpos.push_back((trj->GetPoint(nn)->GetPosition()).x());
        trjypos.push_back((trj->GetPoint(nn)->GetPosition()).y());
        trjzpos.push_back((trj->GetPoint(nn)->GetPosition()).z());
      }
      //  trj->ShowTrajectory(); // long output to stdout
    }
  }

  // fill the ntuple
  analysisManager->AddNtupleRow();

  // printing
  G4int eventID = event->GetEventID();
  G4cout << ">>> Event: " << eventID << G4endl;
  G4cout << "    " << htrid.size() << " hits stored in this event." << G4endl;

  // extract the trajectories and print them out
  G4cout << G4endl;
  G4cout << "Trajectories in tracker: " << n_trajectories << G4endl;
}
