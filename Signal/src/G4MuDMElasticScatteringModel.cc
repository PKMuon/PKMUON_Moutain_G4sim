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
// Creation date: 01.18.2024
//

//
// -------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4MuDMElasticScatteringModel.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Electron.hh"
#include "G4LossTableManager.hh"
#include "G4EmCorrections.hh"
#include "G4ParticleChangeForLoss.hh"
#include "G4Log.hh"
#include "G4Exp.hh"
#include "G4DMPhysics.hh"
#include <TTree.h>
#include "Run.hh"
#include <TTree.h>
#include "TVector3.h"
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TGenPhaseSpace.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4MuDMElasticScatteringModel::G4MuDMElasticScatteringModel(G4DMPhysics* pPhys, const G4ParticleDefinition* p,
                                         const G4String& nam)
  : G4VEmModel(nam), fDMPhysics(pPhys)
{
  if(nullptr != p) { SetParticle(p); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4MuDMElasticScatteringModel::SetParticle(const G4ParticleDefinition* p)
{
  if(nullptr == particle) {
    particle = p;
    mass = particle->GetPDGMass();
    massSquare = mass*mass;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4MuDMElasticScatteringModel::Initialise(const G4ParticleDefinition* p,
                                     const G4DataVector&)
{
  SetParticle(p);
  if(nullptr == fParticleChange) { 
    fParticleChange = GetParticleChangeForLoss();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double G4MuDMElasticScatteringModel::CrossSectionPerVolume(
                                           const G4Material* material,
                                           const G4ParticleDefinition* p,
                                                 G4double kineticEnergy,
                                                 G4double cutEnergy,
                                                 G4double maxEnergy)
{
  G4double xs = fDMPhysics->GetDMXS(); //unit is mm^-1
  return xs; // unit is mm^-1
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double G4MuDMElasticScatteringModel::ComputeDEDXPerVolume(const G4Material* material,
                                                  const G4ParticleDefinition* p,
                                                  G4double kineticEnergy,
                                                  G4double cut)
{
  return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4MuDMElasticScatteringModel::SampleSecondaries(
                          std::vector<G4DynamicParticle*>* vdp,
			  const G4MaterialCutsCouple*,
			  const G4DynamicParticle* dp,
			  G4double minKinEnergy,
			  G4double maxEnergy)
{
  TLorentzVector p4;
  p4.SetPx(dp->Get4Momentum().px()/MeV);
  p4.SetPy(dp->Get4Momentum().py()/MeV);
  p4.SetPz(dp->Get4Momentum().pz()/MeV);
  p4.SetE(dp->Get4Momentum().e()/MeV);

  //DM
  G4double vDM = 220*km/s;
  G4double Beta = vDM/CLHEP::c_light;
  G4double mDM0 = fDMPhysics->GetDMMass();
  G4double mDM = mDM0/(sqrt(1-Beta*Beta));
  G4double EkinDM = 0.5*mDM*vDM;
  G4double pDM = sqrt(2*mDM*EkinDM);

  G4double pxDM = pDM/MeV, pyDM=0, pzDM=0;
  mDM = mDM/MeV;
  G4double EDM = sqrt(mDM*mDM+pDM*pDM);
  TLorentzVector p4DM(pxDM,pyDM,pzDM,EDM);

  TLorentzVector beam = p4;
  TLorentzVector target = p4DM;
  TLorentzVector W = beam + target;
  //(Momentum, Energy units are Mev/C, MeV)
  G4double masses[2] = {dp->GetMass()/MeV,mDM0/MeV} ;
  TGenPhaseSpace event;
  event.SetDecay(W, 2, masses);
  G4double weight = event.Generate();
  TLorentzVector *beamAfterScatter = event.GetDecay(0);
  G4double pxbeam=beamAfterScatter->Px();
  G4double pybeam=beamAfterScatter->Py();
  G4double pzbeam=beamAfterScatter->Pz();
  G4double Ebeam=beamAfterScatter->E();

  // primary change
  G4double kineticEnergy = (Ebeam-(beamAfterScatter->M()))*MeV;
  G4ThreeVector direction;
  direction.setX(beamAfterScatter->Vect().Unit().X());
  direction.setY(beamAfterScatter->Vect().Unit().Y());
  direction.setZ(beamAfterScatter->Vect().Unit().Z());
  fParticleChange->SetProposedKineticEnergy(kineticEnergy);
  fParticleChange->SetProposedMomentumDirection(direction);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
