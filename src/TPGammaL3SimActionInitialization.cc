/// TPGammaL3SimRunAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@lp2ib.in2p3.fr>
//// Copyright: 2024 (C) Projet PALLAS

#include "TPGammaL3SimActionInitialization.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPGammaL3SimActionInitialization::TPGammaL3SimActionInitialization(TPGammaL3SimGeometry* Geom, const char *suff, G4bool pMT)
    : G4VUserActionInitialization(), 
      detector(Geom),
      suffixe(suff),
      flag_MT(pMT)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPGammaL3SimActionInitialization::~TPGammaL3SimActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPGammaL3SimActionInitialization::BuildForMaster() const
{
    // Action pour le processus maître (uniquement utile en mode multithreading)
    SetUserAction(new TPGammaL3SimRunAction(detector, suffixe, flag_MT));
    G4cout << "Build Master" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPGammaL3SimActionInitialization::Build() const
{
    // Création et affectation des actions pour la simulation
    auto *runAction = new TPGammaL3SimRunAction(detector, suffixe, flag_MT);
    auto *eventAction = new TPGammaL3SimEventAction(suffixe);
    
    // Assigner les actions utilisateur
    SetUserAction(new TPGammaL3SimPrimaryGeneratorAction());
    SetUserAction(runAction);
    SetUserAction(eventAction);
    SetUserAction(new TPGammaL3SimSteppingAction(detector, runAction, eventAction));
    //SetUserAction(new TPGammaL3SimTrackingAction());
}