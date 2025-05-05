/// TPGammaL3SimActionInitialization.hh
//// Auteur: Arnaud HUBER for ENL group <huber@lp2ib.in2p3.fr>
//// Copyright: 2024 (C) Projet PALLAS

#ifndef TPGammaL3SimActionInitialization_h
#define TPGammaL3SimActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"
#include "TPGammaL3SimPrimaryGeneratorAction.hh"
#include "TPGammaL3SimRunAction.hh"
#include "TPGammaL3SimEventAction.hh"
#include "TPGammaL3SimSteppingAction.hh"
#include "TPGammaL3SimGeometry.hh"
#include "G4MTRunManager.hh"


class TPGammaL3SimGeometryConstruction;
class TPGammaL3SimPrimaryGeneratorAction;

class TPGammaL3SimActionInitialization : public G4VUserActionInitialization
{
public:
  TPGammaL3SimActionInitialization(TPGammaL3SimGeometry*, const char*, G4bool pMT);
  virtual ~TPGammaL3SimActionInitialization();
  size_t charToSizeT(G4String str);

  virtual void BuildForMaster() const;
  virtual void Build() const;
  char* NEvents;
  G4String suffixe;
  G4bool flag_MT=false;

private:
TPGammaL3SimGeometry * detector;
  
};

#endif