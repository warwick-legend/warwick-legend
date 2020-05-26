#ifndef WLGDTrackInformation_h
#define WLGDTrackInformation_h 1

#include "G4Allocator.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VUserTrackInformation.hh"
#include "globals.hh"

class WLGDTrackInformation : public G4VUserTrackInformation
{
public:
  WLGDTrackInformation();
  WLGDTrackInformation(const G4Track* aTrack);
  WLGDTrackInformation(const WLGDTrackInformation* aTrackInfo);
  virtual ~WLGDTrackInformation();

  inline void* operator new(size_t);
  inline void  operator delete(void* aTrackInfo);

  WLGDTrackInformation& operator=(const WLGDTrackInformation& right);

  virtual void Print() const;

public:

private:
  G4int                 fTrackID;
  G4ParticleDefinition* fParticleDefinition;
  G4ThreeVector         fPosition;
  G4ThreeVector         fMomentum;
  G4double              fEnergy;
  G4double              fTime;

};

extern G4ThreadLocal G4Allocator<WLGDTrackInformation>* aTrackInformationAllocator;

inline void* WLGDTrackInformation::operator new(size_t)
{
  if(!aTrackInformationAllocator)
    aTrackInformationAllocator = new G4Allocator<WLGDTrackInformation>;
  return (void*) aTrackInformationAllocator->MallocSingle();
}

inline void WLGDTrackInformation::operator delete(void* aTrackInfo)
{
  aTrackInformationAllocator->FreeSingle((WLGDTrackInformation*) aTrackInfo);
}

#endif
