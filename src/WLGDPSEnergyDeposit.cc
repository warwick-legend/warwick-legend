// WLGDPSEnergyDeposit
#include "WLGDPSEnergyDeposit.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring total energy deposit
//
///////////////////////////////////////////////////////////////////////////////

WLGDPSEnergyDeposit::WLGDPSEnergyDeposit(G4String name, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit("MeV");
}

WLGDPSEnergyDeposit::WLGDPSEnergyDeposit(G4String name, const G4String& unit, G4int depth)
: G4VPrimitiveScorer(std::move(name), depth)
, fCounter(0)
, HCID(-1)
, EvtMap(nullptr)
{
  SetUnit(unit);
}

WLGDPSEnergyDeposit::~WLGDPSEnergyDeposit() = default;

G4bool WLGDPSEnergyDeposit::ProcessHits(G4Step* aStep, G4TouchableHistory* /*unused*/)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep == 0.)
    return false;  // not for zero edep

  // dummy print info on hit
  G4cout << "energy scorer: particle name = " 
         << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
  G4cout << "lifetime: " 
         << aStep->GetTrack()->GetParticleDefinition()->GetPDGLifeTime() << G4endl;
  G4cout << "PDG: "
         << aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding() << G4endl;

  // end print info
  edep *= aStep->GetPreStepPoint()->GetWeight();  // (Particle Weight)
  EvtMap->add(fCounter, edep);
  fCounter++;
  return true;
}

void WLGDPSEnergyDeposit::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
  if(HCID < 0)
  {
    HCID = GetCollectionID(0);
  }
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*) EvtMap);
  fCounter = 0;
}

void WLGDPSEnergyDeposit::EndOfEvent(G4HCofThisEvent* /*unused*/) { ; }

void WLGDPSEnergyDeposit::clear()
{
  fCounter = 0;
  EvtMap->clear();
}

void WLGDPSEnergyDeposit::DrawAll() { ; }

void WLGDPSEnergyDeposit::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  auto itr = EvtMap->GetMap()->begin();
  for(; itr != EvtMap->GetMap()->end(); itr++)
  {
    G4cout << "  key: " << itr->first
           << "  energy deposit: " << *(itr->second) / GetUnitValue() << " [" << GetUnit()
           << "]" << G4endl;
  }
}

void WLGDPSEnergyDeposit::SetUnit(const G4String& unit)
{
  CheckAndSetUnit(unit, "Energy");
}
