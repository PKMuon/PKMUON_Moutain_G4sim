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
/// \file G4DMPhysics.cc
/// \brief Implementation of the G4DMPhysics class
//
//
/////////////////////////////////////////////////
//
// ClassName:   G4DMPhysics
//
// Authors:  01.06.17 V.Ivanchenko 
// Authors:  01.15.24 Xudong modify
//
//
///////////////////////////////////////////

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4DMPhysics.hh"
#include "G4DMPhysicsMessenger.hh"
#include "G4DM.hh"
#include "G4MuDMElasticScattering.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"
#include "G4ProductionCutsTable.hh"
#include "G4EmConfigurator.hh"
#include "G4EmParameters.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4DMPhysics::G4DMPhysics()
  :G4VPhysicsConstructor(),
   fDMMass(1*CLHEP::GeV),fDMXS(1/CLHEP::mm),fDM(true)
{ 
  fMessenger = new G4DMPhysicsMessenger(this);

  SetVerboseLevel(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4DMPhysics::~G4DMPhysics()
{
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4DMPhysics::ConstructParticle()
{
  if(fDM) { G4DM::DMDefinition(fDMMass); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4DMPhysics::ConstructProcess()
{
  AddDarkMatter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4DMPhysics::SetCuts()
{
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100.*eV,1e5);
  //if ( verboseLevel > 0 ) { DumpCutValuesTable(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4DMPhysics::AddDarkMatter()
{
  G4cout << " G4DMPhysics::AddDarkMatter: " << fDM << G4endl;
  if(fDM) {
    //G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    G4MuDMElasticScattering* mudmelasticscattering = new G4MuDMElasticScattering(this);
    G4ParticleDefinition* muminus = G4MuonMinus::MuonMinus();
    G4ParticleDefinition* muplus = G4MuonPlus::MuonPlus();
    G4ProcessManager* man_muminus = muminus->GetProcessManager();
    man_muminus->AddProcess(mudmelasticscattering, -1, -1, 5);
    G4ProcessManager* man_muplus= muplus->GetProcessManager();
    man_muplus->AddProcess(mudmelasticscattering, -1, -1, 5);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4DMPhysics::SetDMMass(G4double val) 
{ 
  G4cout << "### G4DMPhysics::SetDMMass: new value " << val/GeV
         << " GeV" << G4endl;
  fDMMass = val; 
  fDM = true; 
}

void G4DMPhysics::SetDMXS(G4double val) 
{ 
  G4cout << "### G4DMPhysics::SetDMXS: new value " << val
         << " mm^-1" << G4endl;
  fDMXS = val; 
  fDM = true; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
