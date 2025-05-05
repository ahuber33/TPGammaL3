/// TPGammaL3SimMaterials.cc
/// Auteur: Arnaud HUBER <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "TPGammaL3SimMaterials.hh"

using namespace CLHEP;

TPGammaL3SimMaterials *TPGammaL3SimMaterials::fgInstance = nullptr;


TPGammaL3SimMaterials::TPGammaL3SimMaterials() : fMaterialsList{}
{
	G4double a, z, fractionmass;
	G4double density, pressure, temperature;
	G4double R = 8.3144621; //(en J/K/mole => Constante gaz parfait)
	G4int nel;
	density = 1.e-25 * g / cm3;
	pressure = 1.e-19 * pascal;
	temperature = 0.1 * kelvin;

	// Sodium
	auto elementNa = new G4Element("Sodium", "Na", z = 11., a = 22.989 * g / mole);
	// Iodure
	auto elementI = new G4Element("Iode", "I", z = 53., a = 126.90447 * g / mole);

	//***********************
	// Build Materials      *
	//***********************

	auto NaI = new G4Material("NaI", density = 3.67 * g / cm3, nel = 2);
	NaI->AddElement(elementI, fractionmass = 0.8466);
	NaI->AddElement(elementNa, fractionmass = 0.1534);
	fMaterialsList.push_back(NaI);

}

TPGammaL3SimMaterials::~TPGammaL3SimMaterials()
{
}

G4Material *TPGammaL3SimMaterials::GetMaterial(const char *materialId)
{
	for (int i = 0; i < (int)fMaterialsList.size(); i++)
	{
		if (fMaterialsList[i]->GetName() == materialId)
		{
			G4cout << "Material : " << materialId << " found" << G4endl;
			return fMaterialsList[i];
		}
	}
	G4cout << "ERROR: Materials::getMaterial material " << materialId << " not found." << G4endl;
	return NULL;
}

TPGammaL3SimMaterials *TPGammaL3SimMaterials::getInstance()
{
	static TPGammaL3SimMaterials materials;
	if (fgInstance == nullptr)
	{
		fgInstance = &materials;
	}
	return fgInstance;
}
