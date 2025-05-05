/// TPGammaL3SimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "TPGammaL3SimSteppingAction.hh"

using namespace CLHEP;

const G4String TPGammaL3SimSteppingAction::path = "../simulation_input_files/";

TPGammaL3SimSteppingAction::TPGammaL3SimSteppingAction(TPGammaL3SimGeometry *OptGeom, TPGammaL3SimRunAction *runaction, TPGammaL3SimEventAction *eventaction)
    : detector(OptGeom), runaction(runaction), eventaction(eventaction)
{
}

TPGammaL3SimSteppingAction::~TPGammaL3SimSteppingAction() {}
void TPGammaL3SimSteppingAction::UserSteppingAction(const G4Step *aStep)
{
  // ###################################
  //  Déclaration of functions/variables
  // ###################################
  Parent_ID = aStep->GetTrack()->GetParentID();
  StepNo = aStep->GetTrack()->GetCurrentStepNumber();
  track = aStep->GetTrack();
  thePrePoint = aStep->GetPreStepPoint();
  thePostPoint = aStep->GetPostStepPoint();
  ProcessName = thePostPoint->GetProcessDefinedStep()->GetProcessName();
  VolumName = track->GetVolume()->GetName();
  PreVolumName = thePrePoint->GetPhysicalVolume()->GetName();
  PartName = track->GetDefinition()->GetParticleName();
  ID = track->GetTrackID();
  prePoint = aStep->GetPreStepPoint()->GetPosition();
  postPoint = aStep->GetPostStepPoint()->GetPosition();
  point = prePoint + G4UniformRand() * (postPoint - prePoint);
  x = aStep->GetTrack()->GetPosition().x();
  y = aStep->GetTrack()->GetPosition().y();
  z = aStep->GetTrack()->GetPosition().z();
  Edep = aStep->GetTotalEnergyDeposit() / keV;
  Energy = track->GetKineticEnergy() / MeV;

  
  if (Parent_ID == 0 && StepNo == 1) eventaction->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy() / keV);

  if(PreVolumName =="NaI") 
  {
    eventaction->AddEdep(Edep);
    G4cout << "Edep = " << Edep << G4endl;
  }
}
  

  