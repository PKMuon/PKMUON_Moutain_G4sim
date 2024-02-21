#include "boot.h"
void Ratio(){

TFile* fhistbkg = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/root/Hist.root");
TFile* fhistsig = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Signal/analysis/job/Hist.root");

const char* L[3]={"10","100","10000"};

for(int j=0; j<3; j++){

TH1D *h_sea_0p005 = (TH1D*)fhistsig->Get(Form("hsea_M_5MeV_L_%sm",L[j]));
TH1D *h_sea_0p05 = (TH1D*)fhistsig->Get(Form("hsea_M_50MeV_L_%sm",L[j]));
TH1D *h_sea_0p1 = (TH1D*)fhistsig->Get(Form("hsea_M_100MeV_L_%sm",L[j]));
TH1D *h_sea_0p2 = (TH1D*)fhistsig->Get(Form("hsea_M_200MeV_L_%sm",L[j]));
TH1D *h_sea_0p5 = (TH1D*)fhistsig->Get(Form("hsea_M_500MeV_L_%sm",L[j]));
TH1D *h_sea_1 = (TH1D*)fhistsig->Get(Form("hsea_M_1GeV_L_%sm",L[j]));
TH1D *h_sea_10 = (TH1D*)fhistsig->Get(Form("hsea_M_10GeV_L_%sm",L[j]));
TH1D *h_sea_100 = (TH1D*)fhistsig->Get(Form("hsea_M_100GeV_L_%sm",L[j]));

TH1D *h_mountain_0p005 = (TH1D*)fhistsig->Get(Form("hmountain_M_5MeV_L_%sm",L[j]));
TH1D *h_mountain_0p05 = (TH1D*)fhistsig->Get(Form("hmountain_M_50MeV_L_%sm",L[j]));
TH1D *h_mountain_0p1 = (TH1D*)fhistsig->Get(Form("hmountain_M_100MeV_L_%sm",L[j]));
TH1D *h_mountain_0p2 = (TH1D*)fhistsig->Get(Form("hmountain_M_200MeV_L_%sm",L[j]));
TH1D *h_mountain_0p5 = (TH1D*)fhistsig->Get(Form("hmountain_M_500MeV_L_%sm",L[j]));
TH1D *h_mountain_1 = (TH1D*)fhistsig->Get(Form("hmountain_M_1GeV_L_%sm",L[j]));
TH1D *h_mountain_10 = (TH1D*)fhistsig->Get(Form("hmountain_M_10GeV_L_%sm",L[j]));
TH1D *h_mountain_100 = (TH1D*)fhistsig->Get(Form("hmountain_M_100GeV_L_%sm",L[j]));

cout<<endl<<"L = "<<L[j]<<" m"<<endl;
double ratio_0p005 = (double)(h_sea_0p005->Integral())/(double)(h_mountain_0p005->Integral());
double ratio_0p05 = (double)(h_sea_0p05->Integral())/(double)(h_mountain_0p05->Integral());
double ratio_0p1 = (double)(h_sea_0p1->Integral())/(double)(h_mountain_0p1->Integral());
double ratio_0p2 = (double)(h_sea_0p2->Integral())/(double)(h_mountain_0p2->Integral());
double ratio_0p5 = (double)(h_sea_0p5->Integral())/(double)(h_mountain_0p5->Integral());
double ratio_1 = (double)(h_sea_1->Integral())/(double)(h_mountain_1->Integral());
double ratio_10 = (double)(h_sea_10->Integral())/(double)(h_mountain_10->Integral());
double ratio_100 = (double)(h_sea_100->Integral())/(double)(h_mountain_100->Integral());

cout<<"5MeV:   \t"<<ratio_0p005<<endl;
cout<<"50MeV:  \t"<<ratio_0p05<<endl;
cout<<"100MeV: \t"<<ratio_0p1<<endl;
cout<<"200MeV: \t"<<ratio_0p2<<endl;
cout<<"500MeV: \t"<<ratio_0p5<<endl;
cout<<"1GeV:   \t"<<ratio_1<<endl;
cout<<"10GeV:  \t"<<ratio_10<<endl;
cout<<"100GeV: \t"<<ratio_100<<endl;

}

TH1D *hbkg_sea = (TH1D*)fhistbkg->Get("hsea");
TH1D *hbkg_mountain = (TH1D*)fhistbkg->Get("hmountain");
double ratio_bkg = (double)(hbkg_sea->Integral())/(double)(hbkg_mountain->Integral());
cout<<endl<<"bkg: \t"<<ratio_bkg<<endl;

}
