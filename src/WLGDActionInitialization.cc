#include "WLGDActionInitialization.hh"
#include "WLGDPrimaryGeneratorAction.hh"
#include "WLGDRunAction.hh"
#include "WLGDEventAction.hh"


WLGDActionInitialization::WLGDActionInitialization(WLGDDetectorConstruction* det, G4int ival)
 : G4VUserActionInitialization(), fDet(det), seed(ival)
{}


WLGDActionInitialization::~WLGDActionInitialization()
{}


void WLGDActionInitialization::BuildForMaster() const
{
  SetUserAction(new WLGDRunAction);
}


void WLGDActionInitialization::Build() const
{
  // forward detector and seed
  SetUserAction(new WLGDPrimaryGeneratorAction(fDet, seed));
  SetUserAction(new WLGDEventAction);
  SetUserAction(new WLGDRunAction);
}  

