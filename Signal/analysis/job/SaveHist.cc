#include "boot.h"
void SaveHist(){

const char* MassName[8]={"5MeV","50MeV","100MeV","200MeV","500MeV","1GeV","10GeV","100GeV"};
const char* FreePathName[3]={"10m","100m","10000m"};

TFile* fout = new TFile("./Hist.root","recreate");

TH1D *hmountain[8][3];
TH1D *hsea[8][3];

double xbins=100, xmin=0, xmax=1;
for(int i=0; i<8; i++){
  for(int j=0; j<3; j++){
	TFile *f = new TFile(Form("job_M_%s_L_%s/all.root",MassName[i],FreePathName[j]),"");
	TTree *t = (TTree*)f->Get("T1");

	setStyle();
	gStyle->SetTitleYOffset(1.0);     // Y title offset
	gStyle->SetTitleXOffset(0.8);     // X title offset

	TCanvas *can = new TCanvas("can","can",800,600);setPad();
	gPad->SetBottomMargin(0.12);       // pad bottom margin for writing X title
	gPad->SetRightMargin(0.02);       // pad right margin  for writing Y title
	gPad->SetTopMargin(0.02);         // pad top margin for writing X title
	can->SetLogy();

	hmountain[i][j]       = new TH1D(Form("hmountain_M_%s_L_%s",MassName[i],FreePathName[j]),"hmountain",xbins,xmin,xmax);
	hsea[i][j]            = new TH1D(Form("hsea_M_%s_L_%s",MassName[i],FreePathName[j]),"hsea",xbins,xmin,xmax);

	TString a("Events/"); char b[20];  sprintf(b, "(%.2f",(xmax-xmin)/xbins); TString c(")");
	TString ytitle = a + b + c;
	TString xtitle="cos#it{#theta}";

	TCut cut="flag_Gem3==1 && flag_Gem4==1";

	//project
	t->Project(Form("hmountain_M_%s_L_%s",MassName[i],FreePathName[j]),"costheta_smear_Mountain","1");
	t->Project(Form("hsea_M_%s_L_%s",MassName[i],FreePathName[j]),"costheta_smear_Sea",cut);

	fout->cd();
	hmountain[i][j]->Write();
	hsea[i][j]->Write();

  }
}
fout->Close();

}
