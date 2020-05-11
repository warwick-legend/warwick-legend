// WLGDPSLocation
#include "WLGDPSLocation.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring energy deposit location
//   at termination of the track.
// 
///////////////////////////////////////////////////////////////////////////////

WLGDPSLocation::WLGDPSLocation(G4String name, G4int depth)
  :G4VPrimitiveScorer(name,depth),HCID(-1),fcounter(0),EvtMap(0)
{
  SetUnit("m");
}

WLGDPSLocation::WLGDPSLocation(G4String name, const G4String& unit, 
				     G4int depth)
  :G4VPrimitiveScorer(name,depth),HCID(-1),fcounter(0),EvtMap(0)
{
  SetUnit(unit);
}

WLGDPSLocation::~WLGDPSLocation()
{;}

G4bool WLGDPSLocation::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  if ( aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary ) return FALSE; // collisions

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4ThreeVector loc = preStepPoint->GetPosition(); // location at track creation
  loc.setX(loc.x() / GetUnitValue()); // unit value used
  loc.setY(loc.y() / GetUnitValue());
  loc.setZ(loc.z() / GetUnitValue());
 
  EvtMap->add(fcounter, loc);  

  fcounter++; // next key to process
  return TRUE;
}

void WLGDPSLocation::Initialize(G4HCofThisEvent* HCE)
{
  fcounter = 0;
  EvtMap = new G4THitsMap<G4ThreeVector>(GetMultiFunctionalDetector()->GetName(),
					 GetName());
  if(HCID < 0) {HCID = GetCollectionID(0);}
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*)EvtMap);
}

void WLGDPSLocation::EndOfEvent(G4HCofThisEvent*)
{;}

void WLGDPSLocation::clear()
{
  fcounter = 0;
  EvtMap->clear();
}

void WLGDPSLocation::DrawAll()
{;}

void WLGDPSLocation::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  std::map<G4int,G4ThreeVector*>::iterator itr = EvtMap->GetMap()->begin();
  for(; itr != EvtMap->GetMap()->end(); itr++) {
    G4cout << "  key: " << itr->first
	   << "  energy deposit at: (" 
	   << (*(itr->second)).x() << ", " 
	   << (*(itr->second)).y() << ", "
	   << (*(itr->second)).z() << ")"
	   << " [" << GetUnit()<<"]"
	   << G4endl;
  }
}

void WLGDPSLocation::SetUnit(const G4String& unit)
{
  CheckAndSetUnit(unit,"Length");
}