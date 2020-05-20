#ifndef GB03PSLocation_h
#define GB03PSLocation_h 1

#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"
#include "G4VPrimitiveScorer.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring energy deposit location
//   at termination of the track.
//
///////////////////////////////////////////////////////////////////////////////

class GB03PSLocation : public G4VPrimitiveScorer
{
public:                                            // with description
  GB03PSLocation(G4String name, G4int depth = 0);  // default unit
  GB03PSLocation(G4String name, const G4String& unit, G4int depth = 0);
  virtual ~GB03PSLocation();

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
  G4int                      HCID;
  G4int                      fcounter;
  G4THitsMap<G4ThreeVector>* EvtMap;
};
#endif
