/// TPGammaL3SimGeometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPGammaL3SimGeometry_h
#define TPGammaL3SimGeometry_h 1

#include "G4VUserDetectorConstruction.hh"
#include "TPGammaL3SimMaterials.hh"
#include "Geometry.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

class Geometry;
class TPGammaL3SimMaterials;
class G4VPhysicalVolume;

class TPGammaL3SimGeometry : public G4VUserDetectorConstruction
{
public:
  TPGammaL3SimGeometry();
  ~TPGammaL3SimGeometry();

public:
  G4VPhysicalVolume *Construct();
  void SetLogicalVolumeColor(G4LogicalVolume*, G4String);
  void ConstructWorld();
  void ConstructNaI();
  void ConstructHousing();
  void ConstructAbsorber();
  void GetVariables();
  

private:
  static const G4String path_bin;

  Geometry *Geom;

    // Colors for visualizations
  G4VisAttributes *invis;
  G4VisAttributes *white;
  G4VisAttributes *gray;
  G4VisAttributes *black;
  G4VisAttributes *red;
  G4VisAttributes *orange;
  G4VisAttributes *yellow;
  G4VisAttributes *green;
  G4VisAttributes *cyan;
  G4VisAttributes *blue;
  G4VisAttributes *magenta;

  // Logical Volumes
  G4LogicalVolume *LogicalWorld=nullptr;

  // Physical volumes
  G4VPhysicalVolume *PhysicalWorld=nullptr;
  
  G4double Radius_NaI=0.0;
  G4double Thickness_NaI=0.0;
  G4double Thickness_Housing=0.0;
  G4double Thickness_Absorber=0.0;
};
#endif
