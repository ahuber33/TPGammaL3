// TPGammaL3SimGeometry_test.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "TPGammaL3SimGeometry.hh"

using namespace CLHEP;

const G4String TPGammaL3SimGeometry::path_bin = "../bin/";

// Constructor
TPGammaL3SimGeometry::TPGammaL3SimGeometry()
{}

// Destructor
TPGammaL3SimGeometry::~TPGammaL3SimGeometry()
{}

void TPGammaL3SimGeometry::SetLogicalVolumeColor(G4LogicalVolume *LogicalVolume, G4String Color)
{
  // ***********************
  // Visualization Colors
  // ***********************
  // Create some colors for visualizations
  invis = new G4VisAttributes(G4Colour(255 / 255., 255 / 255., 255 / 255.));
  invis->SetVisibility(false);

  white = new G4VisAttributes(G4Colour(1, 1, 1, 0.1)); // Sets the color (can be looked up online)
  // white->SetForceWireframe(true); // Sets to wire frame mode for coloring the volume
  white->SetForceSolid(true); // Sets to solid mode for coloring the volume
  white->SetVisibility(true); // Makes color visible in visualization

  gray = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 1));
  //  gray->SetForceWireframe(true);
  gray->SetForceSolid(true);
  gray->SetVisibility(true);

  black = new G4VisAttributes(G4Colour(0, 0, 0, 1));
  //  black->SetForceWireframe(true);
  black->SetForceSolid(true);
  black->SetVisibility(true);

  red = new G4VisAttributes(G4Colour(1, 0, 0, 1));
  //  red->SetForceWireframe(true);
  red->SetForceSolid(true);
  red->SetVisibility(true);

  orange = new G4VisAttributes(G4Colour(1, 0.5, 0, 1));
  //  orange->SetForceWireframe(true);
  orange->SetForceSolid(true);
  orange->SetVisibility(true);

  yellow = new G4VisAttributes(G4Colour(1, 1, 0, 0.29));
  //  yellow->SetForceWireframe(true);
  yellow->SetForceSolid(true);
  yellow->SetVisibility(true);

  green = new G4VisAttributes(G4Colour(0, 1, 0, 0.35));
  //  green->SetForceWireframe(true);
  green->SetForceSolid(true);
  green->SetVisibility(true);

  cyan = new G4VisAttributes(G4Colour(0, 1, 1, 0.55));
  //  cyan->SetForceWireframe(true);
  cyan->SetForceSolid(true);
  cyan->SetVisibility(true);

  blue = new G4VisAttributes(G4Colour(0, 0, 1, 1));
  //  blue->SetForceWireframe(true);
  blue->SetForceSolid(true);
  blue->SetVisibility(true);

  magenta = new G4VisAttributes(G4Colour(1, 0, 1, 0.85));
  //  magenta->SetForceWireframe(true);
  // magenta->SetForceSolid(true);
  magenta->SetVisibility(true);

  if (Color == "invis")
  {
    LogicalVolume->SetVisAttributes(invis);
  }
  else if (Color == "black")
  {
    LogicalVolume->SetVisAttributes(black);
  }
  else if (Color == "white")
  {
    LogicalVolume->SetVisAttributes(white);
  }
  else if (Color == "gray")
  {
    LogicalVolume->SetVisAttributes(gray);
  }
  else if (Color == "red")
  {
    LogicalVolume->SetVisAttributes(red);
  }
  else if (Color == "orange")
  {
    LogicalVolume->SetVisAttributes(orange);
  }
  else if (Color == "yellow")
  {
    LogicalVolume->SetVisAttributes(yellow);
  }
  else if (Color == "green")
  {
    LogicalVolume->SetVisAttributes(green);
  }
  else if (Color == "cyan")
  {
    LogicalVolume->SetVisAttributes(cyan);
  }
  else if (Color == "blue")
  {
    LogicalVolume->SetVisAttributes(blue);
  }
  else if (Color == "magenta")
  {
    LogicalVolume->SetVisAttributes(magenta);
  }
}

