#include "/home/pku/yuxd/bond/useful/boot.h"
void draw_costheta(){

TFile* fhistbkg = new TFile("/home/pku/yuxd/bond/PKMUON_Moutain_G4sim/Background/analysis/root/Hist.root");
TFile* fhistsig = new TFile("Hist.root");

setStyle();
TCanvas *can = new TCanvas("can","can",800,600);setPad();
gStyle->SetTitleYOffset(1.0);     // Y title offset
gStyle->SetTitleXOffset(0.8);     // X title offset
gPad->SetBottomMargin(0.12);       // pad bottom margin for writing X title
gPad->SetRightMargin(0.02);       // pad right margin  for writing Y title
gPad->SetTopMargin(0.02);         // pad top margin for writing X title
can->SetLogy();

TH1D *hsig_M_500MeV_L_10km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10km");
TH1D *hsig_M_500MeV_L_100km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_100km");
TH1D *hsig_M_500MeV_L_1000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_1000km");
TH1D *hsig_M_500MeV_L_10000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10000km");
TH1D *hsig_M_500MeV_L_100000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_100000km");
TH1D *hsig_M_500MeV_L_1000000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_1000000km");
TH1D *hsig_M_500MeV_L_10000000km = (TH1D*)fhistsig->Get("hsea_M_500MeV_L_10000000km");

TH1D *hbkg = (TH1D*)fhistbkg->Get("hsea");

double xmin=0, xmax=1, xbins=100;
TString a("Events/"); char b[20];  sprintf(b, "(%.2f",(xmax-xmin)/xbins); TString c(")");
TString ytitle = a + b + c;
TString xtitle="cos#it{#theta}";

hsig_M_500MeV_L_10km->SetLineColor(2);
hsig_M_500MeV_L_100km->SetLineColor(3);
hsig_M_500MeV_L_1000km->SetLineColor(4);
hsig_M_500MeV_L_10000km->SetLineColor(5);
hsig_M_500MeV_L_100000km->SetLineColor(6);
hsig_M_500MeV_L_1000000km->SetLineColor(7);
hsig_M_500MeV_L_10000000km->SetLineColor(8);
hbkg->SetLineColor(1);

hbkg->Scale(50./15.);
hsig_M_500MeV_L_10km->Scale(50.);
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
hsig_M_500MeV_L_10km->Draw("hist,same");
hsig_M_500MeV_L_1000km->Draw("hist,same");
hsig_M_500MeV_L_10000km->Draw("hist,same");
hsig_M_500MeV_L_100000km->Draw("hist,same");
hsig_M_500MeV_L_1000000km->Draw("hist,same");
hsig_M_500MeV_L_10000000km->Draw("hist,same");
hbkg->Draw("hist,same");

TLegend *legend = new TLegend(0.38,0.27,0.48,0.63,NULL,"brNDC");
legend->SetHeader(Form("#it{M}_{DM}=500 MeV"));
legend->AddEntry(hsig_M_500MeV_L_10km,"#it{L}=10 km","F");
legend->AddEntry(hsig_M_500MeV_L_100km,"#it{L}=100 km","F");
legend->AddEntry(hsig_M_500MeV_L_1000km,"#it{L}=1000 km","F");
legend->AddEntry(hsig_M_500MeV_L_10000km,"#it{L}=10000 km","F");
legend->AddEntry(hsig_M_500MeV_L_100000km,"#it{L}=100000 km","F");
legend->AddEntry(hsig_M_500MeV_L_1000000km,"#it{L}=1000000 km","F");
legend->AddEntry(hsig_M_500MeV_L_10000000km,"#it{L}=10000000 km","F");
legend->AddEntry(hbkg,"Air","F");
setLegend(legend);
legend->Draw();

gPad->RedrawAxis();

can->Update();
//can->Draw();
can->Print("costheta_M_500MeV.eps");

}
