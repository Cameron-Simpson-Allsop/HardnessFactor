int Graphfluencecounts2011()


{
	TGraphErrors *gr1 = new TGraphErrors("calibratedfluence_vs_nicounts_2011.txt");
	
		gr1->GetXaxis()->SetTitle("Ni Counts (Raw)");
		gr1->GetYaxis()->SetTitle("Calibrated Proton Fluence (p/cm^2)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Calibrated Proton Fluence vs Ni Counts");
		gr1->SetLineColor(kBlue);	

		
	TF1* fit1 = new TF1("fit1","pol1",300,8000);

	fit1->SetParameter(1,1E9);
	
	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		gr1->Draw("AP");
		gr1->Fit(fit1,"RN");
		fit1->Draw("same");
				
	return 0;
}
