#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"

#include "iostream"

void IVCurves1601()
{
	
TGraphErrors *g1 = new TGraphErrors("Diode_24_BandGap_1601_10_8C.txt");
TGraphErrors *g2 = new TGraphErrors("Diode_24_BandGap_1601_15_1C.txt");
TGraphErrors *g3 = new TGraphErrors("Diode_24_BandGap_1601_20_0C.txt");
TGraphErrors *g4 = new TGraphErrors("Diode_24_BandGap_1601_25_2C.txt");
TGraphErrors *g5 = new TGraphErrors("Diode_24_BandGap_1601_30_3C.txt");
TGraphErrors *g6 = new TGraphErrors("Diode_24_BandGap_1601_35_0C.txt");
TGraphErrors *g7 = new TGraphErrors("Diode_24_BandGap_1601_40_0C.txt");
TGraphErrors *g8 = new TGraphErrors("Diode_24_BandGap_1601_45_3C.txt");
TGraphErrors *g9 = new TGraphErrors("Diode_24_BandGap_1601_50_1C.txt");
TGraphErrors *g10 = new TGraphErrors("Diode_24_BandGap_1601_55_1C.txt");
TGraphErrors *g11 = new TGraphErrors("Diode_24_BandGap_1601_60_1C.txt");
TGraphErrors *g12 = new TGraphErrors("Diode_24_BandGap_1601_21_4C.txt");

	g1->GetXaxis()->SetTitle("Voltage (-V)");
	g1->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g1->SetTitle("Diode 24: 10.8C");

	g2->GetXaxis()->SetTitle("Voltage (-V)");
	g2->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g2->SetTitle("Diode 24: 15.1C");

	g3->GetXaxis()->SetTitle("Voltage (-V)");
	g3->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g3->SetTitle("Diode 24: 20.0C");

	g4->GetXaxis()->SetTitle("Voltage (-V)");
	g4->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g4->SetTitle("Diode 24: 25.2C");

	g5->GetXaxis()->SetTitle("Voltage (-V)");
	g5->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g5->SetTitle("Diode 24: 30.3C");
	
	g6->GetXaxis()->SetTitle("Voltage (-V)");
	g6->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g6->SetTitle("Diode 24: 35.0C");

	g7->GetXaxis()->SetTitle("Voltage (-V)");
	g7->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g7->SetTitle("Diode 24: 40.0C");

	g8->GetXaxis()->SetTitle("Voltage (-V)");
	g8->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g8->SetTitle("Diode 24: 45.3C");

	g9->GetXaxis()->SetTitle("Voltage (-V)");
	g9->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g9->SetTitle("Diode 24: 50.1C");
	
	g10->GetXaxis()->SetTitle("Voltage (-V)");
	g10->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g10->SetTitle("Diode 24: 55.1C");

	g11->GetXaxis()->SetTitle("Voltage (-V)");
	g11->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g11->SetTitle("Diode 24: 60.1C");

	g12->GetXaxis()->SetTitle("Voltage (-V)");
	g12->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g12->SetTitle("Diode 24: 21.4C");

	g1->SetLineColor(1);
	g2->SetLineColor(2);
	g3->SetLineColor(3);
	g4->SetLineColor(4);
	g5->SetLineColor(5);
	g6->SetLineColor(6);
	g7->SetLineColor(7);
	g8->SetLineColor(8);
	g9->SetLineColor(9);
	g10->SetLineColor(13);
	g11->SetLineColor(11);
	g12->SetLineColor(12);	

TGaxis::SetMaxDigits(3);
TCanvas *c = new TCanvas("c","c",600,700);
c->Divide(3,4);

c->cd(1);
	g1->Draw("ALP");

c->cd(2);
	g2->Draw("ALP");

c->cd(3);
	g3->Draw("ALP");

c->cd(4);
	g4->Draw("ALP");

c->cd(5);
	g5->Draw("ALP");

c->cd(6);
	g6->Draw("ALP");

c->cd(7);
	g7->Draw("ALP");

c->cd(8);
	g8->Draw("ALP");

c->cd(9);
	g9->Draw("ALP");

c->cd(10);
	g10->Draw("ALP");

c->cd(11);
	g11->Draw("ALP");

c->cd(12);
	g12->Draw("ALP");

TCanvas *c1 = new TCanvas("c1","c1",600,700);
	g11->Draw("ALP");
	g1->Draw("same");
	g2->Draw("same");
	g3->Draw("same");
	g4->Draw("same");
	g5->Draw("same");
	g6->Draw("same");
	g7->Draw("same");
	g8->Draw("same");
	g9->Draw("same");
	g10->Draw("same");
	g12->Draw("same");

TLegend *legend = new TLegend(0.4,0.2,0.88,0.4);
	legend->SetHeader("Legend");
		legend->AddEntry(g1,"10.8C","l");
		legend->AddEntry(g2,"15.1C","l");
		legend->AddEntry(g3,"20.0C","l");
		legend->AddEntry(g4,"25.2C","l");
		legend->AddEntry(g5,"30.3C","l");
		legend->AddEntry(g6,"35.0C","l");
		legend->AddEntry(g7,"40.0C","l");
		legend->AddEntry(g8,"45.3C","l");
		legend->AddEntry(g9,"50.1C","l");
		legend->AddEntry(g10,"55.1C","l");
		legend->AddEntry(g11,"60.1C","l");
		legend->AddEntry(g12,"21.4C","l");
		legend->Draw();
	

}
