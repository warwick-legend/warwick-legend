#ifndef WLGDStackingAction_H
#define WLGDStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "G4Track.hh"

class WLGDStackingAction : public G4UserStackingAction
{
public:
  WLGDStackingAction();
  virtual ~WLGDStackingAction();

public:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent();

private:

};

#endif

