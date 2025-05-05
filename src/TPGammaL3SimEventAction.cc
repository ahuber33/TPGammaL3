/// TPGammaL3SimEventAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "G4SteppingManager.hh"
#include "TPGammaL3SimSteppingAction.hh"
#include "G4Run.hh"
#include "TPGammaL3SimEventAction.hh"
#include "G4RunManager.hh"

using namespace CLHEP;


TPGammaL3SimEventAction::TPGammaL3SimEventAction(const char* suff):suffixe(suff){}

TPGammaL3SimEventAction::~TPGammaL3SimEventAction(){}


// Initialize all counters and set up the event branches for
// filling histograms with ROOT
void TPGammaL3SimEventAction::BeginOfEventAction(const G4Event* evt){

  G4int event_id = evt->GetEventID();

  //G4cout << "EVENT : " << event_id << G4endl;

  Statistics = {};
  TrackID.clear();

}

void TPGammaL3SimEventAction::SetTrackingID(G4int Track_ID, G4String PartName){
  TrackID.push_back(Track_ID);
  ParticuleName = PartName;
}

// Get the number of stored trajectories and calculate the statistics
void TPGammaL3SimEventAction::EndOfEventAction(const G4Event* evt){
  G4int event_id = evt->GetEventID();

  TPGammaL3SimRunAction *runac = (TPGammaL3SimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());

  runac->UpdateStatistics(Statistics);
}
