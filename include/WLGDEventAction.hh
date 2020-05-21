#ifndef WLGDEventAction_h
#define WLGDEventAction_h 1

#include <vector>

#include "G4UserEventAction.hh"
#include "G4PrimaryParticle.hh"
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

  std::vector<G4double>& GetxLoc() { return xLoc; }
  std::vector<G4double>& GetyLoc() { return yLoc; }
  std::vector<G4double>& GetzLoc() { return zLoc; }

private:
  // methods
  void PrintPrimary(G4PrimaryParticle* pp, G4int ind)

  // data members
  G4int                 fCollID_lar   = -1;
  G4int                 fCollID_ge    = -1;

  std::vector<G4double> xLoc;
  std::vector<G4double> yLoc;
  std::vector<G4double> zLoc;

};

#endif
