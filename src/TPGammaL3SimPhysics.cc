/// TPGammaL3SimPhysics.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "TPGammaL3SimPhysics.hh"

using namespace CLHEP;

TPGammaL3SimPhysics::TPGammaL3SimPhysics():  G4VModularPhysicsList()
{
  //defaultCutValue = 0.001*mm; //0.001
  defaultCutValue = 0.1*mm; //0.001
  //was 0.5*mm

  SetVerboseLevel(1);

  //default physics
  particleList = new G4DecayPhysics();

  //default physics
  raddecayList = new G4RadioactiveDecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics_option3();
}

TPGammaL3SimPhysics::~TPGammaL3SimPhysics(){
  delete raddecayList;
  delete emPhysicsList;
}

void TPGammaL3SimPhysics::ConstructParticle()
{
  // Here are constructed all particles you have chosen
  particleList->ConstructParticle();
}

void TPGammaL3SimPhysics::ConstructProcess()
{
  AddTransportation();
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();
  raddecayList->ConstructProcess();
}

void TPGammaL3SimPhysics::SetCuts()
{
  // defaultCutValue you have typed in is used
  SetCutsWithDefault();
}
