#include "RE01TrackInformation.hh"
#include "RE01TrackingAction.hh"
#include "RE01Trajectory.hh"

#include "G4Track.hh"
#include "G4TrackingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RE01TrackingAction::RE01TrackingAction()
: G4UserTrackingAction()
{
  ;
}

void RE01TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  // Create trajectory only for track in tracking region
  RE01TrackInformation* trackInfo =
    (RE01TrackInformation*) (aTrack->GetUserInformation());

  if(trackInfo->GetTrackingStatus() > 0)
  {
    fpTrackingManager->SetStoreTrajectory(true);
    fpTrackingManager->SetTrajectory(new RE01Trajectory(aTrack));
  }
  else
  {
    fpTrackingManager->SetStoreTrajectory(false);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RE01TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  if(secondaries)
  {
    RE01TrackInformation* info  = (RE01TrackInformation*) (aTrack->GetUserInformation());
    size_t                nSeco = secondaries->size();
    if(nSeco > 0)
    {
      for(size_t i = 0; i < nSeco; i++)
      {
        RE01TrackInformation* infoNew = new RE01TrackInformation(info);
        (*secondaries)[i]->SetUserInformation(infoNew);
      }
    }
  }
}
