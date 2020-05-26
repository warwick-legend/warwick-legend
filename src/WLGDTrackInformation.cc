#include "WLGDTrackInformation.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<WLGDTrackInformation>* aTrackInformationAllocator = 0;

WLGDTrackInformation::WLGDTrackInformation()
: G4VUserTrackInformation()
{
  fTrackID            = 0;
  fParticleDefinition = 0;
  fPosition           = G4ThreeVector(0., 0., 0.);
  fMomentum           = G4ThreeVector(0., 0., 0.);
  fEnergy             = 0.;
  fTime               = 0.;
}

WLGDTrackInformation::WLGDTrackInformation(const G4Track* aTrack)
: G4VUserTrackInformation()
{
  fTrackID            = aTrack->GetTrackID();
  fParticleDefinition = aTrack->GetDefinition();
  fPosition           = aTrack->GetPosition();
  fMomentum           = aTrack->GetMomentum();
  fEnergy             = aTrack->GetTotalEnergy();
  fTime               = aTrack->GetGlobalTime();
}

WLGDTrackInformation ::WLGDTrackInformation(const WLGDTrackInformation* aTrackInfo)
: G4VUserTrackInformation()
{
  fTrackID            = aTrackInfo->fTrackID;
  fParticleDefinition = aTrackInfo->fParticleDefinition;
  fPosition           = aTrackInfo->fPosition;
  fMomentum           = aTrackInfo->fMomentum;
  fEnergy             = aTrackInfo->fEnergy;
  fTime               = aTrackInfo->fTime;
}

WLGDTrackInformation::~WLGDTrackInformation() { ; }

WLGDTrackInformation& WLGDTrackInformation ::operator=(
  const WLGDTrackInformation& aTrackInfo)
{
  fTrackID            = aTrackInfo.fTrackID;
  fParticleDefinition = aTrackInfo.fParticleDefinition;
  fPosition           = aTrackInfo.fPosition;
  fMomentum           = aTrackInfo.fMomentum;
  fEnergy             = aTrackInfo.fEnergy;
  fTime               = aTrackInfo.fTime;

  return *this;
}

void WLGDTrackInformation::Print() const
{
  G4cout << "Track ID " << fTrackID << " (" << fParticleDefinition->GetParticleName()
         << "," << fEnergy / GeV << "[GeV]) at " << fPosition << G4endl;
}
