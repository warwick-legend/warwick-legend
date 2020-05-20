#ifndef WLGDActionInitialization_h
#define WLGDActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "WLGDDetectorConstruction.hh"

/// Action initialization class.

class WLGDActionInitialization : public G4VUserActionInitialization
{
public:
  WLGDActionInitialization(WLGDDetectorConstruction* det, G4String name);
  virtual ~WLGDActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  WLGDDetectorConstruction* fDet;
  G4String                  foutname;
};

#endif
