#ifndef WLGDDetectorConstruction_h
#define WLGDDetectorConstruction_h 1

#include "G4Cache.hh"
#include "G4GenericMessenger.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4MultiFunctionalDetector;

class WLGDDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  WLGDDetectorConstruction();
  ~WLGDDetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();
  virtual void               ConstructSDandField();

  G4double GetWorldSizeZ() { return fvertexZ; }  // inline
  G4double GetWorldExtent() { return fmaxrad; }  // --"--
  void     SetGeometry(const G4String& name);

private:
  void DefineCommands();
  void DefineMaterials();

  G4VPhysicalVolume* SetupBaseline();
  G4VPhysicalVolume* SetupAlternative();

  G4GenericMessenger*                 fDetectorMessenger = nullptr;
  G4double                            fvertexZ           = -1.0;
  G4double                            fmaxrad            = -1.0;
  G4String                            fGeometryName      = "baseline";
  G4Cache<G4MultiFunctionalDetector*> fSD                = nullptr;
};

#endif
