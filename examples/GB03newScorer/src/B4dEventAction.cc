//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4dEventAction.cc 100946 2016-11-03 11:28:08Z gcosmo $
//
/// \file B4dEventAction.cc
/// \brief Implementation of the B4dEventAction class

#include "B4dEventAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dEventAction::B4dEventAction()
 : G4UserEventAction(),
   fAbsoNWHCID(-1),
   fAbsoWWHCID(-1),
   fGapNWHCID(-1),
   fGapWWHCID(-1),
   fLocHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dEventAction::~B4dEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>* 
B4dEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4dEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4ThreeVector>* 
B4dEventAction::GetVecHitsCollection(G4int hcID,
				     const G4Event* event) const
{
  auto hitsCollection 
    = static_cast<G4THitsMap<G4ThreeVector>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4dEventAction::GetVecHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4dEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4dEventAction::EndOfEventAction(const G4Event* event)
{  
   // Get hist collections IDs
  if ( fAbsoNWHCID == -1 ) {
    fAbsoNWHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Calor_abs/PopNW");
    fAbsoWWHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Calor_abs/PopWW");
    fGapNWHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Calor_gap/PopNW");
    fGapWWHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Calor_gap/PopWW");
    fLocHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Calor_abs/Loc");
  }
  
  // Get entries from hits collections
  //
  G4THitsMap<G4double>* absNWHitsMap = GetHitsCollection(fAbsoNWHCID, event);
  G4THitsMap<G4double>* absWWHitsMap = GetHitsCollection(fAbsoWWHCID, event);
  G4THitsMap<G4double>* gapNWHitsMap = GetHitsCollection(fGapNWHCID, event);
  G4THitsMap<G4double>* gapWWHitsMap = GetHitsCollection(fGapWWHCID, event);
  G4THitsMap<G4ThreeVector>* absLocMap = GetVecHitsCollection(fLocHCID, event);

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // 8 columns to fill
  if (!aWWID.empty()) { // clear vectors
    aWWeight.clear();
    aNWeight.clear();
    gWWeight.clear();
    gNWeight.clear();
    aWWID.clear();
    aNWID.clear();
    gWWID.clear();
    gNWID.clear();
    xLoc.clear();
    yLoc.clear();
    zLoc.clear();
  }

  for ( auto it : *absWWHitsMap->GetMap() ) {
    aWWID.push_back(it.first);
    aWWeight.push_back(*it.second);
  }

  for ( auto it : *absNWHitsMap->GetMap() ) {
    aNWID.push_back(it.first);
    aNWeight.push_back(*it.second);
  }
  
  for ( auto it : *gapWWHitsMap->GetMap() ) {
    gWWID.push_back(it.first);
    gWWeight.push_back(*it.second);
  }
  
  for ( auto it : *gapNWHitsMap->GetMap() ) {
    gNWID.push_back(it.first);
    gNWeight.push_back(*it.second);
  }

  for ( auto it : *absLocMap->GetMap() ) { // transform coordinates before storing
    xLoc.push_back((*it.second).x());
    yLoc.push_back((*it.second).y());
    zLoc.push_back((*it.second).z());
  }

  // fill the ntuple
  analysisManager->AddNtupleRow();  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
