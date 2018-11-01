int Graphs0911()


{
	TGraphErrors *gr1 = new TGraphErrors("Diode_16_1_0911.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode_16_2_0911.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode_16_3_0911.txt");
		gr1->GetXaxis()->SetTitle("Voltage(V)");
		gr1->GetYaxis()->SetTitle("Leakage Current (nA)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 16 I-V Sweep 09/11");
		gr1->SetLineColor(kBlue);
		gr2->SetLineColor(kRed);
		gr3->SetLineColor(kGreen);
		
	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		gr1->Draw("ALP");
		gr2->Draw("same");
		gr3->Draw("same");

	
	auto legend = new TLegend(0.4,0.2,0.88,0.4);
		legend->SetHeader("Legend");
		legend->AddEntry(gr1,"Run 1","l");
		legend->AddEntry(gr2,"Run 2","l");
		legend->AddEntry(gr3,"Run 3","l");
		legend->Draw();
return 0;
}
