#include "/home/pku/yuxd/bond/useful/boot.h"
void draw_costheta(){

TFile* fhistbkg = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/src/costheta_0_0p2/Hist.root");
TFile* fhistsig = new TFile("Hist.root");

setStyle();
TCanvas *can = new TCanvas("can","can",800,600);setPad();
gStyle->SetTitleYOffset(1.0);     // Y title offset
gStyle->SetTitleXOffset(0.8);     // X title offset
gPad->SetBottomMargin(0.12);       // pad bottom margin for writing X title
gPad->SetRightMargin(0.02);       // pad right margin  for writing Y title
gPad->SetTopMargin(0.02);         // pad top margin for writing X title
can->SetLogy();

TH1D *hsig_M_500MeV_L_100km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_100km");
TH1D *hsig_M_500MeV_L_1000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_1000km");
TH1D *hsig_M_500MeV_L_10000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10000km");
TH1D *hsig_M_500MeV_L_100000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_100000km");
TH1D *hsig_M_500MeV_L_1000000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_1000000km");
TH1D *hsig_M_500MeV_L_10000000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10000000km");

TH1D *hbkg = (TH1D*)fhistbkg->Get("hsea");

double xmin=0, xmax=0.2, xbins=100;
TString a("Events/"); char b[20];  sprintf(b, "(%.3f",(xmax-xmin)/xbins); TString c(")");
TString ytitle = a + b + c;
TString xtitle="cos#it{#theta}";

hsig_M_500MeV_L_100km->SetLineColor(2);
hsig_M_500MeV_L_1000km->SetLineColor(3);
hsig_M_500MeV_L_10000km->SetLineColor(4);
hsig_M_500MeV_L_100000km->SetLineColor(5);
hsig_M_500MeV_L_1000000km->SetLineColor(6);
hsig_M_500MeV_L_10000000km->SetLineColor(7);
hbkg->SetLineColor(1);

hbkg->Scale(50./15.);
hsig_M_500MeV_L_100km->Scale(50.);
hsig_M_500MeV_L_1000km->Scale(50.);
hsig_M_500MeV_L_10000km->Scale(50.);
hsig_M_500MeV_L_100000km->Scale(50.);
hsig_M_500MeV_L_1000000km->Scale(50.);
hsig_M_500MeV_L_10000000km->Scale(50.);

hsig_M_500MeV_L_100km->SetMaximum(10*(hbkg->GetMaximum()));
hsig_M_500MeV_L_100km->SetMinimum(0.1);
hsig_M_500MeV_L_100km->Draw("hist");
hsig_M_500MeV_L_100km->GetXaxis()->SetTitle(xtitle);
hsig_M_500MeV_L_100km->GetYaxis()->SetTitle(ytitle);
hsig_M_500MeV_L_1000km->Draw("hist,same");
hsig_M_500MeV_L_10000km->Draw("hist,same");
hsig_M_500MeV_L_100000km->Draw("hist,same");
hsig_M_500MeV_L_1000000km->Draw("hist,same");
hsig_M_500MeV_L_10000000km->Draw("hist,same");
hbkg->Draw("hist,same");

TLegend *legend = new TLegend(0.38,0.27,0.48,0.63,NULL,"brNDC");
legend->SetHeader(Form("M=500MeV"));
legend->AddEntry(hsig_M_500MeV_L_100km,"L=100km","F");
legend->AddEntry(hsig_M_500MeV_L_1000km,"L=1000km","F");
legend->AddEntry(hsig_M_500MeV_L_10000km,"L=10000km","F");
legend->AddEntry(hsig_M_500MeV_L_100000km,"L=100000km","F");
legend->AddEntry(hsig_M_500MeV_L_1000000km,"L=1000000km","F");
legend->AddEntry(hsig_M_500MeV_L_10000000km,"L=10000000km","F");
legend->AddEntry(hbkg,"Air","F");
setLegend(legend);
legend->Draw();

gPad->RedrawAxis();

can->Update();
can->Draw();
//can->Print(Form("../figure/costheta_%sm.eps",L));

}
