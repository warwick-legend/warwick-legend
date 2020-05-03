#include "WLGDPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"


WLGDPrimaryGeneratorAction::WLGDPrimaryGeneratorAction(G4int ival)
: G4VUserPrimaryGeneratorAction(),     
  generator(nullptr), 
  fParticleGun(nullptr), fMessenger(nullptr), 
  fMuon(nullptr), 
  fDepth(0.0), fseed(ival) 
{
  generator.seed(fseed); // re-initialize internal state with new seed

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
  typedef std::piecewise_linear_distribution<double> pld_type;

  int nw = 100; // number of bins
  double lower_bound = 1.0;    // energy interval lower bound [GeV]
  double upper_bound = 3000.0; // upper bound [GeV]
  double nearhorizontal = 1.0e-5;
  double fullcosangle = 1.0;

  // custom probability distributions
  pld_type ed(nw, lower_bound, upper_bound, MuEnergy(fDepth) );
  pld_type cosd(nw, nearhorizontal, fullcosangle, MuAngle(fDepth) );
  
  // momentum vector
  G4double px, py, pz;
  double sintheta, sinphi, costheta, cosphi;

  costheta = cosd(generator); // get a random number
  sintheta = std::sqrt(1. - costheta*costheta);

  std::uniform_real_distribution<> rndm(0.0, 1.0); // azimuth angle
  double twopi = 2.0 * std::acos(-1.0);
  double phi = twopi * rndm(generator);  // random uniform number
  sinphi = std::sin(phi);
  cosphi = std::cos(phi);
  
  px = -sintheta * cosphi;
  py = -sintheta * sinphi;
  pz = -costheta;  // default downwards: pz = -1.0
  G4ThreeVector momentumDir(px, py, pz);
  fParticleGun->SetParticleMomentumDirection(momentumDir);

  G4double ekin = ed(generator);  // get random number
  ekin *= GeV;
  fParticleGun->SetParticleEnergy(ekin);
  
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
