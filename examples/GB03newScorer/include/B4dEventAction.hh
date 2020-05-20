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
// $Id: B4dEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
//
/// \file B4dEventAction.hh
/// \brief Definition of the B4dEventAction class

#ifndef B4dEventAction_h
#define B4dEventAction_h 1

#include <vector>

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

/// Event action class
///
/// In EndOfEventAction(), it prints the accumulated quantities of the energy
/// deposit and track lengths of charged particles in Absober and Gap layers
/// stored in the hits collections.

class B4dEventAction : public G4UserEventAction
{
public:
  B4dEventAction();
  virtual ~B4dEventAction();

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);

  std::vector<G4double>& GetAbsWithWeight() { return aWWeight; }
  std::vector<G4double>& GetAbsNoWeight() { return aNWeight; }
  std::vector<G4double>& GetGapWithWeight() { return gWWeight; }
  std::vector<G4double>& GetGapNoWeight() { return gNWeight; }
  std::vector<G4int>&    GetAbsNWID() { return aNWID; }
  std::vector<G4int>&    GetAbsWWID() { return aWWID; }
  std::vector<G4int>&    GetGapNWID() { return gNWID; }
  std::vector<G4int>&    GetGapWWID() { return gWWID; }
  std::vector<G4double>& GetxLocation() { return xLoc; }
  std::vector<G4double>& GetyLocation() { return yLoc; }
  std::vector<G4double>& GetzLocation() { return zLoc; }

private:
  // methods
  G4THitsMap<G4double>*      GetHitsCollection(G4int hcID, const G4Event* event) const;
  G4THitsMap<G4ThreeVector>* GetVecHitsCollection(G4int hcID, const G4Event* event) const;

  // data members
  G4int                 fAbsoNWHCID;
  G4int                 fAbsoWWHCID;
  G4int                 fGapNWHCID;
  G4int                 fGapWWHCID;
  G4int                 fLocHCID;
  std::vector<G4double> aWWeight;
  std::vector<G4double> aNWeight;
  std::vector<G4double> gWWeight;
  std::vector<G4double> gNWeight;
  std::vector<G4double> xLoc;
  std::vector<G4double> yLoc;
  std::vector<G4double> zLoc;
  std::vector<G4int>    aWWID;
  std::vector<G4int>    aNWID;
  std::vector<G4int>    gWWID;
  std::vector<G4int>    gNWID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
