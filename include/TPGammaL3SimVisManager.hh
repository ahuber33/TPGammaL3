/// TPGammaL3SimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimVisManager_h
#define TPGammaL3SimVisManager_h 1

#include "G4VisManager.hh"


class TPGammaL3SimVisManager: public G4VisManager {

public:

  TPGammaL3SimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
