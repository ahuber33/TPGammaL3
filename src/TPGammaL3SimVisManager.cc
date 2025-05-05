/// TPGammaL3SimVisManager.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifdef G4VIS_USE

#include "TPGammaL3SimVisManager.hh"

#ifdef G4VIS_USE_OPENGLX
#include "G4OpenGLImmediateX.hh"
#include "G4OpenGLStoredX.hh"
#endif

TPGammaL3SimVisManager::TPGammaL3SimVisManager () {}

void TPGammaL3SimVisManager::RegisterGraphicsSystems () {


  #ifdef G4VIS_USE_OPENGLX
    RegisterGraphicsSystem (new G4OpenGLImmediateX);
    RegisterGraphicsSystem (new G4OpenGLStoredX);
  #endif

  if (fVerbose > 0) {
    G4cout <<
      "\nYou have successfully chosen to use the following graphics systems."
	 << G4endl;
    PrintAvailableGraphicsSystems ();

  }
}

#endif
