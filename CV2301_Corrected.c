void CV2301_Corrected()
{
	TGraphErrors *gr1 = new TGraphErrors("Diode24_CV_2301_5kHz_corrected.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode24_CV_2301_10kHz_corrected.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode24_CV_2301_30kHz_corrected.txt");
	TGraphErrors *gr4 = new TGraphErrors("Diode24_CV_2301_60kHz_corrected.txt");
	TGraphErrors *gr5 = new TGraphErrors("Diode24_CV_2301_100kHz_corrected.txt");
		
		gr1->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
		gr1->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 24 C-V 23/01, Corrected for Background");
		
		gr1->SetMarkerStyle(20);
        gr2->SetMarkerStyle(21);
        gr3->SetMarkerStyle(22);
        gr4->SetMarkerStyle(23);
        gr5->SetMarkerStyle(33);
        
        gr1->SetMarkerSize(1);
        gr2->SetMarkerSize(1);
        gr3->SetMarkerSize(1);
        gr4->SetMarkerSize(1);
        gr5->SetMarkerSize(1);

    TMultiGraph *mg = new TMultiGraph();
        mg->Add(gr1);
        mg->Add(gr2);
        mg->Add(gr3);
        mg->Add(gr4);
        mg->Add(gr5);
        
        mg->SetTitle("Diode 24 C-V 23/01, Corrected for Background");
        mg->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
        mg->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");         
	

	TCanvas *cv = new TCanvas("cv","cv",600,700);
        
        mg->Draw("ALP");
		
        /*gr1->Draw("ALP");
		gr2->Draw("same");
		gr3->Draw("same");
		gr4->Draw("same");
		gr5->Draw("same");*/		
		
	TLegend *legend = new TLegend(0.6,0.5,0.88,0.7);
	legend->SetHeader("Legend");
		legend->AddEntry(gr1,"5kHz","lp");
		legend->AddEntry(gr2,"10kHz","lp");
		legend->AddEntry(gr3,"30kHz","lp");
		legend->AddEntry(gr4,"60kHz","lp");
		legend->AddEntry(gr5,"100kHz","lp");
		legend->Draw();


}
