#include "WLGDEventAction.hh"
#include "g4root.hh"
#include "WLGDTrajectory.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "Randomize.hh"
#include <iomanip>
#include <vector>


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


void WLGDEventAction::BeginOfEventAction(const G4Event* /*event*/) 
{
  edep.clear();
}

void WLGDEventAction::EndOfEventAction(const G4Event* event)
{
  // Get hist collections IDs
  if(fCollID < 0)
  {
    fCollID   = G4SDManager::GetSDMpointer()->GetCollectionID("Det/Edep");
  }

  // Get entries from hits collections
  //
  G4THitsMap<G4double>*      HitsMap     = GetHitsCollection(fCollID, event);

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  for(auto it : *HitsMap->GetMap())
  {
    edep.push_back((*it.second));
  }

  // fill the ntuple
  analysisManager->AddNtupleRow();


  // printing
  G4int eventID = event->GetEventID();
  G4cout << ">>> Event: " << eventID << G4endl;
  G4cout << "    " << edep.size() << " hits stored in this event." << G4endl;

  // get number of stored trajectories
  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // extract the trajectories and print them out
  G4cout << G4endl;
  G4cout << "Trajectories in tracker "<<
    "--------------------------------------------------------------" 
         << G4endl;

  for(G4int i=0; i<n_trajectories; i++) 
  {
    RE01Trajectory* trj = 
      (RE01Trajectory*)((*(evt->GetTrajectoryContainer()))[i]);
    trj->ShowTrajectory();
  }
}


