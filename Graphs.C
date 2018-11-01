int Graphs()


{
	TGraphErrors *gr1 = new TGraphErrors("IVDiode2Run1_1910.txt");
	TGraphErrors *gr2 = new TGraphErrors("IVDiode2Run2_2010.txt");
	TGraphErrors *gr3 = new TGraphErrors("IVDiode2Run3_2010.txt");
		gr1->GetXaxis()->SetTitle("Voltage(V)");
		gr1->GetYaxis()->SetTitle("Leakage Current (uA)");
		gr1->GetYaxis()->SetTitleOffset(1.7);
		gr1->SetTitle("Title");
		gr1->SetLineColor(kBlue);
		gr2->SetLineColor(kRed);
		
	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		gr1->Draw("ALP");
		gr2->Draw("same");
		gr3->Draw("same");

	
	auto legend = new TLegend(0.4,0.2,0.88,0.4);
		legend->SetHeader("Legend");
		legend->AddEntry(gr1,"IVDiode2EC30Raw_2310","l");
		legend->AddEntry(gr2,"IVDiode2EC40Raw_2310","l");
		legend->Draw();
return 0;
}
