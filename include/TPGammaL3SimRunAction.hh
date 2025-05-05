/// TPGammaL3SimRunAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimRunAction_h
#define TPGammaL3SimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TPGammaL3SimEventAction.hh"
#include "TPGammaL3SimGeometry.hh"
#include "Randomize.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "TFile.h"

//class Geometry;
class TPGammaL3SimGeometry;
class G4Run;

class TPGammaL3SimRunAction : public G4UserRunAction
{

public:
  TPGammaL3SimRunAction(TPGammaL3SimGeometry*, const char*, G4bool);
  ~TPGammaL3SimRunAction();

public:
  void DrawMemoryInformations();
  void CreateROOTFile(G4String);
  void WriteROOTFile(TFile* f);
  void MergeHistograms();
  void DisplayRunTime(time_t, time_t);
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  void SetStepParams(G4int m_ID,G4double m_Temps,G4String m_PartName);

  //adds the photon fates from an event to the run tree
  void UpdateStatistics(RunTally);


private:
  TPGammaL3SimGeometry * detector;
  static const G4String path_bin;
  int threadID;
  static G4Mutex fileMutex;
  G4String suffixe;
  G4String fileName;
  RunTally Stats;
  G4bool flag_MT;
  G4long seed;
  TFile *f;
  TTree *NaI;
  TBranch *RunBranch;
  time_t start;
  time_t end;
  G4String fname, nom_fichier;

};

#endif
