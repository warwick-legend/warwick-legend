#ifndef WLGDDetectorConstruction_h
#define WLGDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GenericMessenger;


class WLGDDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  WLGDDetectorConstruction();
  ~WLGDDetectorConstruction();
  
public:
  
  virtual G4VPhysicalVolume* Construct();
  virtual void     ConstructSDandField();

private:

  void DefineCommands();

  G4VPhysicalVolume* SetupBaseline();
  G4VPhysicalVolume* SetupAlternative();

  G4GenericMessenger* fDetectorMessenger;
  G4bool              fBaseline;
};

#endif

