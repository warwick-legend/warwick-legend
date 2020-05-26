// WLGDPSParentID
#include "WLGDPSParentID.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring ParentID
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSParentID::WLGDPSParentID(G4String name, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit("NoUnit");
}

WLGDPSParentID::~WLGDPSParentID() = default;

G4bool WLGDPSParentID::ProcessHits(G4Step* aStep, G4TouchableHistory* /*unused*/)
{
  if(aStep->GetTotalEnergyDeposit() == 0.)
    return false;  // not for zero edep

  G4int pid = aStep->GetTrack()->GetParentID();
  EvtMap->add(fCounter, pid);
  fCounter++;
  return true;
}

void WLGDPSParentID::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap = new G4THitsMap<G4int>(GetMultiFunctionalDetector()->GetName(), GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
  fCounter = 0;
}

void WLGDPSParentID::EndOfEvent(G4HCofThisEvent* /*unused*/) { ; }

void WLGDPSParentID::clear()
{
  fCounter = 0;
  EvtMap->clear();
}

void WLGDPSParentID::DrawAll() { ; }

void WLGDPSParentID::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  auto itr = EvtMap->GetMap()->begin();
  for(; itr != EvtMap->GetMap()->end(); itr++)
  {
    G4cout << "  key: " << itr->first << "  parent ID: " << *(itr->second) << G4endl;
  }
}

void WLGDPSParentID::SetUnit(const G4String& unit) { ; }
