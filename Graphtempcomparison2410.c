int Graphtempcomparison2410(){

	TCanvas *canvas = new TCanvas("canvas","canvas",600,700);
	TGraphErrors *g1 = new TGraphErrors("IVDiode2EC25Raw_2410.txt");
	TGraphErrors *g2 = new TGraphErrors("IVDiode2EC30Raw_2410.txt");
	TGraphErrors *g3 = new TGraphErrors("IVDiode2EC35Raw_2410.txt");
	TGraphErrors *g4 = new TGraphErrors("IVDiode2EC40Raw_2410.txt");
		g3->GetXaxis()->SetTitle("Voltage (-V)");
		g3->GetYaxis()->SetTitle("Leakage Current (-uA)");
		g3->GetYaxis()->SetTitleOffset(1.1);
		g3->SetTitle("Photodiode 2: Temperature Comparison 24/10 ");
		
		g1->SetLineColor(kBlue);
		g2->SetLineColor(kRed);
		g3->SetLineColor(kGreen);
		g4->SetLineColor(kMagenta);
		
		
		TGaxis::SetMaxDigits(3);
		gStyle->SetOptStat(0);
			
		g3->Draw("ALP");
		g1->Draw("same");
		g2->Draw("same");
		g4->Draw("same");

	
	TLegend *legend = new TLegend(0.4,0.3,0.8,0.5);
                legend->SetHeader("Legend");
		legend->AddEntry(g1,"25C","l");
		legend->AddEntry(g2,"30C","l");
		legend->AddEntry(g3,"35C","l");
                legend->AddEntry(g4,"40C","l");
                legend->Draw();
	
return 0;
}
