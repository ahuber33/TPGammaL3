/// TPGammaL3SimMaterials.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimMaterials_h
#define TPGammaL3SimMaterials_h

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4Material.hh"
#include "G4NistManager.hh"

class G4Material;

class TPGammaL3SimMaterials
{
public:
  static TPGammaL3SimMaterials *getInstance();
  virtual ~TPGammaL3SimMaterials();
  G4Material *GetMaterial(const char*);

protected:
TPGammaL3SimMaterials();
  


private:
  std::vector<G4Material *> fMaterialsList;
  static TPGammaL3SimMaterials *fgInstance;

  G4String TypeIP;
  G4int Nbre_IP;

};
#endif
