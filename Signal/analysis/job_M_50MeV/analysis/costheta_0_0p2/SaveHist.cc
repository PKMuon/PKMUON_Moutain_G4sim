#include "/home/pku/yuxd/bond/useful/boot.h"
void SaveHist(){

const int Nmass=8;
const int Npath=6;

const char* MassName[Nmass]={"5MeV","50MeV","100MeV","200MeV","500MeV","1GeV","10GeV","100GeV"};
const char* FreePathName[Npath]={"100km","1000km","10000km","100000km","1000000km","10000000km"};

TFile* fout = new TFile("./Hist.root","recreate");

TH1D *hmountain[Nmass][Npath];
TH1D *hsea[Nmass][Npath];

double xbins=100, xmin=0, xmax=0.2;
for(int i=0; i<Nmass; i++){
  if(strcmp(MassName[i],"500MeV")!=0) continue;
  for(int j=0; j<Npath; j++){
        cout<<"job_M_"<<MassName[i]<<"_L_"<<FreePathName[j]<<endl;

	//TFile *f = new TFile(Form("../job_M_%s_L_%s/all.root",MassName[i],FreePathName[j]),"");
	//TTree *t = (TTree*)f->Get("T1");

        TChain *t = new TChain("T1");
        t->Add(Form("../../job_M_%s_L_%s/newroot/*.root",MassName[i],FreePathName[j]));

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