void TPGammaL3SimGeometry::ConstructWorld()
{
  G4RotationMatrix DontRotate;
  DontRotate.rotateZ(0 * deg);
  DontRotate.rotateX(0 * deg);

  auto Material = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

  auto SolidWorld = new G4Box("SolidWorld", 50 * cm, 50 * cm, 50 * cm);
  LogicalWorld = new G4LogicalVolume(SolidWorld, Material, "LogicalWorld", 0, 0, 0);

  // Place the world volume: center of world at origin (0,0,0)
  PhysicalWorld = new G4PVPlacement(G4Transform3D(DontRotate, G4ThreeVector(0, 0, 0)), "PhysicalWorld", LogicalWorld, NULL, false, 0);
}

void TPGammaL3SimGeometry::ConstructNaI()
{
  G4RotationMatrix *stack_rot = new G4RotationMatrix;
  // G4double theta = -12*deg;
  stack_rot->rotateZ(0 * deg);
  stack_rot->rotateX(0 * deg);

  auto NaI = TPGammaL3SimMaterials::getInstance()->GetMaterial("NaI");
  // Alu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  // Cuivre = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
  // Etain = G4NistManager::Instance()->FindOrBuildMaterial("G4_Sn");
  // Plomb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
  // Titane = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ti");
  // Fer = G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");
  // Tantale = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ta");


  auto LogicalNaI = Geom->GetCylinderVolume("NaI", 0, Radius_NaI, Thickness_NaI, NaI);
  
  SetLogicalVolumeColor(LogicalNaI, "yellow");

  
  auto physiNaI = new G4PVPlacement(stack_rot,                               // no rotation
                                               G4ThreeVector(0, 0, 0), // position
                                               LogicalNaI,                    // its logical volume
                                               "NaI",
                                               LogicalWorld, // its mother  volume
                                               false,        // no boolean operations
                                               0,
                                               false);
}


void TPGammaL3SimGeometry::ConstructHousing()
{
  G4RotationMatrix *stack_rot = new G4RotationMatrix;
  // G4double theta = -12*deg;
  stack_rot->rotateZ(0 * deg);
  stack_rot->rotateX(0 * deg);

  auto Alu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");

  auto LogicalHousing1 = Geom->GetCylinderVolume("LateralHousing", Radius_NaI+0.1, (Radius_NaI+0.1)+Thickness_Housing, Thickness_NaI, Alu);

  auto LogicalHousing2 = Geom->GetCylinderVolume("FrontHousing", 0, (Radius_NaI+0.1)+Thickness_Housing, Thickness_Housing, Alu);
  
  SetLogicalVolumeColor(LogicalHousing1, "gray");
  SetLogicalVolumeColor(LogicalHousing2, "gray");

  
  auto physiHousing1 = new G4PVPlacement(stack_rot,                               // no rotation
                                               G4ThreeVector(0, 0,0), // position
                                               LogicalHousing1,                    // its logical volume
                                               "LateralHousing",
                                               LogicalWorld, // its mother  volume
                                               false,        // no boolean operations
                                               0,
                                               false);


  auto physiHousing2 = new G4PVPlacement(stack_rot,                               // no rotation
                                              G4ThreeVector(0, 0, 0. -Thickness_NaI/2 -Thickness_Housing/2), // position
                                              LogicalHousing2,                    // its logical volume
                                              "FrontHousing",
                                              LogicalWorld, // its mother  volume
                                              false,        // no boolean operations
                                              0,
                                              false);                                               
}


void TPGammaL3SimGeometry::GetVariables()
{
  // Initialize scint classes
  Geom = new Geometry(path_bin + "TPGammaL3Sim.cfg");

  // ***********************
  // Various dimensions
  // ***********************
  Radius_NaI = Geom->GetRadiusNaI();
  Thickness_NaI = Geom->GetThicknessNaI();
  Thickness_Housing = Geom->GetThicknessHousing();
}

// Main Function: Builds Full block, coupling, and PMT geometries
G4VPhysicalVolume *TPGammaL3SimGeometry::Construct()
{
  GetVariables();

  ConstructWorld();
  ConstructNaI();
  ConstructHousing();

  // Returns world with everything in it and all properties set
  return PhysicalWorld;
}
