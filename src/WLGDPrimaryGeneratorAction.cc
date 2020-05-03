#include "WLGDPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"


WLGDPrimaryGeneratorAction::WLGDPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),     
  fParticleGun(nullptr), fMessenger(nullptr), 
  fMuon(nullptr), 
  fDepth(0.0)
{
  G4int nofParticles = 1;
  fParticleGun  = new G4ParticleGun(nofParticles);
  
  auto particleTable = G4ParticleTable::GetParticleTable();
  fMuon = particleTable->FindParticle("mu-");
  
  // default particle kinematics
  //  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-8.*m));
  fParticleGun->SetParticleDefinition(fMuon);
  
  // define commands for this class
  DefineCommands();
}


WLGDPrimaryGeneratorAction::~WLGDPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fMessenger;
}


void WLGDPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  
  
  fParticleGun->GeneratePrimaryVertex(event);
}


void WLGDPrimaryGeneratorAction::DefineCommands()
{
  // Define /WLGD/generator command directory using generic messenger class
  fMessenger 
    = new G4GenericMessenger(this, 
                             "/WLGD/generator/", 
                             "Primary generator control");
            
  // depth command
  auto& depthCmd
    = fMessenger->DeclareProperty("depth", fDepth, 
        "Underground laboratory depth [km.w.e.].");
  depthCmd.SetParameterName("d", true);
  depthCmd.SetRange("d>=0.");                                
  depthCmd.SetDefaultValue("0.");
  
}

