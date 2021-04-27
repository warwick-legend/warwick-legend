#include "WLGDCrystalHit.hh"

G4ThreadLocal G4Allocator<WLGDCrystalHit>* WLGDCrystalHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WLGDCrystalHit::WLGDCrystalHit()
 : G4VHit(),
   fTid(0),
   fTime(0.),
   fWeight(0.),
   fEdep(0.),
   fPos(G4ThreeVector())
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WLGDCrystalHit::~WLGDCrystalHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WLGDCrystalHit::WLGDCrystalHit(const WLGDCrystalHit& right)
  : G4VHit()
{
  fTid       = right.fTid;
  fTime      = right.fTime;
  fWeight    = right.fWeight;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const WLGDCrystalHit& WLGDCrystalHit::operator=(const WLGDCrystalHit& right)
{
  fTid       = right.fTid;
  fTime      = right.fTime;
  fWeight    = right.fWeight;
  fEdep      = right.fEdep;
  fPos       = right.fPos;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool WLGDCrystalHit::operator==(const WLGDCrystalHit& right) const
{
  return ( this == &right ) ? true : false;
}

void WLGDCrystalHit::Draw()
{ ; }

void WLGDCrystalHit::Print()
{ ; }

