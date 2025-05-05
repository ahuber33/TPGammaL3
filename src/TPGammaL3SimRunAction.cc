/// TPGammaL3SimRunAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "TPGammaL3SimRunAction.hh"

using namespace CLHEP;

G4Mutex TPGammaL3SimRunAction::fileMutex = G4MUTEX_INITIALIZER;
const G4String TPGammaL3SimRunAction::path_bin = "../bin/";

TPGammaL3SimRunAction::TPGammaL3SimRunAction(TPGammaL3SimGeometry *Geom, const char *suff, G4bool pMT)
    : detector (Geom),
    suffixe(suff),
      flag_MT(pMT),
      f(nullptr)
{
}
TPGammaL3SimRunAction::~TPGammaL3SimRunAction() {}

void TPGammaL3SimRunAction::DrawMemoryInformations() {
    std::ifstream file("/proc/self/status");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("VmRSS:") != std::string::npos) { // Mémoire réellement utilisée
            std::cout << "[Memory used] " << line << std::endl;
            break;
        }
    }
}

void TPGammaL3SimRunAction::CreateROOTFile(G4String suffixe)
{
  f = new TFile(suffixe.c_str(), "RECREATE");

  NaI = new TTree("NaI", "NaI_Information");

  // create the branch for each event.
  // Be careful of the data structure here!  /F is a float  /I is an integer
  RunBranch = NaI->Branch("IncidentE", &Stats.IncidentE, "IncidentE/F");
  RunBranch = NaI->Branch("Edep", &Stats.Edep, "Edep/F");
  
}

void TPGammaL3SimRunAction::WriteROOTFile(TFile *f)
{
  f->cd();
  f->Write();
  f->Close();
  delete f;
  f = nullptr;

  G4cout << "Write ROOT file" << G4endl;
}


void TPGammaL3SimRunAction::DisplayRunTime(time_t start, time_t end)
{
  G4int elapsed = end - start;
  G4cout << "Run Completed in " << elapsed / 3600
         << ":" << (elapsed % 3600) / 60 << ":"
         << ((elapsed % 3600) % 60) << G4endl;

  // Output the time in the file Runtime.out
  std::ofstream timeout;
  timeout.open("Runtime.out", std::ios::app);
  timeout << "Run "
          << ": " << elapsed / 3600
          << ":" << (elapsed % 3600) / 60
          << ":" << ((elapsed % 3600) % 60) << G4endl;
  timeout.close();
}

//-----------------------------------------------------
//  BeginOfRunAction:  used to calculate the start time and
//  to set up information in the run tree.
//-----------------------------------------------------
void TPGammaL3SimRunAction::BeginOfRunAction(const G4Run *aRun)
{

  threadID = G4Threading::G4GetThreadId();

  if (flag_MT == false)
  {
    start = time(NULL); // start the timer clock to calculate run times
    seed = start;
    G4Random::setTheSeed(seed);
    G4cout << "seed = " << seed << G4endl;
    fileName = suffixe + ".root";
    CreateROOTFile(fileName);
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  }

  else
  {
    G4AutoLock lock(&fileMutex); // Verrouillage automatique du mutex
    if (G4Threading::IsMasterThread())
    {
      start = time(NULL); // start the timer clock to calculate run times
      seed = start;
      G4Random::setTheSeed(seed);
    }

    else
    {
      G4String s = std::to_string(threadID);
      fileName = suffixe + "_" + s + ".root";
      CreateROOTFile(fileName);
      G4cout << "filename = " << fileName << G4endl;
    }
  }

  if (G4VVisManager::GetConcreteInstance())
  {
    G4UImanager *UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/scene/notifyHandlers");
  }

} // end BeginOfRunAction

//-----------------------------------------------------
//  EndOfRunAction:  used to calculate the end time and
//  to write information to the run tree.
//-----------------------------------------------------
void TPGammaL3SimRunAction::EndOfRunAction(const G4Run *aRun)
{

  G4AutoLock lock(&fileMutex); // Verrouillage automatique du mutex

  if (flag_MT == false)
  {
    end = time(NULL);
    WriteROOTFile(f);
    DisplayRunTime(start, end);
  }

  else
  {
    if (G4Threading::IsMasterThread())
    {
      end = time(NULL);
      DisplayRunTime(start, end);
      // WriteROOTFile(f);
    }

    else
    {
      WriteROOTFile(f);
    }
  }

  if (G4VVisManager::GetConcreteInstance())
  {
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }

  G4cout << "Leaving Run Action" << G4endl;
  DrawMemoryInformations();
}

//---------------------------------------------------------
//  For each event update the statistics in the Run tree
//---------------------------------------------------------

void TPGammaL3SimRunAction::UpdateStatistics(RunTally aRunTally)
{
  //G4AutoLock lock(&fileMutex); // Verrouillage automatique du mutex
  Stats = aRunTally;
  NaI->Fill();
}
