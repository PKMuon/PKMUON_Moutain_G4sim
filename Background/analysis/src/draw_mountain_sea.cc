#include "boot.h"
void draw_mountain_sea(){

TChain *chain = new TChain("T1");
chain->Add("../job_opt2_100m/analysis/root/muCry_*.root");

setStyle();
gStyle->SetTitleYOffset(1.0);     // Y title offset
gStyle->SetTitleXOffset(0.8);     // X title offset

TCanvas *can = new TCanvas("can","can",800,600);setPad();
gPad->SetBottomMargin(0.12);       // pad bottom margin for writing X title
gPad->SetRightMargin(0.02);       // pad right margin  for writing Y title
gPad->SetTopMargin(0.02);         // pad top margin for writing X title
can->SetLogy();

double xbins=100, xmin=0, xmax=1;

TH1D *hmountain       = new TH1D("hmountain","hmountain",xbins,xmin,xmax);
TH1D *hsea       = new TH1D("hsea","hsea",xbins,xmin,xmax);

TString a("Events/"); char b[20];  sprintf(b, "(%.2f",(xmax-xmin)/xbins); TString c(")");
TString ytitle = a + b + c;
TString xtitle="cos#it{#theta}";

TCut cut="flag_Gem3==1 && flag_Gem4==1";

//project
chain->Project("hmountain","costheta_smear_Mountain","1");
chain->Project("hsea","costheta_smear_Sea",cut);

hmountain->SetLineColor(1);
hsea->SetLineColor(2);

cout<<"Events pass Gem1 and Gem2 = "<<chain->GetEntries("1")<<endl;
cout<<"Events pass Gem3 and Gem4 = "<<chain->GetEntries("flag_Gem3==1 && flag_Gem4==1")<<endl;

TFile* fout = new TFile("../root/Hist.root","recreate");
fout->cd();
hmountain->Write();
hsea->Write();
fout->Close();

hsea->Scale((hmountain->Integral())/(hsea->Integral()));

//hmountain->SetMaximum();
hmountain->SetMinimum(0.1);
hmountain->Draw("e");
hmountain->GetXaxis()->SetTitle(xtitle);
hmountain->GetYaxis()->SetTitle(ytitle);
hsea->Draw("hist,same");

TLegend *legend = new TLegend(0.65,0.30,0.85,0.50,NULL,"brNDC");
legend->AddEntry(hmountain,"100m","lep");
legend->AddEntry(hsea,"Sea","F");
setLegend(legend);
legend->Draw();

TPaveText* text = new TPaveText(0.2, 0.9, 0.3, 0.95, "NDC");
text->AddText(Form("Sea"));
//text->Draw();

gPad->RedrawAxis();

can->Update();
can->Print("../figure/costheta_mountain_sea.eps");

}
