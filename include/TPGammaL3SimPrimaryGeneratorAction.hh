/// TPGammaL3SimPrimaryGeneratorAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimPrimaryGeneratorAction_h
#define TPGammaL3SimPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4UImanager.hh"
#include "G4EventManager.hh"
#include "TPGammaL3SimEventAction.hh"

class G4Event;

class TPGammaL3SimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  TPGammaL3SimPrimaryGeneratorAction();
  ~TPGammaL3SimPrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event* anEvent);
  void SetEnergy(G4double en){particleGun->SetParticleEnergy(en);};

  G4double GetEnergy(){return particleGun->GetParticleEnergy();};

private:
  G4ParticleGun* particleGun;
  G4GeneralParticleSource *particleSource;
  G4double IncidentE;
};

#endif
