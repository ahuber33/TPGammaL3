/// Geometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef Geometry_h
#define Geometry_h

#include "G4LogicalVolume.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4Transform3D.hh"
#include "G4UnionSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include <G4Polycone.hh>
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include <math.h>

// #ifndef disable_gdml
#include "G4GDMLParser.hh"
// #endif

class Geometry
{
public:

  //constructor, builds from keys specified in buildfile
  Geometry(G4String buildfile);
  ~Geometry();
  //  void Construct();

public:
  G4LogicalVolume *GetCylinderVolume(G4String, G4double, G4double, G4double, G4Material*);
  G4LogicalVolume *GetBoxVolume(G4String, G4double, G4double, G4double, G4Material*);
  
  G4double GetRadiusNaI(){return Radius_NaI;}
  G4double GetThicknessNaI(){return Thickness_NaI;}
  G4double GetThicknessHousing(){return Thickness_Housing;}
  G4double GetThicknessAbsorber(){return Thickness_Absorber;}



private:
  Geometry *Geom;

  static const G4String path_bin;

  // Logical Volumes
  G4LogicalVolume *LogicalVolume;

  G4double Radius_NaI=0.0;
  G4double Thickness_NaI=0.0;
  G4double Thickness_Housing=0.0;
  G4double Thickness_Absorber=0.0;
  // Other
  G4VisAttributes *clear;

};
#endif
