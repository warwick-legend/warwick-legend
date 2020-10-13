// WLGDPSTrackWeight
#include "WLGDPSTrackWeight.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring total track weight
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSTrackWeight::WLGDPSTrackWeight(G4String name, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit("NoUnit");
}

WLGDPSTrackWeight::~WLGDPSTrackWeight() = default;

G4bool WLGDPSTrackWeight::ProcessHits(G4Step* aStep, G4TouchableHistory* /*unused*/)
{
  if(aStep->GetTotalEnergyDeposit() <= 0.0)
    return false;

  // total weight since start of event
  G4double we = aStep->GetTrack()->GetWeight();

  G4int index = GetIndex(aStep);
  EvtMap->add(index, we);

  return true;
}

void WLGDPSTrackWeight::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
}

void WLGDPSTrackWeight::EndOfEvent(G4HCofThisEvent* /*unused*/) { ; }

void WLGDPSTrackWeight::clear() { EvtMap->clear(); }

void WLGDPSTrackWeight::DrawAll() { ; }

void WLGDPSTrackWeight::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  auto itr = EvtMap->GetMap()->begin();
  for(const auto& itr : *(EvtMap->GetMap()))
  {
    G4cout << "  key: " << itr.first << "  total weight: " << *(itr.second) << G4endl;
  }
}

void WLGDPSTrackWeight::SetUnit(const G4String& /*unused*/) { ; }
