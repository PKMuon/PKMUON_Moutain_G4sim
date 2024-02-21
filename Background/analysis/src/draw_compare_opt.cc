#include "boot.h"
void draw_compare_opt(){

TFile *fopt2 = new TFile("../root/muCry_opt2.root");
TFile *fopt4 = new TFile("../root/muCry.root");

TTree* topt2       = (TTree*)fopt2->Get("T1");
TTree* topt4       = (TTree*)fopt4->Get("T1");

setStyle();
gStyle->SetTitleYOffset(1.0);     // Y title offset
gStyle->SetTitleXOffset(0.8);     // X title offset

TCanvas *can = new TCanvas("can","can",800,600);setPad();
gPad->SetBottomMargin(0.12);       // pad bottom margin for writing X title
gPad->SetRightMargin(0.02);       // pad right margin  for writing Y title
gPad->SetTopMargin(0.02);         // pad top margin for writing X title
can->SetLogy();

double xbins=100, xmin=0, xmax=1;

TH1D *hopt2       = new TH1D("hopt2","hopt2",xbins,xmin,xmax);
TH1D *hopt4       = new TH1D("hopt4","hopt4",xbins,xmin,xmax);

TString a("Events/"); char b[20];  sprintf(b, "(%.2f",(xmax-xmin)/xbins); TString c(")");
TString ytitle = a + b + c;
TString xtitle="cos#it{#theta}";

TCut cut="flag_Gem3==1 && flag_Gem4==1";
TString var="costheta_smear_Sea";

//project
topt2->Project("hopt2",var,cut);
topt4->Project("hopt4",var,cut);

hopt2->SetLineColor(1);
hopt4->SetLineColor(2);

hopt4->Scale((hopt2->Integral())/(hopt4->Integral()));

//hopt2->SetMaximum();
hopt2->SetMinimum(0.1);
hopt2->Draw("e");
hopt2->GetXaxis()->SetTitle(xtitle);
hopt2->GetYaxis()->SetTitle(ytitle);
hopt4->Draw("hist,same");

TLegend *legend = new TLegend(0.65,0.30,0.85,0.50,NULL,"brNDC");
legend->AddEntry(hopt2,"opt2","lep");
legend->AddEntry(hopt4,"opt4","F");
setLegend(legend);
legend->Draw();

TPaveText* text = new TPaveText(0.2, 0.9, 0.3, 0.95, "NDC");
text->AddText(Form("Sea"));
text->Draw();

gPad->RedrawAxis();

can->Update();
can->Print("../figure/costheta_compare_opt24.eps");
}
