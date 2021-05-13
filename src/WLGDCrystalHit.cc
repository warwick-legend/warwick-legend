#include "WLGDCrystalHit.hh"

G4ThreadLocal G4Allocator<WLGDCrystalHit>* WLGDCrystalHitAllocator=0;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool WLGDCrystalHit::operator==(const WLGDCrystalHit& right) const
{
  return ( this == &right ) ? true : false;
}

void WLGDCrystalHit::Draw()
{ ; }

void WLGDCrystalHit::Print()
{ ; }
