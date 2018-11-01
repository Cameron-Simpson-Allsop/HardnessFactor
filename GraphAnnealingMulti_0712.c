int GraphAnnealingMulti_0712()
{
	TGraphErrors *g0 = new TGraphErrors("Diode_5_Anneal_0mins_2411.txt");
	TGraphErrors *g1 = new TGraphErrors("Diode_5_Anneal_10mins_2411.txt");
	TGraphErrors *g2 = new TGraphErrors("Diode_5_Anneal_20mins_2411.txt");
	TGraphErrors *g3 = new TGraphErrors("Diode_5_Anneal_30mins_2411.txt");
	TGraphErrors *g4 = new TGraphErrors("Diode_5_Anneal_40mins_2411.txt");
	TGraphErrors *g5 = new TGraphErrors("Diode_5_Anneal_50mins_2411.txt");	
	TGraphErrors *g6 = new TGraphErrors("Diode_5_Anneal_60mins_2411.txt");
	TGraphErrors *g7 = new TGraphErrors("Diode_5_Anneal_70mins_2411.txt");
	TGraphErrors *g8 = new TGraphErrors("Diode_5_Anneal_80mins_2411.txt");
		
		g1->GetXaxis()->SetTitle("Voltage(V)");
		g1->GetYaxis()->SetTitle("Leakage Current (nA)");
		g1->SetTitle("");
	
		g0->SetLineColor(kBlack);
		g1->SetLineColor(kBlack);
		g2->SetLineColor(kBlack);
		g3->SetLineColor(kBlack);
		g4->SetLineColor(kBlack);
		g5->SetLineColor(kBlack);
		g6->SetLineColor(kBlack);
		g7->SetLineColor(kBlack);
		g8->SetLineColor(kBlack);

		g0->SetMarkerStyle(20);
		g1->SetMarkerStyle(21);
		g2->SetMarkerStyle(22);
		g3->SetMarkerStyle(23);
		g4->SetMarkerStyle(29);
		g5->SetMarkerStyle(33);
		g6->SetMarkerStyle(34);
		g7->SetMarkerStyle(3);
		g8->SetMarkerStyle(5);
	
	TCanvas *Anneal = new TCanvas("Anneal","Anneal",600,700);
		//TGaxis::SetMaxDigits(2);
		g1->Draw("ACP");
		g0->Draw("pcsame");
		g2->Draw("pcsame");
		g3->Draw("pcsame");
		g4->Draw("pcsame");
		g5->Draw("pcsame");
		g6->Draw("pcsame");
		g7->Draw("pcsame");
		g8->Draw("pcsame");

	TLegend *legend = new TLegend(0.13,0.63,0.25,0.88);
                legend->AddEntry(g0,"0mins","lp");
                legend->AddEntry(g1,"10mins","lp");
                legend->AddEntry(g2,"20mins","lp");
                legend->AddEntry(g3,"30mins","lp");
		legend->AddEntry(g4,"40mins","lp");
		legend->AddEntry(g5,"50mins","lp");
		legend->AddEntry(g6,"60mins","lp");
		legend->AddEntry(g7,"70mins","lp");
		legend->AddEntry(g8,"80mins","lp");
                legend->Draw();

return 0;
}
