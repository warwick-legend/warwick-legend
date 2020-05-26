#ifndef RE01StackingAction_H
#define RE01StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

class G4Track;
class G4VHitsCollection;

class RE01StackingAction : public G4UserStackingAction
{
public:
  RE01StackingAction();
  virtual ~RE01StackingAction();

public:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent();

private:
  G4VHitsCollection* GetCalCollection();
  
  G4int fStage;
  G4int fCalorimeterHitsColID;
};

#endif

