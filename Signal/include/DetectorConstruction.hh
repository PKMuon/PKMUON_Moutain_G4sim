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
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"
#include "G4UserLimits.hh"
//#include "G4LogicalVolume.hh"
//#include "G4PVPlacement.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

    virtual     G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; };
    const G4Material*  GetMaterial() const  {return air;};
           
  // G4double GetWorldSize() {return fWorldSize;}; 

  private:
     void DefineMaterials();
     void DefineConstants();
     G4VPhysicalVolume* DefineVolumes();
     G4LogicalVolume*  fScoringVolume;

     G4Material* vacum;
     G4Material* air;
     G4Material* pb;
     G4Material* fe;
     G4Material* w;
     G4Material* cu;
     G4Material* cuLess;
     G4Material* pbMore;
     G4Material* kapton;
     G4Material* kaptonLess;
     G4Material* gasMixture;

     G4Material* Gem_driftcathode_Mat;
     G4Material* Gem_foil_inner_Mat;
     G4Material* Gem_foil_outter_Mat;
     G4Material* Gem_readout_Mat;
     G4Material* Gem_Mat;
     G4Material* world_Mat;

     G4double pi;

     G4double Xcenter, Ycenter, Zcenter;

     G4double global_x;
     G4double global_y;

     G4double Gem_foil_outter_x;
     G4double Gem_foil_outter_y;
     G4double Gem_foil_outter_z;

     G4double Gem_foil_inner_x;
     G4double Gem_foil_inner_y;
     G4double Gem_foil_inner_z;
                             
     G4double Gem_foil_x;
     G4double Gem_foil_y;
     G4double Gem_foil_z;
 
     G4double Gem_driftcathode_x;
     G4double Gem_driftcathode_y;
     G4double Gem_driftcathode_z;
     G4double Gem_readout_x;
     G4double Gem_readout_y;
     G4double Gem_readout_z;
     
     G4double Gem_gap1;
     G4double Gem_gap2;

     G4double Gem_x;
     G4double Gem_y;
     G4double Gem_z;
     
     const G4int num_Gem_outter=3*2;
     const G4int num_Gem_inner=3;

     G4double atmosphere_x;
     G4double atmosphere_y;
     G4double atmosphere_z;

     G4double experimentalHall_x;
     G4double experimentalHall_y;
     G4double experimentalHall_z;

     G4UserLimits* fStepLimit = nullptr; // pointer to user step limits
     G4UserLimits* fStepLimit_Gem = nullptr; // pointer to user step limits
     
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

