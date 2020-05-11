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
  analysisManager->CreateNtupleIColumn("IdWWabs", fEventAction->GetAbsWWID());
  analysisManager->CreateNtupleDColumn("withWabs", fEventAction->GetAbsWithWeight());
  analysisManager->CreateNtupleIColumn("IdNWabs", fEventAction->GetAbsNWID());
  analysisManager->CreateNtupleDColumn("noWabs", fEventAction->GetAbsNoWeight());
  analysisManager->CreateNtupleIColumn("IdWWgap", fEventAction->GetGapWWID());
  analysisManager->CreateNtupleDColumn("withWgap", fEventAction->GetGapWithWeight());
  analysisManager->CreateNtupleIColumn("IdNWgap", fEventAction->GetGapNWID());
  analysisManager->CreateNtupleDColumn("noWgap", fEventAction->GetGapNoWeight());
  analysisManager->CreateNtupleDColumn("xgap", fEventAction->GetxLocation());
  analysisManager->CreateNtupleDColumn("ygap", fEventAction->GetyLocation());
  analysisManager->CreateNtupleDColumn("zgap", fEventAction->GetzLocation());
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

