// WLGDPSTrackID
#include "WLGDPSTrackID.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring TrackID
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSTrackID::WLGDPSTrackID(G4String name, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit("NoUnit");
}

WLGDPSTrackID::~WLGDPSTrackID() = default;

G4bool WLGDPSTrackID::ProcessHits(G4Step* aStep, G4TouchableHistory* /*unused*/)
{
  if(aStep->GetTotalEnergyDeposit() == 0.)
    return false;  // not for zero edep

  G4int tid = aStep->GetTrack()->GetTrackID();
  EvtMap->add(fCounter, tid);
  fCounter++;
  return true;
}

void WLGDPSTrackID::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap = new G4THitsMap<G4int>(GetMultiFunctionalDetector()->GetName(), GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
  fCounter = 0;
}

void WLGDPSTrackID::EndOfEvent(G4HCofThisEvent* /*unused*/) { ; }

void WLGDPSTrackID::clear()
{
  fCounter = 0;
  EvtMap->clear();
}

void WLGDPSTrackID::DrawAll() { ; }

void WLGDPSTrackID::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  for(auto itr : *(EvtMap->GetMap()))
  {
    G4cout << "  key: " << itr.first << "  track ID: " << *(itr.second) << G4endl;
  }
}

void WLGDPSTrackID::SetUnit(const G4String& unit) { ; }
