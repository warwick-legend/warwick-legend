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

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Cons.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
// #include <CLHEP/Units/PhysicalConstants.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StandaloneVisAction::Draw()
{
  G4VVisManager* pVisManager = G4VVisManager::GetConcreteInstance();
  if(pVisManager)
  {
    // size parameter, unit [cm]
    G4double offset = 200.0;  // shift cavern floor to keep detector centre at origin
    // cavern
    G4double stone       = 100.0;  // Hall wall thickness 1 m
    G4double hallrad     = 600.0;  // Hall cylinder diam 12 m
    G4double hallhheight = 850.0;  // Hall cylinder height 17 m
    // water tank
    G4double tankwalltop = 0.6;  // water tank thickness at top 6 mm
    G4double tankwallbot = 0.8;  // water tank thickness at bottom 8 mm
    G4double tankrad     = 550;  // water tank diam 11 m
    G4double tankhheight = 650;  // water tank height 13 m
    // cryostat
    G4double cryowall   = 3.0;    // cryostat wall thickness from GERDA
    G4double vacgap     = 1.0;    // vacuum gap between walls
    G4double cryrad     = 350.0;  // cryostat diam 7 m
    G4double cryhheight = 350.0;  // cryostat height 7 m
    // copper tubes with Germanium ROI
    G4double copper    = 0.05;   // tube thickness 0.5 mm
    G4double curad     = 40.0;   // copper tube diam 80 cm
    G4double cuhheight = 200.0;  // copper tube height 4 m inside cryostat
    G4double cushift   = 150.0;  // shift cu tube inside cryostat to top
    G4double ringrad   = 100.0;  // cu tube placement ring radius
    // Ge cylinder for 250 kg at 5.32 g/cm3
    G4double roiradius     = 25.0;   // detector region diam 50 cm
    G4double roihalfheight = 11.97;  // detector region height 24 cm

    // volumes
    G4Tubs world("World", 0.0 * cm, (hallrad + stone + 0.1) * cm,
                 (hallhheight + stone + offset + 0.1) * cm, 0.0,
                 CLHEP::twopi);  // larger than rest
    pVisManager->Draw(world, G4VisAttributes(G4Colour::Gray()));

    G4Tubs caverntub("Cavern", 0.0 * cm, (hallrad + stone) * cm,
                     (hallhheight + stone) * cm, 0.0,
                     CLHEP::twopi);  // shift to world top
    pVisManager->Draw(caverntub, G4VisAttributes(G4Colour::White()),
                      G4Translate3D(0. * cm, 0. * cm, offset * cm));

    G4Tubs halltub("Hall", 0.0 * cm, hallrad * cm, hallhheight * cm, 0.0,
                   CLHEP::twopi);  // Hall volume
    pVisManager->Draw(halltub, G4VisAttributes(G4Colour::Cyan()),
                      G4Translate3D(0. * cm, 0. * cm, offset * cm));

    G4Cons tankcone("Tank", 0.0 * cm, (tankrad + tankwallbot) * cm, 0.0 * cm,
                    (tankrad + tankwalltop) * cm, tankhheight * cm, 0.0,
                    CLHEP::twopi);  // Water tank wall
    pVisManager->Draw(tankcone, G4VisAttributes(G4Colour::Grey()));

    G4Tubs watertub("Water", 0.0 * cm, tankrad * cm, (tankhheight - tankwallbot) * cm,
                    0.0, CLHEP::twopi);  // Water tank volume
    pVisManager->Draw(watertub, G4VisAttributes(G4Colour::Blue()));

    G4Tubs cryooutertub("Cout", 0.0 * cm, cryrad * cm, cryhheight * cm, 0.0,
                        CLHEP::twopi);  // cryostat outer volume
    pVisManager->Draw(cryooutertub, G4VisAttributes(G4Colour::Green()));

    G4Tubs cryovactub("Cvac", 0.0 * cm, (cryrad - cryowall) * cm, cryhheight * cm, 0.0,
                      CLHEP::twopi);  // cryostat vacuum gap volume
    pVisManager->Draw(cryovactub, G4VisAttributes(G4Colour::Grey()));

    G4Tubs cryoinnertub("Cinn", 0.0 * cm, (cryrad - cryowall - vacgap) * cm,
                        cryhheight * cm, 0.0, CLHEP::twopi);  // cryostat inner volume
    pVisManager->Draw(cryoinnertub, G4VisAttributes(G4Colour::Green()));

    G4Tubs lartub("Lar", 0.0 * cm, (cryrad - 2 * cryowall - vacgap) * cm, cryhheight * cm,
                  0.0, CLHEP::twopi);  // liquid argon volume
    pVisManager->Draw(lartub, G4VisAttributes(G4Colour::White()));

    G4Tubs lidtub("Lid", 0.0 * cm, cryrad * cm, cryowall / 2.0 * cm, 0.0,
                  CLHEP::twopi);  // close cryostat cylinder at top and bottom
    pVisManager->Draw(
      lidtub, G4VisAttributes(G4Colour::Grey()),
      G4Translate3D(0. * cm, 0. * cm, (cryhheight + cryowall / 2.0) * cm));
    pVisManager->Draw(
      lidtub, G4VisAttributes(G4Colour::Grey()),
      G4Translate3D(0. * cm, 0. * cm, -(cryhheight + cryowall / 2.0) * cm));

    G4Tubs cutub("Cu", 0.0 * cm, curad * cm, cuhheight * cm, 0.0,
                 CLHEP::twopi);  // Cu tube
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()),
                      G4Translate3D(ringrad * cm, 0. * cm, cushift * cm));
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()),
                      G4Translate3D(0. * cm, ringrad * cm, cushift * cm));
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()),
                      G4Translate3D(-ringrad * cm, 0. * cm, cushift * cm));
    pVisManager->Draw(cutub, G4VisAttributes(G4Colour::Red()),
                      G4Translate3D(0. * cm, -ringrad * cm, cushift * cm));

    G4Tubs innerlartub("UAr", 0.0 * cm, (curad - copper) * cm, cuhheight * cm, 0.0,
                       CLHEP::twopi);  // UAr filling tube
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()),
                      G4Translate3D(ringrad * cm, 0. * cm, cushift * cm));
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()),
                      G4Translate3D(0. * cm, ringrad * cm, cushift * cm));
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()),
                      G4Translate3D(-ringrad * cm, 0. * cm, cushift * cm));
    pVisManager->Draw(innerlartub, G4VisAttributes(G4Colour::Grey()),
                      G4Translate3D(0. * cm, -ringrad * cm, cushift * cm));

    G4Tubs roitub("Ge", 0.0 * cm, roiradius * cm, roihalfheight * cm, 0.0,
                  CLHEP::twopi);  // 250 kg Ge tube
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()),
                      G4Translate3D(ringrad * cm, 0. * cm, 0. * cm));
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()),
                      G4Translate3D(0. * cm, ringrad * cm, 0. * cm));
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()),
                      G4Translate3D(-ringrad * cm, 0. * cm, 0. * cm));
    pVisManager->Draw(roitub, G4VisAttributes(G4Colour::White()),
                      G4Translate3D(0. * cm, -ringrad * cm, 0. * cm));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
