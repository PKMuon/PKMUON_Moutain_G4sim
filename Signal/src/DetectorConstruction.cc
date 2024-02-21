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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"

#include "G4DM.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4PhysicalConstants.hh"  //twopi
#include "G4LogicalSkinSurface.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4GenericTrap.hh"
#include "G4UserLimits.hh"
#include "Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),fScoringVolume(nullptr)
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
     delete vacum;
     delete air;
     delete pb;
     delete cu;
     delete cuLess;
     delete pbMore;
     delete kapton;
     delete kaptonLess;
     delete gasMixture;
     delete fStepLimit;
     delete fStepLimit_Gem;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  G4cout << "Defining the materials" << G4endl;
  // Get nist material manager
  G4NistManager* nistManager = G4NistManager::Instance();
  // Build materials
  vacum   = nistManager->FindOrBuildMaterial("G4_Galactic");
  air   = nistManager->FindOrBuildMaterial("G4_AIR");
  pb   = nistManager->FindOrBuildMaterial("G4_Pb");
  fe   = nistManager->FindOrBuildMaterial("G4_Fe");
  w   = nistManager->FindOrBuildMaterial("G4_W");
  cu   = nistManager->FindOrBuildMaterial("G4_Cu");

  G4cout<<"define high density Pb"<<G4endl;
  // define high density Pb
  G4int nComponent;
  G4double fracmass=1.0;
  pbMore   = new G4Material("pbMore",11.34*1*g/cm3,nComponent=1);
  pbMore -> AddMaterial(pb,fracmass);

  G4cout<<"define low density Cu"<<G4endl;
  // define low density Cu
  G4double ratio_outter = 0.77790212; // 1-(3600*pi)/(29400*sqrt(3))
  G4double density = ratio_outter * 8.94 * g/cm3;
  cuLess   = new G4Material("cuLess",density,nComponent=1);
  cuLess -> AddMaterial(cu,fracmass);

  G4cout<<"define Kapton"<<G4endl;
  // Define Kapton material
  density = 1.42 * g/cm3; // Density of Kapton
  kapton = new G4Material("Kapton", density, 3);
  kapton->AddElement(nistManager->FindOrBuildElement("H"), 0.0273);
  kapton->AddElement(nistManager->FindOrBuildElement("C"), 0.7213);
  kapton->AddElement(nistManager->FindOrBuildElement("O"), 0.2514);

  G4double ratio_inner = 0.81183374; // 1-(3600*pi+2500*pi)/2/(29400*sqrt(3))
  density = ratio_inner * 1.42 * g/cm3; // Density of Kapton
  kaptonLess = new G4Material("KaptonLess", density, 3);
  kaptonLess->AddElement(nistManager->FindOrBuildElement("H"), 0.0273);
  kaptonLess->AddElement(nistManager->FindOrBuildElement("C"), 0.7213);
  kaptonLess->AddElement(nistManager->FindOrBuildElement("O"), 0.2514);

  G4cout<<"define mixgass"<<G4endl;
  // Define 70%Ar and 30%CO2 gas mixture
  density = 1.822 * mg/cm3; // Density of the gas mixture
  gasMixture = new G4Material("ArCO2GasMixture", density, 3);
  gasMixture->AddElement(nistManager->FindOrBuildElement("Ar"), 0.7);
  gasMixture->AddElement(nistManager->FindOrBuildElement("C"), 0.3/3);
  gasMixture->AddElement(nistManager->FindOrBuildElement("O"), 0.3/3*2);

  G4cout<<"define detector material"<<G4endl;
  // Define detector material
  Gem_driftcathode_Mat = cu;
  Gem_foil_inner_Mat = kaptonLess;
  Gem_foil_outter_Mat = cuLess;
  Gem_readout_Mat = cu;
  Gem_Mat = gasMixture;
  world_Mat = air;
  //world_Mat = vacum;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineConstants()
{
  pi=CLHEP::pi;

  global_x=10*km; 
  global_y=10*km; 

  //global_x=10*m; 
  //global_y=10*m; 

  Gem_foil_outter_x=global_x;
  Gem_foil_outter_y=global_y;
  Gem_foil_outter_z=5*um;

  Gem_foil_inner_x=global_x;
  Gem_foil_inner_y=global_y;
  Gem_foil_inner_z=50*um;

  Gem_foil_x=global_x;
  Gem_foil_y=global_y;
  Gem_foil_z=Gem_foil_outter_z*2+Gem_foil_inner_z*1;

  Gem_driftcathode_x=global_x;
  Gem_driftcathode_y=global_y;
  Gem_driftcathode_z=0.1*mm;

  Gem_readout_x=global_x;
  Gem_readout_y=global_y;
  Gem_readout_z=0.2*mm;

  Gem_gap1 = 4.8*mm;
  Gem_gap2 = 2*mm;
  Gem_x=global_x;
  Gem_y=global_y;
  Gem_z=
        Gem_gap1
        +num_Gem_inner*Gem_gap2
        +num_Gem_inner*Gem_foil_z
        //+(num_Gem_outter*Gem_foil_outter_z+num_Gem_inner*Gem_foil_inner_z)
        +Gem_driftcathode_z
        +Gem_readout_z;

  atmosphere_x=global_x;
  atmosphere_y=global_y;
  atmosphere_z=100*m;

  experimentalHall_x=atmosphere_x+1*m;
  experimentalHall_y=atmosphere_y+1*m;
  experimentalHall_z=atmosphere_z+1*m;
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *DetectorConstruction::DefineVolumes()
{

    /*******************************
   * Gem drift cathode      *
   *******************************/
  G4VSolid* Gem_driftcathode_box
    = new G4Box("Gem_driftcathode_box", Gem_driftcathode_x/2, Gem_driftcathode_y/2, Gem_driftcathode_z/2);

  G4LogicalVolume* Gem_driftcathode_Log 
    = new G4LogicalVolume(Gem_driftcathode_box,
			  Gem_driftcathode_Mat,
                          "Gem_driftcathode_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits
  Gem_driftcathode_Log->SetVisAttributes(G4VisAttributes::GetInvisible());

    /*******************************
   * Gem foil o      *
   *******************************/
  G4VSolid* Gem_foil_o_box
    = new G4Box("Gem_foil_o_box", Gem_foil_outter_x/2, Gem_foil_outter_y/2, Gem_foil_outter_z/2);

  G4LogicalVolume* Gem_foil_o_Log 
    = new G4LogicalVolume(Gem_foil_o_box,
			  Gem_foil_outter_Mat,
                          "Gem_foil_o_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits
  Gem_foil_o_Log->SetVisAttributes(G4VisAttributes::GetInvisible());

    /*******************************
   * Gem foil i     *
   *******************************/
  G4VSolid* Gem_foil_i_box
    = new G4Box("Gem_foil_i_box", Gem_foil_inner_x/2, Gem_foil_inner_y/2, Gem_foil_inner_z/2);

  G4LogicalVolume* Gem_foil_i_Log 
    = new G4LogicalVolume(Gem_foil_i_box,
			  Gem_foil_inner_Mat,
                          "Gem_foil_i_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits
  Gem_foil_i_Log->SetVisAttributes(G4VisAttributes::GetInvisible());

    /*******************************
   * Gem foil     *
   *******************************/
  G4VSolid* Gem_foil_box
    = new G4Box("Gem_foil_box", Gem_foil_x/2, Gem_foil_y/2, Gem_foil_z/2);

  G4LogicalVolume* Gem_foil_Log 
    = new G4LogicalVolume(Gem_foil_box,
			  Gem_foil_inner_Mat,
                          "Gem_foil_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits
  Gem_foil_Log->SetVisAttributes(G4VisAttributes::GetInvisible());

  // put Gem foil o1 in Gem foil
  Zcenter = (Gem_foil_inner_z+Gem_foil_outter_z)/2;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_foil_o_Log,             //its logical volume
                    "Gem_foil_o1_Phys",                //its name
                    Gem_foil_Log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

  // put Gem foil o2 in Gem foil
  Zcenter = -(Gem_foil_inner_z+Gem_foil_outter_z)/2;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_foil_o_Log,             //its logical volume
                    "Gem_foil_o2_Phys",                //its name
                    Gem_foil_Log,                //its mother  volume
                    false,                   //no boolean operation
                    1,                       //copy number
                    1);          //overlaps checking

  // put Gem foil i in Gem foil
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,0),                    //at position
                    Gem_foil_i_Log,             //its logical volume
                    "Gem_foil_i_Phys",                //its name
                    Gem_foil_Log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

    /*******************************
   * Gem Readout       *
   *******************************/
  G4VSolid* Gem_readout_box
    = new G4Box("Gem_readout_box", Gem_readout_x/2, Gem_readout_y/2, Gem_readout_z/2);

  G4LogicalVolume* Gem_readout_Log 
    = new G4LogicalVolume(Gem_readout_box,
			  Gem_readout_Mat,
                          "Gem_readout_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits
  Gem_readout_Log->SetVisAttributes(G4VisAttributes::GetInvisible());

    /*******************************
   * Gem       *
   *******************************/
  G4VSolid* Gem_box
    = new G4Box("Gem_box", Gem_x/2, Gem_y/2, Gem_z/2);

  G4LogicalVolume* Gem_Log 
    = new G4LogicalVolume(Gem_box,
			  Gem_Mat,
                          "Gem_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits
  Gem_Log->SetVisAttributes(G4VisAttributes::GetInvisible());

  //G4double maxStep_Gem = 1*um;
  //fStepLimit_Gem = new G4UserLimits(maxStep_Gem);
  //Gem_Log->SetUserLimits(fStepLimit_Gem);

  // put Gem component in Gem
  Zcenter = - Gem_z/2 + Gem_driftcathode_z/2;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_driftcathode_Log,             //its logical volume
                    "Gem_driftcathode_Phys",                //its name
                    Gem_Log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

  Zcenter += (Gem_driftcathode_z/2 + Gem_gap1 + Gem_foil_z/2);
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_foil_Log,             //its logical volume
                    "Gem_foil_1_Phys",                //its name
                    Gem_Log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

  Zcenter += (Gem_foil_z/2 + Gem_gap2 + Gem_foil_z/2);
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_foil_Log,             //its logical volume
                    "Gem_foil_2_Phys",                //its name
                    Gem_Log,                //its mother  volume
                    false,                   //no boolean operation
                    1,                       //copy number
                    1);          //overlaps checking

  Zcenter += (Gem_foil_z/2 + Gem_gap2 + Gem_foil_z/2);
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_foil_Log,             //its logical volume
                    "Gem_foil_3_Phys",                //its name
                    Gem_Log,                //its mother  volume
                    false,                   //no boolean operation
                    2,                       //copy number
                    1);          //overlaps checking

  Zcenter += (Gem_foil_z/2 + Gem_gap2 + Gem_readout_z/2);
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_readout_Log,             //its logical volume
                    "Gem_readout_Phys",                //its name
                    Gem_Log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

    /*******************************
   * The atmosphere gap       *
   *******************************/

  G4VSolid* atmosphere_box 
    = new G4Box("atmosphere_box",             // atmosphere Volume
                atmosphere_x/2,        // x size
                atmosphere_y/2,        // y size
                atmosphere_z/2);       // z size
  
  G4LogicalVolume* atmosphere_Log 
    = new G4LogicalVolume(atmosphere_box,
			  world_Mat,
                          "atmosphere_Log",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits

  G4double maxStep = 500*m;
  fStepLimit = new G4UserLimits(maxStep);
  atmosphere_Log->SetUserLimits(fStepLimit);

    /*******************************
   * The Experimental Hall       *
   *******************************/

  G4VSolid* experimentalHall_box 
    = new G4Box("expHall_box",             // World Volume
                experimentalHall_x/2,        // x size
                experimentalHall_y/2,        // y size
                experimentalHall_z/2);       // z size
  
  G4LogicalVolume* experimentalHallLog 
    = new G4LogicalVolume(experimentalHall_box,
			  world_Mat,
                          "expHallLog",
                          0,               //opt: fieldManager
                          0,               //opt: SensitiveDetector
                          0);              //opt: UserLimits

  G4VPhysicalVolume* experimentalHallPhys 
    = new G4PVPlacement(0,
                        G4ThreeVector(),   //at (0,0,0)
                        "expHall",
                        experimentalHallLog,
                        0,
                        false, 
                        0);
    
  experimentalHallLog->SetVisAttributes(G4VisAttributes::GetInvisible());

  // put Gem upper 1 in world
  Zcenter = - atmosphere_z/2 - Gem_z - Gem_z/2;
  G4cout<<"upper Gem 1 = "<<Zcenter<<G4endl;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_Log,             //its logical volume
                    "Gem_u1_Phys",                //its name
                    experimentalHallLog,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

  // put Gem upper 2 in world
  Zcenter = - atmosphere_z/2 - Gem_z/2;
  G4cout<<"upper Gem 2 = "<<Zcenter<<G4endl;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_Log,             //its logical volume
                    "Gem_u2_Phys",                //its name
                    experimentalHallLog,                //its mother  volume
                    false,                   //no boolean operation
                    1,                       //copy number
                    1);          //overlaps checking

  // put Gem lower 1 in world
  Zcenter = atmosphere_z/2 + Gem_z/2;
  G4cout<<"lower Gem 1 = "<<Zcenter<<G4endl;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_Log,             //its logical volume
                    "Gem_l1_Phys",                //its name
                    experimentalHallLog,                //its mother  volume
                    false,                   //no boolean operation
                    2,                       //copy number
                    1);          //overlaps checking

  // put Gem lower 2 in world
  Zcenter = atmosphere_z/2 + Gem_z + Gem_z/2;
  G4cout<<"lower Gem 2 = "<<Zcenter<<G4endl;
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,Zcenter),                    //at position
                    Gem_Log,             //its logical volume
                    "Gem_l2_Phys",                //its name
                    experimentalHallLog,                //its mother  volume
                    false,                   //no boolean operation
                    3,                       //copy number
                    1);          //overlaps checking

  // put atmosphere gap in world
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,0),                    //at position
                    atmosphere_Log,             //its logical volume
                    "atmosphere_Phys",                //its name
                    experimentalHallLog,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    1);          //overlaps checking

  fScoringVolume = Gem_readout_Log;

  // visualization attributes ------------------------------------------------

  auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  visAttributes->SetVisibility(false);
  experimentalHallLog->SetVisAttributes(visAttributes);

  //visAttributes = new G4VisAttributes(G4Colour(233/256.,206/256.,238./256,0.1));
  visAttributes = new G4VisAttributes(G4Colour(1,1,1,0.1));   // LightGray
  Gem_Log->SetVisAttributes(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(1,0.5,0,0.8));
  visAttributes->SetForceSolid(true);
  Gem_driftcathode_Log->SetVisAttributes(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0,0,1,0.8));
  visAttributes->SetForceSolid(true);
  Gem_foil_i_Log->SetVisAttributes(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(1,0,1,0.8));
  visAttributes->SetForceSolid(true);
  Gem_foil_o_Log->SetVisAttributes(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0,1,0,0.8));
  visAttributes->SetForceSolid(true);
  Gem_readout_Log->SetVisAttributes(visAttributes);

  return experimentalHallPhys;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4cout << "Construt the DetectorGeometry" <<G4endl;
  
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // define a material
  DefineMaterials();
    
  // define some constant
  DefineConstants();

  // Define volumes
  return DefineVolumes();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
