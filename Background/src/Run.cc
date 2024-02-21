//
// 2020.5.8 by siguang wang (siguang@pku.edu.cn  PKU)
//


#include <TTree.h>
#include "Run.hh"
#include <TTree.h>
#include "TVector3.h"
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TMath.h>
#include <TRandom3.h>
#include "TClonesArray.h"
#include <iostream>
#include "RunMessenger.hh"
#include "G4SystemOfUnits.hh"

static Run*  instance = 0;

Run::Run()
  :  fRunMessenger(0)
{
   totEdep=0;
  _GunEng = 0;
  rootFileName = "test.root";
  fRunMessenger = new RunMessenger(this);
}

Run::~Run() {
 
  delete fRunMessenger;
}

Run*  Run::GetInstance()
{
  if (instance == 0 )
    {
      instance = new Run();
    }
  return instance;
}


void Run::initTree() {
  std::cout << "Init Tree File." << std::endl;
  _file = new TFile(rootFileName.c_str(), "RECREATE");
  _tree = new TTree("T1", "Simple Out Tree");

//  _tree->Branch("GemTrkID", &GemTrkID, "GemTrkID[4]/I");
//  _tree->Branch("GemTrkMID", &GemTrkMID, "GemTrkMID[4]/I");
  _tree->Branch("GemTrkPx", &GemTrkPx, "GemTrkPx[4]/D");
  _tree->Branch("GemTrkPy", &GemTrkPy, "GemTrkPy[4]/D");
  _tree->Branch("GemTrkPz", &GemTrkPz, "GemTrkPz[4]/D");
  _tree->Branch("GemTrkE", &GemTrkE, "GemTrkE[4]/D");
  _tree->Branch("GemTrkEdep", &GemTrkEdep, "GemTrkEdep[4]/D");
  _tree->Branch("GemTrkX", &GemTrkX, "GemTrkX[4]/D");
  _tree->Branch("GemTrkY", &GemTrkY, "GemTrkY[4]/D");
  _tree->Branch("GemTrkZ", &GemTrkZ, "GemTrkZ[4]/D");

  totEdep = 0;
  _GunEng =0;
  cosTh=-2;
  status=false;
  X0=0;
  Y0=0;
  Z0=0;
  px0=0;
  py0=0;
  pz0=0;

  vX.clear();
  vY.clear();
  vZ.clear(); 

  vEdep.clear();
  vTrkID.clear();
 
  vReadoutTrkid.clear();
  vReadoutTrkparentid.clear();
  vReadoutE.clear();
  vReadoutEdep.clear();
  vReadoutPosX.clear();
  vReadoutPosY.clear();
  vReadoutPosZ.clear();
  vPx.clear();
  vPy.clear();
  vPz.clear();
  vPbTrkid.clear();
  vPbPosX.clear();
  vPbPosY.clear();
  vPbPosZ.clear();

  std::vector<Double_t>().swap(vEdep);
  std::vector<Double_t>().swap(vX);
  std::vector<Double_t>().swap(vY);
  std::vector<Double_t>().swap(vZ);
  std::vector<Int_t>().swap(vTrkID);
  std::vector<Int_t>().swap(vReadoutTrkid);
  std::vector<Int_t>().swap(vReadoutTrkparentid);
  std::vector<Double_t>().swap(vReadoutE);
  std::vector<Double_t>().swap(vReadoutEdep);
  std::vector<Double_t>().swap(vReadoutPosX);
  std::vector<Double_t>().swap(vReadoutPosY);
  std::vector<Double_t>().swap(vReadoutPosZ);
  std::vector<Double_t>().swap(vPx);
  std::vector<Double_t>().swap(vPy);
  std::vector<Double_t>().swap(vPz);
  std::vector<Int_t>().swap(vPbTrkid);
  std::vector<Double_t>().swap(vPbPosX);
  std::vector<Double_t>().swap(vPbPosY);
  std::vector<Double_t>().swap(vPbPosZ);
  
  for (int i=0; i<4; i++)
  {
    GemTrkID[i]=0;
    GemTrkMID[i]=0;
    GemTrkPx[i]=0;
    GemTrkPy[i]=0;
    GemTrkPz[i]=0;
    GemTrkE[i]=0;
    GemTrkEdep[i]=0;
    GemTrkX[i]=0;
    GemTrkY[i]=0;
    GemTrkZ[i]=0;
    GemTrkStatus[i]=false;
  }

  G4cout << "ROOT Name = " << rootFileName << G4endl;

}

void Run::AddEnergy1(double Eng1) {
  if(Eng1>0)  totEdep += Eng1 ;
}



void Run::SetPos(G4double inX,G4double inY,G4double inZ){
  X0 = inX;
  Y0 = inY;
  Z0 = inZ;
}

void Run::SetPxyz(G4double inX,G4double inY,G4double inZ){
  px0 = inX;
  py0 = inY;
  pz0 = inZ;
}

void Run::SetPosF(G4double fiX,G4double fiY,G4double fiZ){
  X1 = fiX;
  Y1 = fiY;
  Z1 = fiZ;
}

void Run::SetPxyzF(G4double fiX,G4double fiY,G4double fiZ){
  px1 = fiX;
  py1 = fiY;
  pz1 = fiZ;
}

