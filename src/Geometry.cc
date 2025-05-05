// Geometry.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "Geometry.hh"


using namespace CLHEP;

// ***********************
// Constructor
// ***********************
const G4String Geometry::path_bin = "../bin/";

// Fonction pour lire un tableau entre accolades {valeurs}
template <typename T>
std::vector<T> ParseArray(const std::string &line)
{
  std::vector<T> values;
  std::string content = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1); // Récupère les valeurs entre {}
  std::stringstream ss(content);
  T value;

  while (ss >> value)
  {
    values.push_back(value); // Ajoute les valeurs au vecteur
    if (ss.peek() == ',')    // Ignore les virgules
      ss.ignore();
  }

  return values;
}

Geometry::Geometry(G4String buildfile)
{
  // Read keys and values from file buildfile defined in x_blockGeometry.cc
  // Some of these variables may not be needed.
  G4cout << "\n The Variables that we read in are: " << G4endl;

  std::ifstream config;
  config.open(buildfile);
  if (!config.is_open())
    G4cout << "Error opening file " << buildfile << G4endl;
  else
  {
    while (config.is_open())
    {
      G4String variable;
      G4String unit;
      G4double value;

      config >> variable;
      if (!config.good())
        break;
      // ####################### COMMON variables ###########################
      if (variable == "Radius_NaI")
      {
        config >> value >> unit;
        Radius_NaI = value * G4UnitDefinition::GetValueOf(unit);
      }      
      else if (variable == "Thickness_NaI")
      {
        config >> value >> unit;
        Thickness_NaI = value * G4UnitDefinition::GetValueOf(unit);
      }      
      else if (variable == "Thickness_Housing")
      {
        config >> value >> unit;
        Thickness_Housing = value * G4UnitDefinition::GetValueOf(unit);
      }      
    }
  }
  config.close();

  G4cout << "\n Radius_NaI = " << Radius_NaI
         << "\n Thickness NaI = " << Thickness_NaI 
         << "\n Thickness Housing = " << Thickness_Housing 
         << "\n " << G4endl;
}
// ***********************
// Destructor
// ***********************
Geometry::~Geometry()
{}

G4LogicalVolume *Geometry::GetCylinderVolume(G4String name, G4double InternalRadius, G4double ExternalRadius, G4double Thickness, G4Material *Material)
{

  auto solid = new G4Tubs("solid_"+name, InternalRadius, ExternalRadius, (Thickness / 2) * mm, 0., 360. * deg);
  auto LogicalVolume = new G4LogicalVolume(solid, Material, "logical_"+name);

  return LogicalVolume;
}

