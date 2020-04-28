//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file visualization/standalone/src/StandaloneVisAction.cc
/// \brief Implementation of the StandaloneVisAction class
//
//
// $Id: StandaloneVisAction.cc 69587 2013-05-08 14:26:03Z gcosmo $

#include "StandaloneVisAction.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"
// #include <CLHEP/Units/PhysicalConstants.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StandaloneVisAction::Draw() {
  G4VVisManager* pVisManager = G4VVisManager::GetConcreteInstance();
  if (pVisManager) {

    // size parameter, unit [cm]
    // cavern
    G4double stone = 100.0;       // Hall wall thickness 1 m
    G4double hallhside = 850.0; // Hall cube side 17 m
    // cryostat
    G4double tankhside = 650;   // cryostat cube side 13 m
    G4double outerwall = 1.2;     // outer SS wall thickness
    G4double insulation = 80.0;   // polyurethane foam
    G4double innerwall = 0.12;    // inner SS membrane
    // copper tubes with Germanium ROI
    G4double copper = 0.05;      // tube thickness 0.5 mm
    G4double curad = 40.0;       // copper tube diam 80 cm
    G4double cuhheight = 334.34;  // copper tube height 7 m inside cryostat
    G4double cushift = 234.34;    // shift cu tube inside cryostat to top
    G4double ringrad = 100.0;    // cu tube placement ring radius
    // Ge cylinder for 250 kg at 5.32 g/cm3
    G4double roiradius = 25.0;      // detector region diam 50 cm
    G4double roihalfheight = 11.97; // detector region height 24 cm
    
    // total
    G4double offset = hallhside - tankhside; // shift cavern floor to keep detector centre at origin
    G4double worldside = hallhside + stone + offset + 0.1; // larger than rest
    G4double larside = tankhside-outerwall-insulation-innerwall; // cube side of LAr volume


  // volumes
    G4Box world("World",  worldside*cm, worldside*cm, worldside*cm); // larger than rest
    pVisManager->Draw(world, G4VisAttributes(G4Colour::Gray()));

    G4Box cavernbox("Cavern", (hallhside+stone)*cm, (hallhside+stone)*cm, (hallhside+stone)*cm); // shift to world top
    pVisManager->Draw(cavernbox, G4VisAttributes(G4Colour::White()), G4Translate3D(0.*cm, 0.*cm, offset*cm));

    G4Box hallbox("Hall", hallhside*cm, hallhside*cm, hallhside*cm); // Hall volume
    pVisManager->Draw(hallbox, G4VisAttributes(G4Colour::Cyan()), G4Translate3D(0.*cm, 0.*cm, offset*cm));

    G4Box tankbox("Cout", tankhside*cm, tankhside*cm, tankhside*cm); // Cryostat tank wall
    pVisManager->Draw(tankbox, G4VisAttributes(G4Colour::Grey()));

    G4Box waterbox("insulator", (tankhside-outerwall)*cm, (tankhside-outerwall)*cm, (tankhside-outerwall)*cm); // inside outer wall
    pVisManager->Draw(waterbox, G4VisAttributes(G4Colour::Blue()));

    G4Box cryoouterbox("membrane", (tankhside-outerwall-insulation)*cm, (tankhside-outerwall-insulation)*cm, (tankhside-outerwall-insulation)*cm);  // inside insulation
    pVisManager->Draw(cryoouterbox, G4VisAttributes(G4Colour::Green()));

    G4Box larbox("LAr", larside*cm, larside*cm, larside*cm); // liquid argon volume inside membrane
    pVisManager->Draw(larbox, G4VisAttributes(G4Colour::White()));

    // core parts
    G4Tubs cutub("Cu", 0.0*cm, curad*cm, cuhheight*cm, 0.0, CLHEP::twopi);  // Cu tube
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()), G4Translate3D(ringrad*cm, 0.*cm, cushift*cm));
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()), G4Translate3D(0.*cm, ringrad*cm, cushift*cm));
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()), G4Translate3D(-ringrad*cm, 0.*cm, cushift*cm));
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()), G4Translate3D(0.*cm, -ringrad*cm, cushift*cm));

    G4Tubs innerlartub("UAr", 0.0*cm, (curad-copper)*cm, cuhheight*cm, 0.0, CLHEP::twopi);  // UAr filling tube
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()), G4Translate3D(ringrad*cm, 0.*cm, cushift*cm));
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()), G4Translate3D(0.*cm, ringrad*cm, cushift*cm));
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()), G4Translate3D(-ringrad*cm, 0.*cm, cushift*cm));
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()), G4Translate3D(0.*cm, -ringrad*cm, cushift*cm));

    G4Tubs roitub("Ge", 0.0*cm, roiradius*cm, roihalfheight*cm, 0.0, CLHEP::twopi);  // 250 kg Ge tube
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()), G4Translate3D(ringrad*cm, 0.*cm, 0.*cm));
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()), G4Translate3D(0.*cm, ringrad*cm, 0.*cm));
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()), G4Translate3D(-ringrad*cm, 0.*cm, 0.*cm));
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()), G4Translate3D(0.*cm, -ringrad*cm, 0.*cm));

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
