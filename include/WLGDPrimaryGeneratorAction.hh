#ifndef WLGDPrimaryGeneratorAction_h
#define WLGDPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4GenericMessenger;
class G4Event;
class G4ParticleDefinition;

/// Primary generator
///
/// A single particle is generated.
// The G4GenericMessenger is used for simple UI
/// User can select 
/// - the underground laboratory depth in [km.w.e.]


class WLGDPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    WLGDPrimaryGeneratorAction();
    virtual ~WLGDPrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
    
    void SetDepth(G4double val) { fDepth = val; }
    G4double GetDepth() const { return fDepth; }


  private:
    void DefineCommands();

    G4ParticleGun* fParticleGun;
    G4GenericMessenger* fMessenger;
    G4ParticleDefinition* fMuon;
    G4double fDepth;
};

#endif
