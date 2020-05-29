#ifndef WLGDTrackingAction_h
#define WLGDTrackingAction_h 1

#include "G4UserTrackingAction.hh"

class WLGDTrackingAction : public G4UserTrackingAction
{
public:
  WLGDTrackingAction();
  virtual ~WLGDTrackingAction(){};

  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);
};

#endif
