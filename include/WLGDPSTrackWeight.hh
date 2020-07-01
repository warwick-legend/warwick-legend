#ifndef WLGDPSTrackWeight_h
#define WLGDPSTrackWeight_h 1

#include "G4THitsMap.hh"
#include "G4VPrimitiveScorer.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring total Track Weight
//
///////////////////////////////////////////////////////////////////////////////

class WLGDPSTrackWeight : public G4VPrimitiveScorer
{
public:                                                 // with description
  WLGDPSTrackWeight(G4String name, G4int depth = 0);  // default unit
  virtual ~WLGDPSTrackWeight();

protected:  // with description
  virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);

public:
  virtual void Initialize(G4HCofThisEvent*);
  virtual void EndOfEvent(G4HCofThisEvent*);
  virtual void clear();
  virtual void DrawAll();
  virtual void PrintAll();

  virtual void SetUnit(const G4String& unit);

private:
  int                   fCounter;
  G4int                 HCID;
  G4THitsMap<G4double>* EvtMap;
};
#endif
