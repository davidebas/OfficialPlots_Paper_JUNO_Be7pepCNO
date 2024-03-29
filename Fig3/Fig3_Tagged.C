#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"

double aa = -4.80508e-09;
double bb = 0.000663382;
double cc = 0.0195086;

double funzione3(double x) {
	return (cc+bb*x+aa*x*x);
}

double funzione4(double *x, double *par) {
	return (-bb+TMath::Sqrt(bb*bb-4*(cc-x[0])*aa) ) / (2*aa);
}

void Fig3_Tagged() {	

	int maximumplot = 3e7;
	double minimumplot = 1;

	TFile f1("Inputs/OutputRoot_Test_BX_6Y.root","read");
	TH1D* h1 = (TH1D*)f1.Get("PseudoDataset_Tag")->Clone();
	
	TFile f2("Inputs/OutputRoot_Test_Ideal_6Y.root","read");
	TH1D* h2 = (TH1D*)f2.Get("PseudoDataset_Tag")->Clone();

	TFile f3("Inputs/OutputRoot_Test_Baseline_6Y.root","read");
	TH1D* h3 = (TH1D*)f3.Get("PseudoDataset_Tag")->Clone();

	TFile f4("Inputs/OutputRoot_Test_Worst_6Y.root","read");
	TH1D* h4 = (TH1D*)f4.Get("PseudoDataset_Tag")->Clone();

	TH1D* h_Be7 = (TH1D*)f1.Get("PDFs/Be7;2")->Clone();
	TH1D* h_pep = (TH1D*)f1.Get("PDFs/pep;2")->Clone();
	TH1D* h_CNO = (TH1D*)f1.Get("PDFs/CNO;2")->Clone();

	TFile f_CNO("Inputs/Paper_PDFs_NuSol_J21v1r0-Pre0_r15_Thr300_1Y_Smoothed_2022-March.root","read");
	TH1D* h_N13 = (TH1D*)f_CNO.Get("h_NQE_N13")->Clone();
	TH1D* h_O15 = (TH1D*)f_CNO.Get("h_NQE_O15")->Clone();

	TCanvas *c1 = new TCanvas("c1", "Spectra_FourScenarios",700,500);
	c1->cd();
	//gStyle->SetOptTitle(0);
	c1->Range(-4.369567,-4.362157,968.6522,2.124133);
	c1->SetFillColor(0);
	c1->SetBorderMode(0);
	c1->SetBorderSize(2);
	c1->SetLogy();
	c1->SetRightMargin(0.08);
	c1->SetLeftMargin(0.12);
	c1->SetTopMargin(0.10);
	c1->SetBottomMargin(0.12);
	c1->SetFrameBorderMode(0);

	TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.52,0.90,0.80);
	pad1->SetFillColor(11);
	pad1->Draw();
		
	/**** DATA ****/
	h1->GetXaxis()->CenterTitle(kTRUE);
	h1->GetYaxis()->CenterTitle(kTRUE);
	gStyle->SetTitleFontSize(0.055);
	h1->SetTitle("");

	h1->GetYaxis()->SetTitleSize(0.055);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->GetXaxis()->SetLabelFont(42);							
	h1->GetYaxis()->SetTitle("Events / p.e.");
	h1->GetYaxis()->SetLabelSize(0.055);
	h1->GetXaxis()->SetLabelSize(0.055);

	h1->GetXaxis()->SetTitleSize(0.055);
	h1->GetXaxis()->SetTitleOffset(1.0);
	
	h1->GetXaxis()->SetLabelSize(0);
	h1->GetXaxis()->SetTickSize(0);
		
	h1->GetXaxis()->SetTitle("Energy [keV]");
	h1->GetXaxis()->SetRangeUser(650,2400);
	h1->GetYaxis()->SetRangeUser(minimumplot,maximumplot);
	h1->SetLineColor(kBlack);
	h1->SetLineWidth(2);
	
	
	h1->SetLineColor(kSpring-5);

	h1->DrawCopy();
	h2->SetLineColor(kAzure+8);
	h3->SetLineColor(kBlue+1);
	h4->SetLineColor(kViolet-7);

	h1->SetLineWidth(2);
	h2->SetLineWidth(2);
	h3->SetLineWidth(2);
	h4->SetLineWidth(2);

	h2->DrawCopy("same");
	h3->DrawCopy("same");
	h4->DrawCopy("same");

	/**** SOLAR NEUTRINOS ****/
	h_Be7->SetLineColor(kRed); h_Be7->SetLineWidth(4); 
	h_Be7->DrawCopy("same");

	h_pep->SetLineColor(kOrange+1); h_pep->SetLineWidth(4); 
	h_pep->DrawCopy("same");

	h_N13->Scale(30931./h_N13->Integral());
	h_O15->Scale(23420./h_O15->Integral());

	h_N13->SetLineColor(906); h_N13->SetLineWidth(4);
	h_N13->DrawCopy("same");

	h_O15->SetLineColor(kOrange-1); h_O15->SetLineWidth(4);
	h_O15->DrawCopy("same");

	gStyle->SetOptStat(0);
	c1->Update();
	
	// LEGEND
	TLegend *leg1 = new TLegend(0.3,0.68,0.75,0.89,NULL,"brNDC");
	leg1->SetTextAlign(13);
	leg1->SetTextSize(0.055);
	leg1->SetBorderSize(0);
	leg1->SetFillStyle(0);
	leg1->SetTextFont(42);
	leg1->AddEntry(h4,"IBD radiopurity","l");
	leg1->AddEntry(h3,"Baseline radiopurity","l");
	leg1->AddEntry(h2,"Ideal radiopurity","l");	
	leg1->AddEntry(h1,"BX-like radiopurity","l");	
	leg1->Draw();
	c1->Update();
	
	TLegend *leg2 = new TLegend(0.72,0.68,0.9,0.89,NULL,"brNDC");
	leg2->SetTextAlign(13);
	leg2->SetTextSize(0.055);
	leg2->SetBorderSize(0);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(42);	
	leg2->AddEntry(h_Be7,"^{7}Be #nu","l");
	leg2->AddEntry(h_pep,"pep #nu","l");
	leg2->AddEntry(h_N13,"^{13}N-#nu","l");	
	leg2->AddEntry(h_O15,"^{15}O-#nu","l");

	leg2->Draw();
	
	// upper x axis
	TGaxis *A3 = new TGaxis(650,maximumplot,2400,maximumplot,650, 2400,10,"-");
	A3->SetTitle("p.e.");
	A3->SetTitleSize(0.05);
	A3->SetTitleOffset(0.9);
	A3->SetLabelSize(0.05);
	A3->SetTextFont(42);
	A3->SetLabelFont(42);
	A3->CenterTitle(kTRUE);
	A3->Draw("SAME");
	c1->Update();	

	// lower x axis
	TF1 *LowerAxis3=new TF1("LowerAxis3",funzione4,funzione3(650),funzione3(2400),0);
	TGaxis *A5 = new TGaxis(650,minimumplot,2400,minimumplot,"LowerAxis3",520);
	A5->SetTitle("");
	A5->SetLabelSize(0.05);
	A5->SetTitleSize(0.05);
	A5->SetTitleOffset(0.);
	A5->SetLabelFont(42);
	A5->SetTextFont(42);
	A5->Draw();
	c1->Update();

	c1->Update();

  c1->Print("Fig3_Tagged.pdf","pdf");
}

#ifndef __CINT__
int main() {
  Fig3_Tagged();
}
#endif