void Run::ClearAll(){
  totEdep = 0;
  _GunEng =0;
  cosTh=-2;
  status=false;

  X0=0;
  Y0=0;
  Z0=0;
  
  px0=0;
  py0=0;
  pz0=0;
  
  X1=0;
  Y1=0;
  Z1=0;
  
  px1=0;
  py1=0;
  pz1=0;

  vX.clear();
  vY.clear();
  vZ.clear(); 
  vEdep.clear();
  vTrkID.clear();

  vReadoutTrkid.clear();
  vReadoutTrkparentid.clear();
  vReadoutE.clear();
  vReadoutEdep.clear();
  vReadoutPosX.clear();
  vReadoutPosY.clear();
  vReadoutPosZ.clear();
  vPx.clear();
  vPy.clear();
  vPz.clear();
  vPbTrkid.clear();
  vPbPosX.clear();
  vPbPosY.clear();
  vPbPosZ.clear();

  std::vector<Double_t>().swap(vEdep);
  std::vector<Double_t>().swap(vX);
  std::vector<Double_t>().swap(vY);
  std::vector<Double_t>().swap(vZ);
  std::vector<Int_t>().swap(vTrkID);
  std::vector<Int_t>().swap(vReadoutTrkid);
  std::vector<Int_t>().swap(vReadoutTrkparentid);
  std::vector<Double_t>().swap(vReadoutE);
  std::vector<Double_t>().swap(vReadoutEdep);
  std::vector<Double_t>().swap(vReadoutPosX);
  std::vector<Double_t>().swap(vReadoutPosY);
  std::vector<Double_t>().swap(vReadoutPosZ);
  std::vector<Double_t>().swap(vPx);
  std::vector<Double_t>().swap(vPy);
  std::vector<Double_t>().swap(vPz);
  std::vector<Int_t>().swap(vPbTrkid);
  std::vector<Double_t>().swap(vPbPosX);
  std::vector<Double_t>().swap(vPbPosY);
  std::vector<Double_t>().swap(vPbPosZ);
 
  for (int i=0; i<4; i++)
  {
    GemTrkID[i]=0;
    GemTrkMID[i]=0;
    GemTrkPx[i]=0;
    GemTrkPy[i]=0;
    GemTrkPz[i]=0;
    GemTrkE[i]=0;
    GemTrkEdep[i]=0;
    GemTrkX[i]=0;
    GemTrkY[i]=0;
    GemTrkZ[i]=0;
    GemTrkStatus[i]=false;
  }
}

void Run::SetGemTrkID(int i, int ID){
  GemTrkID[i]=ID;
}

void Run::SetGemTrkMID(int i, int MID){
  GemTrkMID[i]=MID;
}

void Run::SetGemTrkPx(int i, double Px){
  GemTrkPx[i]=Px;
}

void Run::SetGemTrkPy(int i, double Py){
  GemTrkPy[i]=Py;
}

void Run::SetGemTrkPz(int i, double Pz){
  GemTrkPz[i]=Pz;
}

void Run::SetGemTrkE(int i, double E){
  GemTrkE[i]=E;
}

void Run::SetGemTrkEdep(int i, double Edep){
  GemTrkEdep[i]=Edep;
}

void Run::SetGemTrkX(int i, double X){
  GemTrkX[i]=X;
}

void Run::SetGemTrkY(int i, double Y){
  GemTrkY[i]=Y;
}

void Run::SetGemTrkZ(int i, double Z){
  GemTrkZ[i]=Z;
}

void Run::SetGemTrkStatus(int i, bool status){
  GemTrkStatus[i]=status;
}

void Run::SetGemTruthZ(int i, double Z){
  GemTruthZ[i]=Z;
}

void  Run::AddX(G4double inX){
  vX.push_back(inX);
}
void  Run::AddY(G4double inY){
  vY.push_back(inY);
}
void  Run::AddZ(G4double inZ){
  vZ.push_back(inZ);
}
void  Run::AddEdep(G4double inE){
  vEdep.push_back(inE);
}

void  Run::AddTrkID(G4int iTrkID){
  vTrkID.push_back(iTrkID);
}

void  Run::AddReadoutEdepX(G4double X){
  vReadoutPosX.push_back(X);
}

void  Run::AddReadoutEdepY(G4double Y){
  vReadoutPosY.push_back(Y);
}

void  Run::AddReadoutEdepZ(G4double Z){
  vReadoutPosZ.push_back(Z);
}

void  Run::AddPbEdepX(G4double X){
  vPbPosX.push_back(X);
}

void  Run::AddPbEdepY(G4double Y){
  vPbPosY.push_back(Y);
}

void  Run::AddPbEdepZ(G4double Z){
  vPbPosZ.push_back(Z);
}

void  Run::AddReadoutE(G4double E){
  vReadoutE.push_back(E);
}

void  Run::AddReadoutEdep(G4double E){
  vReadoutEdep.push_back(E);
}

void  Run::AddPx(G4double X){
  vPx.push_back(X);
}

void  Run::AddPy(G4double Y){
  vPy.push_back(Y);
}

void  Run::AddPz(G4double Z){
  vPz.push_back(Z);
}

void  Run::AddReadoutTrkid(G4int i){
  vReadoutTrkid.push_back(i);
}

void  Run::AddReadoutTrkparentid(G4int i){
  vReadoutTrkparentid.push_back(i);
}

void  Run::AddPbTrkid(G4int i){
  vPbTrkid.push_back(i);
}

void Run::Fill(){
  _tree->Fill();
/*
  G4cout<<"this is Run::Fill function: size of vReadoutPosX is "<<vReadoutPosX.size()<<G4endl;
  for(int i=0; i<vReadoutPosX.size(); i++){
  G4cout<<"trk "<<i<<G4endl;
  G4cout<<"x = "<<vReadoutPosX[i]<<G4endl;
  G4cout<<"y = "<<vReadoutPosY[i]<<G4endl;
  G4cout<<"z = "<<vReadoutPosZ[i]<<G4endl;
  G4cout<<"e = "<<vReadoutEdep[i]<<G4endl;
  }
*/
  ClearAll();
}

void Run::saveTree(){
  _file->cd();
  _tree->Write("T1",TObject::kOverwrite);
  _file->Close();
}
