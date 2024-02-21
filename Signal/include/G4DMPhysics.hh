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
/// \file exoticphysics/dmparticle/include/G4DMPhysics.hh
/// \brief Definition of the G4DMPhysics class
//
//
/////////////////////////////////////////////////
//
// ClassName:   G4DMPhysics
//
// Authors:  01.06.17 V.Ivanchenko 
// Authors:  01.18.24 Xudong
//
//
///////////////////////////////////////////

#ifndef G4DMPhysics_h
#define G4DMPhysics_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4VPhysicsConstructor;
class G4DMPhysicsMessenger;
class StepMax;

class G4DMPhysics: public G4VPhysicsConstructor
{
public:

  G4DMPhysics();
  virtual ~G4DMPhysics();

  virtual void ConstructParticle();
    
  virtual void SetCuts();
        
  virtual void ConstructProcess();

  void AddG4DMPhysics(const G4String& name);

  void SetDMMass(G4double val);
  double GetDMMass() {return fDMMass;};
  void SetDMXS(G4double val);
  double GetDMXS() {return fDMXS;};

private:

  void AddDarkMatter(); 

  G4VPhysicsConstructor*  fEmG4DMPhysics;
  G4VPhysicsConstructor*  fDecayG4DMPhysics;
  G4String                fEmName;
    
  G4DMPhysicsMessenger* fMessenger;

  G4double fDMMass; 
  G4double fDMXS; 

  G4bool fDM;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

