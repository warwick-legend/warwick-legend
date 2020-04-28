//
//
// GB03PSLocation
#include "GB03PSLocation.hh"
#include "G4UnitsTable.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring energy deposit location
//   at termination of the track.
// 
///////////////////////////////////////////////////////////////////////////////

GB03PSLocation::GB03PSLocation(G4String name, G4int depth)
  :G4VPrimitiveScorer(name,depth),HCID(-1),fcounter(0),EvtMap(0)
{
  SetUnit("m");
}

GB03PSLocation::GB03PSLocation(G4String name, const G4String& unit, 
				     G4int depth)
  :G4VPrimitiveScorer(name,depth),HCID(-1),fcounter(0),EvtMap(0)
{
  SetUnit(unit);
}

GB03PSLocation::~GB03PSLocation()
{;}

G4bool GB03PSLocation::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  if ( aStep->GetTrack()->GetTrackStatus() != fStopAndKill ) return FALSE; // termination
  //  if ( aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary ) return FALSE; // collisions

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4ThreeVector loc = preStepPoint->GetPosition(); // location at track creation
  loc.setX(loc.x() / GetUnitValue()); // unit value used
  loc.setY(loc.y() / GetUnitValue());
  loc.setZ(loc.z() / GetUnitValue());
 
  EvtMap->add(fcounter, loc);  

  fcounter++; // next key to process
  return TRUE;
}

void GB03PSLocation::Initialize(G4HCofThisEvent* HCE)
{
  fcounter = 0;
  EvtMap = new G4THitsMap<G4ThreeVector>(GetMultiFunctionalDetector()->GetName(),
					 GetName());
  if(HCID < 0) {HCID = GetCollectionID(0);}
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*)EvtMap);
}

void GB03PSLocation::EndOfEvent(G4HCofThisEvent*)
{;}

void GB03PSLocation::clear()
{
  fcounter = 0;
  EvtMap->clear();
}

void GB03PSLocation::DrawAll()
{;}

void GB03PSLocation::PrintAll()
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

void GB03PSLocation::SetUnit(const G4String& unit)
{
  CheckAndSetUnit(unit,"Length");
}
