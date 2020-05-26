#ifndef WLGDTrajectory_h
#define WLGDTrajectory_h 1

#include "G4Allocator.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4TrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include <stdlib.h>
#include <vector>

class G4Polyline;
class G4AttDef;
class G4AttValue;


class WLGDTrajectory : public G4VTrajectory
{
public:
  using WLGDTrajectoryPointContainer = std::vector<G4VTrajectoryPoint*>;


  WLGDTrajectory(const G4Track* aTrack);
  virtual ~WLGDTrajectory();

  virtual void ShowTrajectory(std::ostream& os = G4cout) const;
  virtual void DrawTrajectory() const;
  virtual const std::map<G4String, G4AttDef>* GetAttDefs() const;
  virtual std::vector<G4AttValue>*            CreateAttValues() const;
  virtual void                                AppendStep(const G4Step* aStep);
  virtual void MergeTrajectory(G4VTrajectory* secondTrajectory);

  inline void* operator new(size_t);
  inline void  operator delete(void*);
  inline int   operator==(const WLGDTrajectory& right) const { return (this == &right); }

  virtual G4int               GetTrackID() const { return fTrackID; }
  virtual G4int               GetParentID() const { return fParentID; }
  virtual G4String            GetParticleName() const { return fParticleName; }
  virtual G4int               GetPDGEncoding() const { return fPDGEncoding; }
  virtual G4ThreeVector       GetInitialMomentum() const { return fMomentum; }
  virtual int                 GetPointEntries() const { return fPositionRecord->size(); }
  virtual G4VTrajectoryPoint* GetPoint(G4int i) const { return (*fPositionRecord)[i]; }

private:
  WLGDTrajectoryPointContainer* fPositionRecord;
  G4int                         fTrackID;
  G4int                         fParentID;
  G4ParticleDefinition*         fParticleDefinition;
  G4String                      fParticleName;
  G4int                         fPDGEncoding;
  G4ThreeVector                 fMomentum;
  G4ThreeVector                 fVertexPosition;
  G4double                      fGlobalTime;
};

extern G4ThreadLocal G4Allocator<WLGDTrajectory>* myTrajectoryAllocator;

inline void* WLGDTrajectory::operator new(size_t)
{
  if(!myTrajectoryAllocator)
    myTrajectoryAllocator = new G4Allocator<WLGDTrajectory>;
  return (void*) myTrajectoryAllocator->MallocSingle();
}

inline void WLGDTrajectory::operator delete(void* aTrajectory)
{
  myTrajectoryAllocator->FreeSingle((WLGDTrajectory*) aTrajectory);
}

#endif
