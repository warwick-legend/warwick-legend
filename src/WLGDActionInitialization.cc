#include "WLGDActionInitialization.hh"
#include "WLGDPrimaryGeneratorAction.hh"
#include "WLGDRunAction.hh"
#include "WLGDEventAction.hh"


WLGDActionInitialization::WLGDActionInitialization(WLGDDetectorConstruction* det, G4String name)
 : G4VUserActionInitialization(), fDet(det), foutname(name)
{}


WLGDActionInitialization::~WLGDActionInitialization()
{}


void WLGDActionInitialization::BuildForMaster() const
{
  auto event = new WLGDEventAction;
  SetUserAction(new WLGDRunAction(event, foutname));
}


void WLGDActionInitialization::Build() const
{
  // forward detector
  SetUserAction(new WLGDPrimaryGeneratorAction(fDet));
  auto event = new WLGDEventAction;
  SetUserAction(event);
  SetUserAction(new WLGDRunAction(event, foutname));
}  

