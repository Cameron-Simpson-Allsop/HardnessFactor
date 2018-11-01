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
		
		g8->GetXaxis()->SetTitle("Voltage(V)");
		g8->GetYaxis()->SetTitle("Leakage Current (nA)");
		g8->GetYaxis()->SetTitleOffset(1.3);
		g8->SetTitle("Diode 5 I-V Sweeps for Varying Annealing Times");
	
		g0->SetLineColour(9);
		g1->SetLineColour(1);
		g2->SetLineColour(2);
		g3->SetLineColour(3);
		g4->SetLineColour(4);
		g5->SetLineColour(5);
		g6->SetLineColour(6);
		g7->SetLineColour(7);
		g8->SetLineColour(8);
	
	TCanvas *Anneal = new TCanvas("Anneal","Anneal",600,700);
		g8->Draw("ALP");
		g0->Draw("same");		
		g1->Draw("same");
		g2->Draw("same");
		g3->Draw("same");
		g4->Draw("same");
		g5->Draw("same");
		g6->Draw("same");
		g7->Draw("same");
		g8->Draw("same");

return 0;
}
