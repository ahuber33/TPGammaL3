/// TPGammaL3SimPrimaryGeneratorAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "TPGammaL3SimPrimaryGeneratorAction.hh"


G4UImanager* UI = G4UImanager::GetUIpointer();
TPGammaL3SimPrimaryGeneratorAction::TPGammaL3SimPrimaryGeneratorAction(){
  //G4int n_particle = 1;

  //particleGun = new G4ParticleGun(n_particle);
  //UI->ApplyCommand("/control/execute setgun.mac");
  //UI->ApplyCommand("/control/execute setgun_script_use.mac");

  particleSource = new G4GeneralParticleSource();
  //UI->ApplyCommand("/control/execute setsource.mac");
}

TPGammaL3SimPrimaryGeneratorAction::~TPGammaL3SimPrimaryGeneratorAction(){
  //delete particleGun;
  delete particleSource;
}

void TPGammaL3SimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

  //particleGun->GeneratePrimaryVertex(anEvent);
  particleSource->GeneratePrimaryVertex(anEvent);

  //  always require these two lines
  G4EventManager *evtman = G4EventManager::GetEventManager();
  TPGammaL3SimEventAction *evtac = (TPGammaL3SimEventAction*)evtman->GetUserEventAction();

  //evtac->SetIncidentE(particleGun->GetParticleEnergy());
  //evtac->SetIncidentE(particleSource->GetParticleEnergy());
}
