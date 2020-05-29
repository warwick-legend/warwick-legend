#include "WLGDActionInitialization.hh"
#include "WLGDEventAction.hh"
#include "WLGDPrimaryGeneratorAction.hh"
#include "WLGDRunAction.hh"
#include "WLGDStackingAction.hh"
#include "WLGDTrackingAction.hh"

WLGDActionInitialization::WLGDActionInitialization(WLGDDetectorConstruction* det,
                                                   G4String                  name)
: G4VUserActionInitialization()
, fDet(det)
, foutname(std::move(name))
{}

WLGDActionInitialization::~WLGDActionInitialization() = default;

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
  SetUserAction(new WLGDStackingAction);
  SetUserAction(new WLGDTrackingAction);
}
