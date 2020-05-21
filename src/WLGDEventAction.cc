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


void WLGDEventAction::BeginOfEventAction(const G4Event* /*event*/) 
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  if(fCollID_lar<0 || fCollID_ge<0)
  {
    G4String colNam;
    fCollID_lar = SDman->GetCollectionID(colNam="LArCollection");
    fCollID_ge  = SDman->GetCollectionID(colNam="GeCollection");
  }
}

void WLGDEventAction::EndOfEventAction(const G4Event* event)
{
  // printing
  G4int eventID = event->GetEventID();
  G4cout << ">>> Event: " << eventID << G4endl;

  // safety
  if(event->GetNumberOfPrimaryVertex() == 0)
  {
    G4cout << "Event is empty." << G4endl;
    return;
  }
  if(fCollID_lar<0 || fCollID_ge<0)
  {
    G4cout << "No Hit collection ID's." << G4endl;
    return;
  }
  G4cout << "    " << xLoc.size() << " hits stored in this event." << G4endl;

  G4HCofThisEvent * HCE = event->GetHCofThisEvent();
  WLGDLArHitsCollection* LHC = nullptr;
  WLGDGeHitsCollection*  GHC = nullptr;

  if(HCE != nullptr)
  {
    LHC = (WLGDLArHitsCollection*)(HCE->GetHC(fCollID_lar));
    GHC = (WLGDGeHitsCollection*)(HCE->GetHC(fCollID_ge));

    // 3 columns to fill
    if(!xLoc.empty())
    {  // clear vectors
      xLoc.clear();
      yLoc.clear();
      zLoc.clear();
    }  
  }

  if(LHC != nullptr)
  {
    for (auto entry : LHC)
    {      
      for (auto val : *entry)
      {    
        xLoc.push_back(val.x()); // could add other observables   
        yLoc.push_back(val.y());
        zLoc.push_back(val.z());
      }
    }
  }
  if(GHC != nullptr)
  {
    for (auto entry : GHC)
    {
      for (auto val : *entry)
      {
        xLoc.push_back(val.x()); // could add other observables
        yLoc.push_back(val.y());
        zLoc.push_back(val.z());
      }
    }  
  }    

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill the ntuple
  analysisManager->AddNtupleRow();

  // get number of stored trajectories
  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  // extract the trajectories and print them out
  G4cout << G4endl;
  G4cout << "Trajectories in tracker "<<
    "--------------------------------------------------------------" 
         << G4endl;
  if(fpEventManager->GetVerboseLevel()>0)
  {
    for(G4int i=0; i<n_trajectories; i++) 
    {
      auto trj = (WLGDTrajectory*)((*(evt->GetTrajectoryContainer()))[i]);
      trj->ShowTrajectory();
    }
  }
    
  G4cout << G4endl;
  G4cout << "Primary particles "<<
    "--------------------------------------------------------------" 
         << G4endl;
  G4int n_vertex = evt->GetNumberOfPrimaryVertex();
  for(G4int iv=0;iv<n_vertex;iv++)
  {
    G4PrimaryVertex* pv = evt->GetPrimaryVertex(iv);
    G4cout << G4endl;
    G4cout << "Primary vertex "
           << G4ThreeVector(pv->GetX0(),pv->GetY0(),pv->GetZ0())
           << "   at t = " << (pv->GetT0())/ns << " [ns]" << G4endl;
    if(fpEventManager->GetVerboseLevel()>0)
    {
      G4PrimaryParticle* pp = pv->GetPrimary();
      while(pp)
      {
        PrintPrimary(pp,0);
        pp = pp->GetNext();
      }
    }
  }
}

void WLGDEventAction::PrintPrimary(G4PrimaryParticle* pp,G4int ind)
{
  for(G4int ii=0;ii<=ind;ii++)
  { G4cout << "  "; }
  G4cout << "==PDGcode " << pp->GetPDGcode() << " ";
  if(pp->GetG4code()!=0)
  { G4cout << "(" << pp->GetG4code()->GetParticleName() << ")"; }
  else
  { G4cout << "is not defined in G4"; }
  G4cout << " " << pp->GetMomentum()/GeV << " [GeV] ";
  if(pp->GetTrackID()<0)
  { G4cout << G4endl; }
  else
  { G4cout << ">>> G4Track ID " << pp->GetTrackID() << G4endl; }

  G4PrimaryParticle* daughter = pp->GetDaughter();
  while(daughter)
  {
    PrintPrimary(daughter,ind+1);
    daughter = daughter->GetNext();
  }
}


