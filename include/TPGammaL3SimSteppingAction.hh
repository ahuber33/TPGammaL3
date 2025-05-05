/// TPGammaL3SimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimSteppingAction_h
#define TPGammaL3SimSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "TPGammaL3SimRunAction.hh"


class G4Step;
class G4SteppingManager;
class TPGammaL3SimGeometry;
class TPGammaL3SimRunAction;
class TPGammaL3SimEventAction;

class TPGammaL3SimSteppingAction : public G4UserSteppingAction
{
public:
  TPGammaL3SimSteppingAction(TPGammaL3SimGeometry*,TPGammaL3SimRunAction*,TPGammaL3SimEventAction*);
  ~TPGammaL3SimSteppingAction();
public:
  void UserSteppingAction(const G4Step*);

private:
  TPGammaL3SimGeometry * detector;
  TPGammaL3SimRunAction* runaction;
  TPGammaL3SimEventAction* eventaction;
  static const G4String path;
  G4int Parent_ID=0;
  G4int StepNo=0;
  G4Track* track=nullptr;
  G4StepPoint* thePrePoint=nullptr;
  G4StepPoint* thePostPoint=nullptr;
  G4String ProcessName="";
  G4String VolumName="";
  G4String PreVolumName="";
  G4String PartName="";
  G4int ID=0;
  G4ThreeVector prePoint;
  G4ThreeVector postPoint;
  G4ThreeVector point;
  G4double x=0.0;
  G4double y=0.0;
  G4double z=0.0;
  G4double Edep=0.0;
  G4double Energy=0.0;

};
#endif
