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

private:
  G4int                 fTrackID            = 0;
  G4ParticleDefinition* fParticleDefinition = nullptr;
  G4ThreeVector         fPosition           = G4ThreeVector(0., 0., 0.);
  G4ThreeVector         fMomentum           = G4ThreeVector(0., 0., 0.);
  G4double              fEnergy             = 0.0;
  G4double              fTime               = 0.0;
};

extern G4ThreadLocal G4Allocator<WLGDTrackInformation>* aTrackInformationAllocator;

inline void* WLGDTrackInformation::operator new(size_t)
{
  if(aTrackInformationAllocator == nullptr)
  {
    aTrackInformationAllocator = new G4Allocator<WLGDTrackInformation>;
  }
  return (void*) aTrackInformationAllocator->MallocSingle();
}

inline void WLGDTrackInformation::operator delete(void* aTrackInfo)
{
  aTrackInformationAllocator->FreeSingle((WLGDTrackInformation*) aTrackInfo);
}

#endif
