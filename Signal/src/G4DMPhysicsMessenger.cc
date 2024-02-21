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
/// \file exoticphysics/dmparticle/src/G4DMPhysicsMessenger.cc
/// \brief Implementation of the G4DMPhysicsMessenger class
//
//
//---------------------------------------------------------------------------
//
// ClassName:   G4DMPhysicsMessenger
//
// Description: EM physics with a possibility to add PAI model
//
// Author:      V.Ivanchenko 01.09.2010
// Author:      Xudong 01.18.2024
//
//----------------------------------------------------------------------------
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4DMPhysicsMessenger.hh"

#include "G4DMPhysics.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4DMPhysicsMessenger::G4DMPhysicsMessenger(G4DMPhysics* pPhys)
:G4UImessenger(),fDMPhysics(pPhys)
{   
  fPhysDir = new G4UIdirectory("/pkmuon/phys/");
  fPhysDir->SetGuidance("physics list commands");

  fMCmd = new G4UIcmdWithADoubleAndUnit("/pkmuon/phys/setDMmass",this);  
  fMCmd->SetGuidance("Set DM mass");
  fMCmd->SetParameterName("mass",false);
  fMCmd->SetUnitCategory("Mass");
  fMCmd->SetRange("mass>0.0");
  fMCmd->SetDefaultUnit("GeV");
  fMCmd->SetUnitCandidates("eV KeV MeV GeV TeV PeV");
  fMCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fXSCmd = new G4UIcmdWithADoubleAndUnit("/pkmuon/phys/setDMxs",this);  
  fXSCmd->SetGuidance("Set DM cross section");
  fXSCmd->SetParameterName("xs",false);
  //fXSCmd->SetDefaultUnit("m");//it will automatically convert values into that in unit of m, can not open it
  fXSCmd->SetUnitCandidates("fm nm um mm cm m km");
  fXSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4DMPhysicsMessenger::~G4DMPhysicsMessenger()
{
  delete fMCmd;
  delete fXSCmd;
  delete fPhysDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4DMPhysicsMessenger::SetNewValue(G4UIcommand* command,
                                       G4String newValue)
{       
  if (command == fMCmd) {
    G4cout << "\n---> DM mass from file: " << newValue << G4endl;
    fDMPhysics->SetDMMass(fMCmd->GetNewDoubleValue(newValue));
  }
  if (command == fXSCmd) {
    G4cout << "\n---> DM xs from file: " << newValue << G4endl;
    double rawvalue = fXSCmd->GetNewDoubleRawValue(newValue);
G4cout<<"rawvalue = "<<rawvalue<<G4endl;
    double unitvalue = fXSCmd->GetNewUnitValue(newValue);
    double newvalue = rawvalue*(1/unitvalue)/(1/CLHEP::mm); //new value in the unit of mm^-1
    fDMPhysics->SetDMXS(newvalue);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

