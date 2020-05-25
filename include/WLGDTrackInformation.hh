#ifndef RE01TrackInformation_h
#define RE01TrackInformation_h 1

#include "G4Allocator.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VUserTrackInformation.hh"
#include "globals.hh"

class RE01TrackInformation : public G4VUserTrackInformation
{
public:
  RE01TrackInformation();
  RE01TrackInformation(const G4Track* aTrack);
  RE01TrackInformation(const RE01TrackInformation* aTrackInfo);
  virtual ~RE01TrackInformation();

  inline void* operator new(size_t);
  inline void  operator delete(void* aTrackInfo);

  RE01TrackInformation& operator=(const RE01TrackInformation& right);

  void         SetSourceTrackInformation(const G4Track* aTrack);
  virtual void Print() const;

public:
  inline G4int GetTrackingStatus() const { return fTrackingStatus; }
  inline void  SetTrackingStatus(G4int i) { fTrackingStatus = i; }
  inline G4int GetSourceTrackID() const { return fSourceTrackID; }
  inline void  SetSuspendedStepID(G4int i) { fSuspendedStepID = i; }
  inline G4int GetSuspendedStepID() const { return fSuspendedStepID; }

private:
  // Information of the primary track at the primary vertex
  G4int                 fOriginalTrackID;  // Track ID of primary particle
  G4ParticleDefinition* fParticleDefinition;
  G4ThreeVector         fOriginalPosition;
  G4ThreeVector         fOriginalMomentum;
  G4double              fOriginalEnergy;
  G4double              fOriginalTime;

  G4int fTrackingStatus;
  // trackingStatus = 1 : primary or secondary track which has not yet reached
  //                      to calorimeter
  //                = 0 : track which or ancester of which has reached to
  //                      calorimeter
  //                = 2 : track or its ancester had reached to calorimeter
  //                      and then escaped from it
  // Information of the track which reached to the calorimeter boundary at the
  // boundary surface.
  // This information is valid only for trackingStatus = 0 or 2
  G4int                 fSourceTrackID;
  G4ParticleDefinition* fSourceDefinition;
  G4ThreeVector         fSourcePosition;
  G4ThreeVector         fSourceMomentum;
  G4double              fSourceEnergy;
  G4double              fSourceTime;
  G4int                 fSuspendedStepID;
};

extern G4ThreadLocal G4Allocator<RE01TrackInformation>* aTrackInformationAllocator;

inline void* RE01TrackInformation::operator new(size_t)
{
  if(!aTrackInformationAllocator)
    aTrackInformationAllocator = new G4Allocator<RE01TrackInformation>;
  return (void*) aTrackInformationAllocator->MallocSingle();
}

inline void RE01TrackInformation::operator delete(void* aTrackInfo)
{
  aTrackInformationAllocator->FreeSingle((RE01TrackInformation*) aTrackInfo);
}

#endif
