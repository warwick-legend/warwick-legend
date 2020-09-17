// WLGDPSLocation
#include "WLGDPSLocation.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring energy deposit location
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSLocation::WLGDPSLocation(G4String name, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit("m");
}

WLGDPSLocation::WLGDPSLocation(G4String name, const G4String& unit, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit(unit);
}

WLGDPSLocation::~WLGDPSLocation() = default;

G4bool WLGDPSLocation::ProcessHits(G4Step* aStep, G4TouchableHistory* /*unused*/)
{

  G4StepPoint*  preStepPoint = aStep->GetPreStepPoint();
  G4ThreeVector loc          = preStepPoint->GetPosition();  // location at track creation

  EvtMap->add(fCounter, loc);
  fCounter++;
  return true;
}

void WLGDPSLocation::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap =
    new G4THitsMap<G4ThreeVector>(GetMultiFunctionalDetector()->GetName(), GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
  fCounter = 0;
}

void WLGDPSLocation::EndOfEvent(G4HCofThisEvent* /*unused*/) { ; }

void WLGDPSLocation::clear()
{
  fCounter = 0;
  EvtMap->clear();
}

void WLGDPSLocation::DrawAll() { ; }

void WLGDPSLocation::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  auto itr = EvtMap->GetMap()->begin();
  for(; itr != EvtMap->GetMap()->end(); itr++)
  {
    G4cout << "  key: " << itr->first << "  energy deposit at: ("
           << (*(itr->second)).x() / GetUnitValue() << ", "
           << (*(itr->second)).y() / GetUnitValue() << ", "
           << (*(itr->second)).z() / GetUnitValue() << ")"
           << " [" << GetUnit() << "]" << G4endl;
  }
}

void WLGDPSLocation::SetUnit(const G4String& unit) { CheckAndSetUnit(unit, "Length"); }
