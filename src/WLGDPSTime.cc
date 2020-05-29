// WLGDPSTime
#include "WLGDPSTime.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring global track time
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSTime::WLGDPSTime(G4String name, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit("ns");
}

WLGDPSTime::WLGDPSTime(G4String name, const G4String& unit, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit(unit);
}

WLGDPSTime::~WLGDPSTime() = default;

G4bool WLGDPSTime::ProcessHits(G4Step* aStep, G4TouchableHistory* /*unused*/)
{
  if(aStep->GetTotalEnergyDeposit() == 0.)
    return false;  // not for zero edep

  // global time since start of event
  G4double tt = aStep->GetTrack()->GetGlobalTime();

  EvtMap->add(fCounter, tt);
  fCounter++;
  return true;
}

void WLGDPSTime::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
  fCounter = 0;
}

void WLGDPSTime::EndOfEvent(G4HCofThisEvent* /*unused*/) { ; }

void WLGDPSTime::clear()
{
  fCounter = 0;
  EvtMap->clear();
}

void WLGDPSTime::DrawAll() { ; }

void WLGDPSTime::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  auto itr = EvtMap->GetMap()->begin();
  for(; itr != EvtMap->GetMap()->end(); itr++)
  {
    G4cout << "  key: " << itr->first
           << "  global time: " << *(itr->second) / GetUnitValue() << " [" << GetUnit()
           << "]" << G4endl;
  }
}

void WLGDPSTime::SetUnit(const G4String& unit) { CheckAndSetUnit(unit, "Time"); }
