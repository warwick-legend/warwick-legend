#ifndef WLGDStackingAction_H
#define WLGDStackingAction_H 1

#include "G4Track.hh"
#include "G4UserStackingAction.hh"
#include "globals.hh"

class WLGDStackingAction : public G4UserStackingAction
{
public:
  WLGDStackingAction()          = default;
  virtual ~WLGDStackingAction() = default;

public:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void                       NewStage();
  virtual void                       PrepareNewEvent();

private:
};

#endif
