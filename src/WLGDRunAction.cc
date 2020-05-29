#include "WLGDRunAction.hh"
#include "WLGDEventAction.hh"
#include "g4root.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

WLGDRunAction::WLGDRunAction(WLGDEventAction* eventAction, G4String name)
: G4UserRunAction()
, fEventAction(eventAction)
, fout(std::move(name))
{
  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Create directories
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // Creating ntuple with vector entries
  //
  analysisManager->CreateNtuple("Score", "Hits");
  analysisManager->CreateNtupleIColumn("Htrid",
                                       fEventAction->GetHitTrackID());  // Hit score
  analysisManager->CreateNtupleIColumn("Hptid",
                                       fEventAction->GetHitParentID());  // Hit score
  analysisManager->CreateNtupleDColumn("Edep", fEventAction->GetHitEdep());
  analysisManager->CreateNtupleDColumn("Time", fEventAction->GetHitTime());
  analysisManager->CreateNtupleDColumn("Hitxloc", fEventAction->GetHitxLoc());
  analysisManager->CreateNtupleDColumn("Hityloc", fEventAction->GetHityLoc());
  analysisManager->CreateNtupleDColumn("Hitzloc", fEventAction->GetHitzLoc());
  analysisManager->CreateNtupleIColumn(
    "Trjtid", fEventAction->GetTrjTrackID());  // Trajectory score
  analysisManager->CreateNtupleIColumn(
    "Trjpid", fEventAction->GetTrjParentID());
  analysisManager->CreateNtupleIColumn(
    "Trjpdg", fEventAction->GetTrjPDG());
  analysisManager->CreateNtupleIColumn(   
    "Trjentries", fEventAction->GetTrjEntries());
  analysisManager->CreateNtupleDColumn(
    "TrjXVtx", fEventAction->GetTrjXVtx());
  analysisManager->CreateNtupleDColumn(
    "TrjYVtx", fEventAction->GetTrjYVtx());
  analysisManager->CreateNtupleDColumn(
    "TrjZVtx", fEventAction->GetTrjZVtx());
  analysisManager->CreateNtupleDColumn(
    "TrjXPos", fEventAction->GetTrjXPos());
  analysisManager->CreateNtupleDColumn(
    "TrjYPos", fEventAction->GetTrjYPos());
  analysisManager->CreateNtupleDColumn(
    "TrjZPos", fEventAction->GetTrjZPos());

  analysisManager->FinishNtuple();
}

WLGDRunAction::~WLGDRunAction() { delete G4AnalysisManager::Instance(); }

void WLGDRunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  analysisManager->OpenFile(fout);
}

void WLGDRunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // save ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}
