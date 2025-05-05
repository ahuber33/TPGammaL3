/// TPGammaL3SimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimEventAction_h
#define TPGammaL3SimEventAction_h 1

#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"

class G4Event;

// This struct carries statistics for the whole Run
struct RunTally
{
  float IncidentE;
  float Edep;
  //std::vector<float> EBremCreation;

  inline int operator==(const RunTally &right) const
  {
    return (this == &right);
  }
};

class TPGammaL3SimEventAction : public G4UserEventAction
{
public:
  TPGammaL3SimEventAction(const char *);
  ~TPGammaL3SimEventAction();

public:
  void BeginOfEventAction(const G4Event *);
  void EndOfEventAction(const G4Event *);
  void SetTrackingID(G4int Track_ID, G4String PartName);
  void SetIncidentE(G4double a) { Statistics.IncidentE = a; }
  void AddEdep(G4double a) { Statistics.Edep += a; }

private:
  TTree *EventTree;
  TBranch *EventBranch;
  RunTally Statistics;
  G4String suffixe;
  std::vector<int> TrackID;
  G4String ParticuleName;
};

#endif
