int Graphs1611()


{
	TGraphErrors *gr1 = new TGraphErrors("Diode_20_1_1611.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode_20_2_1611.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode_20_3_1611.txt");
		gr1->GetXaxis()->SetTitle("Voltage(V)");
		gr1->GetYaxis()->SetTitle("Leakage Current (nA)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 20 I-V Sweep 16/11");
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