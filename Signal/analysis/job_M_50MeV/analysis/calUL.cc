#include "TH1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "/home/pku/yuxd/bond/useful/boot.h"

double L2sigma(double M, double L){

//M in unit of GeV
//L in unit of cm

double rho = 0.3; //GeV/cm3
double ndm = rho/M;
double sigma = 1 / ndm / L;
return sigma;

}

void calUL(){

TFile* fhistbkg = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/root/Hist.root");
TFile* fhistsig = new TFile("Hist.root");

TH1D *hbkg = (TH1D*)fhistbkg->Get("hsea");
hbkg->Print();

double L[7]={10,100,1000,10000,100000,1000000,10000000};

TH1D *hsig_M_500MeV_L_10km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10km");
hsig_M_500MeV_L_10km->Print();

TH1D *hsig_M_500MeV_L_100km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_100km");
hsig_M_500MeV_L_100km->Print();

TH1D *hsig_M_500MeV_L_1000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_1000km");
hsig_M_500MeV_L_1000km->Print();

TH1D *hsig_M_500MeV_L_10000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10000km");
hsig_M_500MeV_L_10000km->Print();

TH1D *hsig_M_500MeV_L_100000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_100000km");
hsig_M_500MeV_L_100000km->Print();

TH1D *hsig_M_500MeV_L_1000000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_1000000km");
hsig_M_500MeV_L_1000000km->Print();

TH1D *hsig_M_500MeV_L_10000000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10000000km");
hsig_M_500MeV_L_10000000km->Print();

/*
double chi2;
cout<<"UU"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "UU,CHI2,P");
cout<<"UW"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "UW,CHI2,P");
cout<<"WW"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "WW,CHI2,P");
cout<<"NORM"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "NORM,UU,CHI2,P");

cout<<"after scale"<<endl;
hbkg->Scale(50./15.);
hsig_M_500MeV_L_100km->Scale(50.);
hbkg->Print();
hsig_M_500MeV_L_100km->Print();
cout<<"UU"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "UU,CHI2,P");
cout<<"UW"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "UW,CHI2,P");
cout<<"WW"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "WW,CHI2,P");
cout<<"NORM"<<endl;
chi2 = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "NORM,UU,CHI2,P");
cout<<hbkg->Chi2Test(hsig_M_500MeV_L_100km, "CHI2")/hbkg->Chi2Test(hsig_M_500MeV_L_100km, "CHI2/NDF")<<endl;
*/

hbkg->Scale(50./15.);
hsig_M_500MeV_L_10km->Scale(5000.);
hsig_M_500MeV_L_100km->Scale(50.);
hsig_M_500MeV_L_1000km->Scale(50.);
hsig_M_500MeV_L_10000km->Scale(50.);
hsig_M_500MeV_L_100000km->Scale(50.);
hsig_M_500MeV_L_1000000km->Scale(50.);
hsig_M_500MeV_L_10000000km->Scale(50.);

double pvalue_M_500MeV[7];
pvalue_M_500MeV[0] = hbkg->Chi2Test(hsig_M_500MeV_L_10km, "UU,NORM");
pvalue_M_500MeV[1] = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "UU,NORM");
pvalue_M_500MeV[2] = hbkg->Chi2Test(hsig_M_500MeV_L_1000km, "UU,NORM");
pvalue_M_500MeV[3] = hbkg->Chi2Test(hsig_M_500MeV_L_10000km, "UU,NORM");
pvalue_M_500MeV[4] = hbkg->Chi2Test(hsig_M_500MeV_L_100000km, "UU,NORM");
pvalue_M_500MeV[5] = hbkg->Chi2Test(hsig_M_500MeV_L_1000000km, "UU,NORM");
pvalue_M_500MeV[6] = hbkg->Chi2Test(hsig_M_500MeV_L_10000000km, "UU,NORM");

double ss_M_500MeV[7];
for (int i=0; i<7; i++) ss_M_500MeV[i] = sqrt(2) * TMath::ErfcInverse( pvalue_M_500MeV[i] );
for (int i=0; i<7; i++) cout<<"L="<<L[i]<<"km, pvalue="<<pvalue_M_500MeV[i]<<", significance="<<ss_M_500MeV[i]<<"sigma"<<endl;

double chi2_M_500MeV[7];
chi2_M_500MeV[0] = hbkg->Chi2Test(hsig_M_500MeV_L_10km, "UU,NORM,CHI2,P");
chi2_M_500MeV[1] = hbkg->Chi2Test(hsig_M_500MeV_L_100km, "UU,NORM,CHI2,P");
chi2_M_500MeV[2] = hbkg->Chi2Test(hsig_M_500MeV_L_1000km, "UU,NORM,CHI2,P");
chi2_M_500MeV[3] = hbkg->Chi2Test(hsig_M_500MeV_L_10000km, "UU,NORM,CHI2,P");
chi2_M_500MeV[4] = hbkg->Chi2Test(hsig_M_500MeV_L_100000km, "UU,NORM,CHI2,P");
chi2_M_500MeV[5] = hbkg->Chi2Test(hsig_M_500MeV_L_1000000km, "UU,NORM,CHI2,P");
chi2_M_500MeV[6] = hbkg->Chi2Test(hsig_M_500MeV_L_10000000km, "UU,NORM,CHI2,P");

double ndf = hbkg->GetNbinsX() - 1;
double pdf_M_500MeV[7];
for(int i=0; i<7; i++) pdf_M_500MeV[i] = ROOT::Math::chisquared_pdf(chi2_M_500MeV[i], ndf);

double km2cm = 1e5;
double sigma_M_500MeV[7];
for(int i=0; i<7; i++) sigma_M_500MeV[i] = L2sigma(0.5, L[i]*km2cm);
for (int i=0; i<7; i++) cout<<"L="<<L[i]<<"km, sigma="<<sigma_M_500MeV[i]<<endl;


TGraph* graph = new TGraph(7, sigma_M_500MeV, pdf_M_500MeV);

setStyle();
TCanvas* c1 = new TCanvas("c1", "Likelihood vs sigma", 800, 600);
setPad();

c1->SetLogx();

graph->SetMarkerStyle(20);
graph->SetMarkerSize(1.5);
graph->SetMarkerColor(kBlue);

graph->Draw("AP");

//graph->SetTitle("Array Data Plot");
graph->GetXaxis()->SetTitle("#sigma_{#mu,DM} (cm^{2})");
graph->GetYaxis()->SetTitle("Likelihood");

c1->Draw();
c1->Print("Likelihood_vs_xs.eps");

}

