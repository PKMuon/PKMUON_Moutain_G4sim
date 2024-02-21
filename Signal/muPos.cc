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
/// \file rdecay01.cc
/// \brief Main program of the radioactivedecay/rdecay01 example
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "GetSeedFromTime.hh"
#include "TRandom3.h"
#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4DMPhysics.hh"

#include <iostream>
#include <chrono>

int main(int argc,char** argv) {
  auto start = std::chrono::high_resolution_clock::now();

  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if (argc == 1) ui = new G4UIExecutive(argc,argv);

  
  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  unsigned long seed = GetSeedFromTime();
  G4cout << "seed=" <<seed<< G4endl;
  CLHEP::HepRandom::setTheSeed(seed);
  G4Random::setTheSeed(seed);
  gRandom->SetSeed(seed);
  //construct the default run manager
  //#ifdef G4MULTITHREADED
  //G4MTRunManager* runManager = new G4MTRunManager;
  //runManager->SetNumberOfThreads(std::min(4,G4Threading::G4GetNumberOfCores()));
  //#else
  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);
  G4RunManager* runManager = new G4RunManager;
  //#endif

  //set mandatory initialization classes
  //
  DetectorConstruction* det;
  runManager->SetUserInitialization(det = new DetectorConstruction);
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  //G4VModularPhysicsList* physicsList = new QBBC;
  //physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  //physicsList->ReplacePhysics(new G4EmStandardPhysics_option3());
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option2());
  //physicsList->ReplacePhysics(new G4EmStandardPhysics_option1());
  //physicsList->ReplacePhysics(new G4EmStandardPhysics());
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());

  // dm physics is added
  G4DMPhysics * theDM = new G4DMPhysics();

  // regsiter monopole physics
  physicsList->RegisterPhysics(theDM);

  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new ActionInitialization(det));

  //initialize G4 kernel
  runManager->Initialize();

  //initialize visualization
  G4VisManager* visManager = nullptr;

  //get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui)  {
   //interactive mode
   visManager = new G4VisExecutive;
   visManager->Initialize();
   UImanager->ApplyCommand("/control/execute vis.mac");
   ui->SessionStart();
   delete ui;
  }
  else  {
   //batch mode
   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   UImanager->ApplyCommand(command+fileName);
  }

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Total Running time: " << duration.count() << " ms" << std::endl;

  //job termination
  delete visManager;
  delete runManager;
}

