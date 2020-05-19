// WLGDPSTime
#include "WLGDPSTime.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring global track time
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSTime::WLGDPSTime(G4String name, G4int depth)
: G4VPrimitiveScorer(name, depth)
, HCID(-1)
, EvtMap(0)
{
    SetUnit("ns");
}

WLGDPSTime::WLGDPSTime(G4String name, const G4String& unit, G4int depth)
: G4VPrimitiveScorer(name, depth)
, HCID(-1)
, EvtMap(0)
{
    SetUnit(unit);
}

WLGDPSTime::~WLGDPSTime() { ; }

G4bool WLGDPSTime::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    if(aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary)
        return FALSE;  // all collisions

    G4double tt = aStep->GetTrack()->GetGlobalTime();

    G4int idx = GetIndex(aStep);
    EvtMap->add(idx, tt);

    return TRUE;
}

void WLGDPSTime::Initialize(G4HCofThisEvent* HCE)
{
    EvtMap =
        new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    if(HCID < 0)
    {
        HCID = GetCollectionID(0);
    }
    HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
}

void WLGDPSTime::EndOfEvent(G4HCofThisEvent*) { ; }

void WLGDPSTime::clear()
{
    EvtMap->clear();
}

void WLGDPSTime::DrawAll() { ; }

void WLGDPSTime::PrintAll()
{
    G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
    G4cout << " PrimitiveScorer " << GetName() << G4endl;
    G4cout << " Number of entries " << EvtMap->entries() << G4endl;
    std::map<G4int, G4double*>::iterator itr = EvtMap->GetMap()->begin();
    for(; itr != EvtMap->GetMap()->end(); itr++)
    {
        G4cout << "  key: " << itr->first << "  global time: "
               << *(itr->second) / GetUnitValue()
               << " [" << GetUnit() << "]" << G4endl;
    }
}

void WLGDPSTime::SetUnit(const G4String& unit) { CheckAndSetUnit(unit, "Time"); }
