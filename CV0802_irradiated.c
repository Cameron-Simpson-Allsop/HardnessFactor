void CV0802_irradiated()
{
	TGraphErrors *gr1 = new TGraphErrors("Diode3_CV_0802_5kHz.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode3_CV_0802_10kHz.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode3_CV_0802_30kHz.txt");
	TGraphErrors *gr4 = new TGraphErrors("Diode3_CV_0802_60kHz.txt");
	TGraphErrors *gr5 = new TGraphErrors("Diode3_CV_0802_100kHz.txt");
		
	gr1->SetMarkerStyle(31);
        gr2->SetMarkerStyle(2);
        gr3->SetMarkerStyle(3);
        gr4->SetMarkerStyle(4);
        gr5->SetMarkerStyle(5);
        
        gr1->SetMarkerSize(1.5);
        gr2->SetMarkerSize(1.5);
        gr3->SetMarkerSize(1.5);
        gr4->SetMarkerSize(1.5);
        gr5->SetMarkerSize(1.5);

    TMultiGraph *mg = new TMultiGraph();
        mg->Add(gr1);
        mg->Add(gr2);
        mg->Add(gr3);
        mg->Add(gr4);
        mg->Add(gr5);
        
        mg->SetTitle("Diode 3 Irradiated C-V 08/02");
        mg->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
        mg->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");  

	TCanvas *cv = new TCanvas("cv","cv",600,700);
		mg->Draw("ALP");

	TLegend *legend = new TLegend(0.6,0.5,0.88,0.7);
	legend->SetHeader("Legend");
		legend->AddEntry(gr1,"5kHz Irradiated","lp");
		legend->AddEntry(gr2,"10kHz Irradiated","lp");
		legend->AddEntry(gr3,"30kHz Irradiated","lp");
		legend->AddEntry(gr4,"60kHz Irradiated","lp");
		legend->AddEntry(gr5,"100kHz Irradiated","lp");
      	legend->Draw();


}
