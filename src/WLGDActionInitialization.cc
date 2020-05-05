#include "WLGDActionInitialization.hh"
#include "WLGDPrimaryGeneratorAction.hh"
#include "WLGDRunAction.hh"
#include "WLGDEventAction.hh"


WLGDActionInitialization::WLGDActionInitialization(WLGDDetectorConstruction* det)
 : G4VUserActionInitialization(), fDet(det)
{}


WLGDActionInitialization::~WLGDActionInitialization()
{}


void WLGDActionInitialization::BuildForMaster() const
{
  SetUserAction(new WLGDRunAction);
}


void WLGDActionInitialization::Build() const
{
  // forward detector
  SetUserAction(new WLGDPrimaryGeneratorAction(fDet));
  SetUserAction(new WLGDEventAction);
  SetUserAction(new WLGDRunAction);
}  

