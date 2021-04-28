#include "WLGDStackingAction.hh"
// #include "WLGDTrackInformation.hh"

G4ClassificationOfNewTrack WLGDStackingAction ::ClassifyNewTrack(const G4Track* aTrack)
{
  G4ClassificationOfNewTrack classification = fUrgent;

//  if(aTrack->GetParentID() == 0)  // Primary particle
//  {
//    WLGDTrackInformation* trackInfo = new WLGDTrackInformation(aTrack);
//    aTrack->SetUserInformation(trackInfo);  // attach own track info
//  }
  return classification;
}

void WLGDStackingAction::NewStage() { ; }

void WLGDStackingAction::PrepareNewEvent() { ; }
