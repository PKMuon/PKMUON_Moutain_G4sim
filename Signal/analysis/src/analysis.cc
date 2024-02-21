#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sys/time.h>
#include <TVector3.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>

using namespace std;
extern double Z1;
extern double Z2;
extern double Z3;
extern double Z4;

void analysis(){
TRandom *rand = new TRandom();
double sigma=100*0.001;

TFile *f = new TFile("../../build/root_file/muCRY_i.root","");
TTree *t = (TTree*)f->Get("T1");

double GemTrkPx[4], GemTrkPy[4], GemTrkPz[4], GemTrkE[4];
double GemTrkEdep[4];
double GemTrkX[4], GemTrkY[4], GemTrkZ[4];

t->SetBranchAddress("GemTrkPx",&GemTrkPx);
t->SetBranchAddress("GemTrkPy",&GemTrkPy);
t->SetBranchAddress("GemTrkPz",&GemTrkPz);
t->SetBranchAddress("GemTrkE",&GemTrkE);
t->SetBranchAddress("GemTrkEdep",&GemTrkEdep);
t->SetBranchAddress("GemTrkX",&GemTrkX);
t->SetBranchAddress("GemTrkY",&GemTrkY);
t->SetBranchAddress("GemTrkZ",&GemTrkZ);
//t->Print();

//new file and new tree
TFile * fn = new TFile("../root/muCRY.root","recreate");
TTree * tn = new TTree("T1","tree");
tn = t->CloneTree(0);

double m_GemTrkX_smear[4], m_GemTrkY_smear[4];
double m_muon_Edep_Mountain, m_muon_Edep_Sea;
double m_muon_E_Mountain, m_muon_E_Sea;
double m_costheta_Mountain, m_costheta_smear_Mountain;
double m_costheta_Sea, m_costheta_smear_Sea;
int m_flag_Gem3, m_flag_Gem4;
tn->Branch("GemTrkX_smear", m_GemTrkX_smear, "GemTrkX_smear[4]/D");
tn->Branch("GemTrkY_smear", m_GemTrkY_smear, "GemTrkY_smear[4]/D");
tn->Branch("costheta_Mountain", &m_costheta_Mountain, "costheta_Mountain/D");
tn->Branch("costheta_smear_Mountain", &m_costheta_smear_Mountain, "costheta_smear_Mountain/D");
tn->Branch("costheta_Sea", &m_costheta_Sea, "costheta_Sea/D");
tn->Branch("costheta_smear_Sea", &m_costheta_smear_Sea, "costheta_smear_Sea/D");
tn->Branch("muon_Edep_Mountain", &m_muon_Edep_Mountain, "muon_Edep_Mountain/D");
tn->Branch("muon_Edep_Sea", &m_muon_Edep_Sea, "muon_Edep_Sea/D");
tn->Branch("muon_E_Mountain", &m_muon_E_Mountain, "muon_E_Mountain/D");
tn->Branch("muon_E_Sea", &m_muon_E_Sea, "muon_E_Sea/D");
tn->Branch("flag_Gem3", &m_flag_Gem3, "flag_Gem3/I");
tn->Branch("flag_Gem4", &m_flag_Gem4, "flag_Gem4/I");

struct timeval start;
struct timeval end;
unsigned long timer;

gettimeofday(&start, NULL); // 计时开始

int nevent = t->GetEntries();
for(int ievent=0; ievent<nevent; ievent++){
        if (ievent % (int)(nevent / 10) == 0) cout << "Processing progress: " << ievent / (int)(nevent / 10) << "0%" << endl;
        t->GetEntry(ievent);
//cout<<endl<<"ievent = "<<ievent<<endl;

//	if(GemTrkZ[2]==0) m_flag_Gem3=0;
//	else if(GemTrkZ[2]!=0) m_flag_Gem3=1;
//	if(GemTrkZ[3]==0) m_flag_Gem4=0;
//	else if(GemTrkZ[3]!=0) m_flag_Gem4=1;

	if(fabs(GemTrkZ[2]-0)<0.1) m_flag_Gem3=0;
	else if(fabs(GemTrkZ[2]-0)>0.1) m_flag_Gem3=1;
	if(fabs(GemTrkZ[3]-0)<0.1) m_flag_Gem4=0;
	else if(fabs(GemTrkZ[3]-0)>0.1) m_flag_Gem4=1;

        for(int igem=0; igem<4; igem++){
        m_GemTrkX_smear[igem] = GemTrkX[igem]+rand->Gaus(0,sigma);
        m_GemTrkY_smear[igem] = GemTrkY[igem]+rand->Gaus(0,sigma);
        }

        // angle <incoming vector, outcoming vector>
        TVector3 *Pos1 = new TVector3(GemTrkX[0],GemTrkY[0],GemTrkZ[0]);
        TVector3 *Pos2 = new TVector3(GemTrkX[1],GemTrkY[1],GemTrkZ[1]);
        TVector3 *Pos3 = new TVector3(GemTrkX[2],GemTrkY[2],GemTrkZ[2]);
        TVector3 *Pos4 = new TVector3(GemTrkX[3],GemTrkY[3],GemTrkZ[3]);
        TVector3 Vec_muon_Mountain = *Pos2 - *Pos1;
        TVector3 Vec_muon_Sea = *Pos4 - *Pos3;
        TVector3 Vec_vertical(0,0,1);
        m_costheta_Mountain = cos(Vec_vertical.Angle(Vec_muon_Mountain));
        m_costheta_Sea = cos(Vec_vertical.Angle(Vec_muon_Sea));
//cout<<"m_costheta_Mountain = "<<m_costheta_Mountain<<endl;
//cout<<"m_costheta_Sea = "<<m_costheta_Sea<<endl;
//for(int ii=0; ii<4; ii++){
//	cout<<"GemTrkX = "<<GemTrkX[0]<<" , "<<GemTrkX[1]<<" , "<<GemTrkX[2]<<" , "<<GemTrkX[3]<<endl;
//	cout<<"GemTrkY = "<<GemTrkY[0]<<" , "<<GemTrkY[1]<<" , "<<GemTrkY[2]<<" , "<<GemTrkY[3]<<endl;
//	cout<<"GemTrkZ = "<<GemTrkZ[0]<<" , "<<GemTrkZ[1]<<" , "<<GemTrkZ[2]<<" , "<<GemTrkZ[3]<<endl;
//}

        TVector3 *Pos1_smear = new TVector3(m_GemTrkX_smear[0],m_GemTrkY_smear[0],GemTrkZ[0]);
        TVector3 *Pos2_smear = new TVector3(m_GemTrkX_smear[1],m_GemTrkY_smear[1],GemTrkZ[1]);
        TVector3 *Pos3_smear = new TVector3(m_GemTrkX_smear[2],m_GemTrkY_smear[2],GemTrkZ[2]);
        TVector3 *Pos4_smear = new TVector3(m_GemTrkX_smear[3],m_GemTrkY_smear[3],GemTrkZ[3]);
        TVector3 Vec_muon_smear_Mountain = *Pos2_smear - *Pos1_smear;
        TVector3 Vec_muon_smear_Sea = *Pos4_smear - *Pos3_smear;
        m_costheta_smear_Mountain = cos(Vec_vertical.Angle(Vec_muon_smear_Mountain));
        m_costheta_smear_Sea = cos(Vec_vertical.Angle(Vec_muon_smear_Sea));
//cout<<"m_costheta_smear_Mountain = "<<m_costheta_smear_Mountain<<endl;
//cout<<"m_costheta_smear_Sea = "<<m_costheta_smear_Sea<<endl;
//for(int ii=0; ii<4; ii++){
//	cout<<"m_GemTrkX_smear = "<<m_GemTrkX_smear[0]<<" , "<<m_GemTrkX_smear[1]<<" , "<<m_GemTrkX_smear[2]<<" , "<<m_GemTrkX_smear[3]<<endl;
//	cout<<"m_GemTrkY_smear = "<<m_GemTrkY_smear[0]<<" , "<<m_GemTrkY_smear[1]<<" , "<<m_GemTrkY_smear[2]<<" , "<<m_GemTrkY_smear[3]<<endl;
//}
        m_muon_Edep_Mountain = GemTrkEdep[1];
        m_muon_E_Mountain = GemTrkE[1];
        m_muon_Edep_Sea = GemTrkEdep[3];
        m_muon_E_Sea = GemTrkE[3];

        tn->Fill();
}
gettimeofday(&end, NULL); // 计时结束
timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
printf("time = %ld us\n", timer);

fn->cd();
fn->Write();
fn->Close();
f->Close();

}

