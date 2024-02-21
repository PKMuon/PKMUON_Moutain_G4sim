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
// File name:     G4MuDMElasticScatteringModel
//
// Author:        Xudong Yu
//
// Creation date: 09.08.2002
//
// Class Description:
//
// Implementation of DM muon elastic scattering model of energy loss and momentum direction change

// -------------------------------------------------------------------
//

#ifndef G4MuDMElasticScatteringModel_h
#define G4MuDMElasticScatteringModel_h 1

#include "G4VEmModel.hh"

class G4DMPhysics;
class G4ParticleChangeForLoss;

class G4MuDMElasticScatteringModel : public G4VEmModel
{

public:

  explicit G4MuDMElasticScatteringModel(G4DMPhysics* pPhys, const G4ParticleDefinition* p = nullptr,
                               const G4String& nam = "MuDMElasticScattering");

  ~G4MuDMElasticScatteringModel() = default;

  void Initialise(const G4ParticleDefinition*, const G4DataVector&) override;

  G4double CrossSectionPerVolume(const G4Material*,
				 const G4ParticleDefinition*,
				 G4double kineticEnergy,
				 G4double cutEnergy,
				 G4double maxEnergy) override;

  G4double ComputeDEDXPerVolume(const G4Material*,
                                const G4ParticleDefinition*,
                                G4double kineticEnergy,
                                G4double cutEnergy) override;

  void SampleSecondaries(std::vector<G4DynamicParticle*>*,
				const G4MaterialCutsCouple*,
				const G4DynamicParticle*,
				G4double tmin,
				G4double maxEnergy) override;

  // hide assignment operator
  G4MuDMElasticScatteringModel & operator=(const  G4MuDMElasticScatteringModel &right) = delete;
  G4MuDMElasticScatteringModel(const  G4MuDMElasticScatteringModel&) = delete;

private:

  G4DMPhysics* fDMPhysics;
  void SetParticle(const G4ParticleDefinition* p);

  const G4ParticleDefinition* particle = nullptr;
  G4ParticleChangeForLoss*    fParticleChange = nullptr;

  G4double mass = 1.0;
  G4double massSquare = 1.0;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#endif
