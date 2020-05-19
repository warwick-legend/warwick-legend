#include "WLGDEventAction.hh"
#include "g4root.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "Randomize.hh"
#include <iomanip>
#include <vector>

WLGDEventAction::WLGDEventAction()
: G4UserEventAction()
, fCollID_water(-1)
, fCollID_lar(-1)
, fCollID_ular(-1)
, fCollID_ge(-1)
, fLocID_water(-1)
, fLocID_lar(-1)
, fLocID_ular(-1)
, fLocID_ge(-1)
{
}

WLGDEventAction::~WLGDEventAction() {}

G4THitsMap<G4double>* WLGDEventAction::GetHitsCollection(G4int          hcID,
                                                         const G4Event* event) const
{
    auto hitsCollection =
        static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

    if(!hitsCollection)
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

    if(!hitsCollection)
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("WLGDEventAction::GetVecHitsCollection()", "MyCode0003",
                    FatalException, msg);
    }

    return hitsCollection;
}

void WLGDEventAction::BeginOfEventAction(const G4Event* /*event*/) {}

void WLGDEventAction::EndOfEventAction(const G4Event* event)
{
    // Get hist collections IDs
    if(fCollID_lar < 0)
    {
        fCollID_water = G4SDManager::GetSDMpointer()->GetCollectionID("WaterDet/Edep");
        fCollID_lar   = G4SDManager::GetSDMpointer()->GetCollectionID("LarDet/Edep");
        fCollID_ular  = G4SDManager::GetSDMpointer()->GetCollectionID("ULarDet/Edep");
        fCollID_ge    = G4SDManager::GetSDMpointer()->GetCollectionID("GeDet/Edep");

        fLocID_water = G4SDManager::GetSDMpointer()->GetCollectionID("WaterDet/Loc");
        fLocID_lar   = G4SDManager::GetSDMpointer()->GetCollectionID("LarDet/Loc");
        fLocID_ular  = G4SDManager::GetSDMpointer()->GetCollectionID("ULarDet/Loc");
        fLocID_ge    = G4SDManager::GetSDMpointer()->GetCollectionID("GeDet/Loc");
    }

    // Get entries from hits collections
    //
    G4THitsMap<G4double>*      waterHitsMap = GetHitsCollection(fCollID_water, event);
    G4THitsMap<G4double>*      larHitsMap   = GetHitsCollection(fCollID_lar, event);
    G4THitsMap<G4double>*      ularHitsMap  = GetHitsCollection(fCollID_ular, event);
    G4THitsMap<G4double>*      geHitsMap    = GetHitsCollection(fCollID_ge, event);
    G4THitsMap<G4ThreeVector>* waterLocMap  = GetVecHitsCollection(fLocID_water, event);
    G4THitsMap<G4ThreeVector>* larLocMap    = GetVecHitsCollection(fLocID_lar, event);
    G4THitsMap<G4ThreeVector>* ularLocMap   = GetVecHitsCollection(fLocID_ular, event);
    G4THitsMap<G4ThreeVector>* geLocMap     = GetVecHitsCollection(fLocID_ge, event);

    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // 8 columns to fill
    if(!edep_lar.empty())
    {  // clear vectors
        edep_water.clear();
        edep_lar.clear();
        edep_ular.clear();
        edep_ge.clear();
        xLoc_water.clear();
        xLoc_lar.clear();
        xLoc_ular.clear();
        xLoc_ge.clear();
        yLoc_water.clear();
        yLoc_lar.clear();
        yLoc_ular.clear();
        yLoc_ge.clear();
        zLoc_water.clear();
        zLoc_lar.clear();
        zLoc_ular.clear();
        zLoc_ge.clear();
    }

    for(auto it : *waterHitsMap->GetMap())
        edep_water.push_back(*it.second);

    for(auto it : *larHitsMap->GetMap())
        edep_lar.push_back(*it.second);

    for(auto it : *ularHitsMap->GetMap())
        edep_ular.push_back(*it.second);

    for(auto it : *geHitsMap->GetMap())
        edep_ge.push_back(*it.second);

    for(auto it : *waterLocMap->GetMap())
    {
        xLoc_water.push_back((*it.second).x());
        yLoc_water.push_back((*it.second).y());
        zLoc_water.push_back((*it.second).z());
    }

    for(auto it : *larLocMap->GetMap())
    {
        xLoc_lar.push_back((*it.second).x());
        yLoc_lar.push_back((*it.second).y());
        zLoc_lar.push_back((*it.second).z());
    }

    for(auto it : *ularLocMap->GetMap())
    {
        xLoc_ular.push_back((*it.second).x());
        yLoc_ular.push_back((*it.second).y());
        zLoc_ular.push_back((*it.second).z());
    }

    for(auto it : *geLocMap->GetMap())
    {
        xLoc_ge.push_back((*it.second).x());
        yLoc_ge.push_back((*it.second).y());
        zLoc_ge.push_back((*it.second).z());
    }

    // fill the ntuple
    analysisManager->AddNtupleRow();

    // printing
    G4int eventID = event->GetEventID();
    G4cout << ">>> Event: " << eventID << G4endl;
    G4cout << "    " << edep_water.size() 
               << " water hits stored in this event." << G4endl;
    G4cout << "    " << edep_lar.size()
               << " LAr hits stored in this event." << G4endl;
    G4cout << "    " << edep_ular.size()
               << " ULAr hits stored in this event." << G4endl;
    G4cout << "    " << edep_ge.size()
               << " germanium hits stored in this event." << G4endl;
}
