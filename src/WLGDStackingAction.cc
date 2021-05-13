#include "WLGDStackingAction.hh"
// #include "WLGDTrackInformation.hh"

G4ClassificationOfNewTrack WLGDStackingAction ::ClassifyNewTrack(const G4Track* aTrack)
{
  G4ClassificationOfNewTrack classification = fUrgent;

  return classification;
}

void WLGDStackingAction::NewStage() { ; }

void WLGDStackingAction::PrepareNewEvent() { ; }
