int GraphNiBrookhaven1411()


{
	TGraphErrors *gr1 = new TGraphErrors("Ni_vs_Brookhaven_edited.txt");
		gr1->GetXaxis()->SetTitle("Ni Counts (Calibrated)");
		gr1->GetYaxis()->SetTitle("Brookhaven Counts");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Ni/Brookhaven Counts Comparison");
		gr1->SetLineColor(kBlue);
		

	TF1* fit1 = new TF1("fit1","pol1",2,110);
	TCanvas *c2 = new TCanvas("c2","c2",600,700);
		gr1->Draw("AP");
		gr1->Fit(fit1,"RN");
		fit1->Draw("same");
				
return 0;
}
