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
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
//
// File name:     G4MuDMElasticScattering
//
// Author:        Xudong Yu
//
// Creation date: 18.01.2024
//
//
// Class Description:
//
// This class manages the elastic scattering with DM process for muons.
// it inherites from G4VContinuousDiscreteProcess via G4VEnergyLossProcess.
//

// -------------------------------------------------------------------
//

#ifndef G4MuDMElasticScattering_h
#define G4MuDMElasticScattering_h 1

#include "G4VEnergyLossProcess.hh"
#include "globals.hh"
#include "G4VEmModel.hh"

class G4DMPhysics;
class G4Material;

class G4MuDMElasticScattering : public G4VEnergyLossProcess
{

public:

  explicit G4MuDMElasticScattering(G4DMPhysics* pPhys, const G4String& name = "muDMelasscat");

  ~G4MuDMElasticScattering() = default;

  G4bool IsApplicable(const G4ParticleDefinition& p) override;

  G4double MinPrimaryEnergy(const G4ParticleDefinition* p,
                            const G4Material*, G4double) override;


  // hide assignment operator
  G4MuDMElasticScattering & operator=(const G4MuDMElasticScattering &right) = delete;
  G4MuDMElasticScattering(const G4MuDMElasticScattering&) = delete;

  // print description in html
  void ProcessDescription(std::ostream&) const override;

protected:

  void InitialiseEnergyLossProcess(const G4ParticleDefinition*,
                                   const G4ParticleDefinition*) override;

private:

  G4DMPhysics* fDMPhysics;
  const G4ParticleDefinition* theParticle = nullptr;
  const G4ParticleDefinition* theBaseParticle = nullptr;

  G4double mass = 0.0;
  G4double ratio = 0.0;

  G4bool isInitialised = false;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
