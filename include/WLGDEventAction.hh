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
    
  std::vector<G4double>& GetAbsWithWeight() { return aWWeight; }
  std::vector<G4double>& GetAbsNoWeight() { return aNWeight; }
  std::vector<G4double>& GetxLocation() { return xLoc; }
  std::vector<G4double>& GetyLocation() { return yLoc; }
  std::vector<G4double>& GetzLocation() { return zLoc; }


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

    
