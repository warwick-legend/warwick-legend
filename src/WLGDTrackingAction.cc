#include "WLGDTrackingAction.hh"
// #include "WLGDTrackInformation.hh"
#include "WLGDTrajectory.hh"

#include "G4Track.hh"
#include "G4TrackingManager.hh"

WLGDTrackingAction::WLGDTrackingAction() = default;

void WLGDTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  // Create trajectory for track if requested
  if(fpTrackingManager->GetStoreTrajectory() > 0)
  {
    fpTrackingManager->SetTrajectory(new WLGDTrajectory(aTrack));
  }
}

void WLGDTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
}
