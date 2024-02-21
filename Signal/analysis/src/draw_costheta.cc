#include "boot.h"
void draw_costheta(const char* L){

TFile* fhistbkg = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/root/Hist.root");
TFile* fhistsig = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Signal/analysis/job/Hist.root");

setStyle();
TCanvas *can = new TCanvas("can","can",800,600);setPad();
gStyle->SetTitleYOffset(1.0);     // Y title offset
gStyle->SetTitleXOffset(0.8);     // X title offset
gPad->SetBottomMargin(0.12);       // pad bottom margin for writing X title
gPad->SetRightMargin(0.02);       // pad right margin  for writing Y title
gPad->SetTopMargin(0.02);         // pad top margin for writing X title
can->SetLogy();

TH1D *h_const_0p005 = (TH1D*)fhistsig->Get(Form("hsea_M_5MeV_L_%sm",L));
TH1D *h_const_0p05 = (TH1D*)fhistsig->Get(Form("hsea_M_50MeV_L_%sm",L));
TH1D *h_const_0p1 = (TH1D*)fhistsig->Get(Form("hsea_M_100MeV_L_%sm",L));
TH1D *h_const_0p2 = (TH1D*)fhistsig->Get(Form("hsea_M_200MeV_L_%sm",L));
TH1D *h_const_0p5 = (TH1D*)fhistsig->Get(Form("hsea_M_500MeV_L_%sm",L));
TH1D *h_const_1 = (TH1D*)fhistsig->Get(Form("hsea_M_1GeV_L_%sm",L));
TH1D *h_const_10 = (TH1D*)fhistsig->Get(Form("hsea_M_10GeV_L_%sm",L));
TH1D *h_const_100 = (TH1D*)fhistsig->Get(Form("hsea_M_100GeV_L_%sm",L));

TH1D *hbkg = (TH1D*)fhistbkg->Get("hsea");

double xmin=-1, xmax=1, xbins=100;
TString a("Events/"); char b[20];  sprintf(b, "(%.2f",(xmax-xmin)/xbins); TString c(")");
TString ytitle = a + b + c;
TString xtitle="cos#it{#theta}";

h_const_0p005->SetLineColor(2);
h_const_0p05->SetLineColor(3);
h_const_0p5->SetLineColor(4);
h_const_0p2->SetLineColor(5);
h_const_0p1->SetLineColor(6);
h_const_1->SetLineColor(7);
h_const_10->SetLineColor(8);
h_const_100->SetLineColor(9);
hbkg->SetLineColor(1);

h_const_0p005->Scale((hbkg->Integral())/(h_const_0p005->Integral()));
h_const_0p05->Scale((hbkg->Integral())/(h_const_0p05->Integral()));
h_const_0p5->Scale((hbkg->Integral())/(h_const_0p5->Integral()));
h_const_0p2->Scale((hbkg->Integral())/(h_const_0p2->Integral()));
h_const_0p1->Scale((hbkg->Integral())/(h_const_0p1->Integral()));
h_const_1->Scale((hbkg->Integral())/(h_const_1->Integral()));
h_const_10->Scale((hbkg->Integral())/(h_const_10->Integral()));
h_const_100->Scale((hbkg->Integral())/(h_const_100->Integral()));

h_const_0p005->SetMaximum(10*(hbkg->GetMaximum()));
h_const_0p005->SetMinimum(0.1);
h_const_0p005->Draw("hist");
h_const_0p005->GetXaxis()->SetTitle(xtitle);
h_const_0p005->GetYaxis()->SetTitle(ytitle);
h_const_0p05->Draw("hist,same");
h_const_0p5->Draw("hist,same");
h_const_0p2->Draw("hist,same");
h_const_0p1->Draw("hist,same");
h_const_1->Draw("hist,same");
h_const_10->Draw("hist,same");
h_const_100->Draw("hist,same");
hbkg->Draw("hist,same");

TLegend *legend = new TLegend(0.38,0.27,0.48,0.63,NULL,"brNDC");
legend->SetHeader(Form("L=%sm",L));
legend->AddEntry(h_const_0p005,"#it{M}_{DM}=0.005 GeV","F");
legend->AddEntry(h_const_0p05,"#it{M}_{DM}=0.05 GeV","F");
legend->AddEntry(h_const_0p1,"#it{M}_{DM}=0.1 GeV","F");
legend->AddEntry(h_const_0p2,"#it{M}_{DM}=0.2 GeV","F");
legend->AddEntry(h_const_0p5,"#it{M}_{DM}=0.5 GeV","F");
legend->AddEntry(h_const_1,"#it{M}_{DM}=1 GeV","F");
legend->AddEntry(h_const_10,"#it{M}_{DM}=10 GeV","F");
legend->AddEntry(h_const_100,"#it{M}_{DM}=100 GeV","F");
legend->AddEntry(hbkg,"Air","F");
setLegend(legend);
legend->Draw();

gPad->RedrawAxis();

can->Update();
can->Print(Form("../figure/costheta_%sm.eps",L));

/*
delete h_const_0p005;
delete h_const_0p05;
delete h_const_0p5;
delete h_const_0p2;
delete h_const_0p1;
delete h_const_1;
delete h_const_10;
delete h_const_100;

delete hbkg;

delete can;
*/

}
