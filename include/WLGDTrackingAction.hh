#ifndef RE01TrackingAction_h
#define RE01TrackingAction_h 1

#include "G4UserTrackingAction.hh"

class RE01TrackingAction : public G4UserTrackingAction
{
public:
  RE01TrackingAction();
  virtual ~RE01TrackingAction(){};

  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);
};

#endif
