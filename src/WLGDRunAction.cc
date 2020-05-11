#include "WLGDRunAction.hh"
#include "WLGDEventAction.hh"
#include "g4root.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


B4RunAction::B4RunAction(B4dEventAction* eventAction, G4String name)
 : G4UserRunAction(),
   fEventAction(eventAction), fout(name)
{ 
  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Create directories 
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // Creating ntuple with vector entries
  //
  analysisManager->CreateNtuple("Score", "Edep and location");
  analysisManager->CreateNtupleDColumn("Edepwater", fEventAction->GetEdepWater());
  analysisManager->CreateNtupleDColumn("Edeplar", fEventAction->GetEdepLar());
  analysisManager->CreateNtupleDColumn("Edepular", fEventAction->GetEdepULar());
  analysisManager->CreateNtupleDColumn("Edepge", fEventAction->GetEdepGe());
  analysisManager->CreateNtupleDColumn("xwater", fEventAction->GetxLocWater());
  analysisManager->CreateNtupleDColumn("xlar", fEventAction->GetxLocLar());
  analysisManager->CreateNtupleDColumn("xular", fEventAction->GetxLocULar());
  analysisManager->CreateNtupleDColumn("xge", fEventAction->GetxLocGe());
  analysisManager->CreateNtupleDColumn("ywater", fEventAction->GetyLocWater());
  analysisManager->CreateNtupleDColumn("ylar", fEventAction->GetyLocLar());
  analysisManager->CreateNtupleDColumn("yular", fEventAction->GetyLocULar());
  analysisManager->CreateNtupleDColumn("yge", fEventAction->GetyLocGe());
  analysisManager->CreateNtupleDColumn("zwater", fEventAction->GetzLocWater());
  analysisManager->CreateNtupleDColumn("zlar", fEventAction->GetzLocLar());
  analysisManager->CreateNtupleDColumn("zular", fEventAction->GetzLocULar());
  analysisManager->CreateNtupleDColumn("zge", fEventAction->GetzLocGe());
  analysisManager->FinishNtuple();

}


B4RunAction::~B4RunAction()
{
  delete G4AnalysisManager::Instance();  
}


void B4RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  analysisManager->OpenFile(fout);
}


void B4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // save ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

