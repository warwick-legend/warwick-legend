#ifndef WLGDActionInitialization_h
#define WLGDActionInitialization_h 1

#^nclude "WLGDDetectorConstruction.hh"
#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class WLGDActionInitialization : public G4VUserActionInitialization
{
  public:
    WLGDActionInitialization(WLGDDetectorConstruction* det, G4int ival);
    virtual ~WLGDActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    WLGDDetectorConstruction* fDet;
    G4int seed;
};


#endif

    
