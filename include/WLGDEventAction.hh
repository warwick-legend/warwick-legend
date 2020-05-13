#ifndef WLGDEventAction_h
#define WLGDEventAction_h 1

#include <vector>

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

/// Event action class
///

class WLGDEventAction : public G4UserEventAction
{
public:
  WLGDEventAction();
  virtual ~WLGDEventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
    
  // to create columns for Ntuple
  std::vector<G4double>& GetEdepWater() { return edep_water; }
  std::vector<G4double>& GetEdepLar() { return edep_lar; }
  std::vector<G4double>& GetEdepULar() { return edep_ular; }
  std::vector<G4double>& GetEdepGe() { return edep_ge; }
  std::vector<G4double>& GetxLocWater() { return xLoc_water; }
  std::vector<G4double>& GetxLocLar() { return xLoc_lar; }
  std::vector<G4double>& GetxLocULar() { return xLoc_ular; }
  std::vector<G4double>& GetxLocGe() { return xLoc_ge; }
  std::vector<G4double>& GetyLocWater() { return yLoc_water; }
  std::vector<G4double>& GetyLocLar() { return yLoc_lar; }
  std::vector<G4double>& GetyLocULar() { return yLoc_ular; }
  std::vector<G4double>& GetyLocGe() { return yLoc_ge; }
  std::vector<G4double>& GetzLocWater() { return zLoc_water; }
  std::vector<G4double>& GetzLocLar() { return zLoc_lar; }
  std::vector<G4double>& GetzLocULar() { return zLoc_ular; }
  std::vector<G4double>& GetzLocGe() { return zLoc_ge; }


private:
  // methods
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4THitsMap<G4ThreeVector>* GetVecHitsCollection(G4int hcID,
						  const G4Event* event) const;
  
  // data members                   
  G4int  fCollID_water;
  G4int  fCollID_lar;
  G4int  fCollID_ular;
  G4int  fCollID_ge;
  G4int  fLocID_water;
  G4int  fLocID_lar;
  G4int  fLocID_ular;
  G4int  fLocID_ge;
  std::vector<G4double> edep_water;
  std::vector<G4double> edep_lar;
  std::vector<G4double> edep_ular;
  std::vector<G4double> edep_ge;
  std::vector<G4double> xLoc_water;
  std::vector<G4double> xLoc_lar;
  std::vector<G4double> xLoc_ular;
  std::vector<G4double> xLoc_ge;
  std::vector<G4double> yLoc_water;
  std::vector<G4double> yLoc_lar;
  std::vector<G4double> yLoc_ular;
  std::vector<G4double> yLoc_ge;
  std::vector<G4double> zLoc_water;
  std::vector<G4double> zLoc_lar;
  std::vector<G4double> zLoc_ular;
  std::vector<G4double> zLoc_ge;

};
                     

#endif

    
