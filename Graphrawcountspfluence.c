int Graphfluencecounts1511()


{
	TGraphErrors *gr1 = new TGraphErrors("raw_Ni_counts_vs_pfluence_1511.txt");
	TGraphErrors *gr2 = new TGraphErrors("raw_Ni_counts_vs_pfluence_1511_edited.txt");
	TGraphErrors *gr3 = new TGraphErrors("Ni_vs_Brookhaven.txt");
	TGraphErrors *gr4 = new TGraphErrors("Ni_vs_Brookhaven_edited.txt");
		gr1->GetXaxis()->SetTitle("Ni Counts (Raw)");
		gr1->GetYaxis()->SetTitle("Proton Fluence (p/cm^2)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Proton Fluence vs Ni Counts");
	
		gr2->GetXaxis()->SetTitle("Ni Counts (Raw)");
		gr2->GetYaxis()->SetTitle("Proton Fluence (p/cm^2)");
		gr2->GetYaxis()->SetTitleOffset(1.45);
		gr2->SetTitle("Proton Fluence vs Ni Counts (Edited)");
		
		gr3->GetXaxis()->SetTitle("Ni Counts (Calibrated)");
		gr3->GetYaxis()->SetTitle("Brookhaven Counts");
		gr3->GetYaxis()->SetTitleOffset(1.45);
		gr3->SetTitle("Ni/Brookhaven Counts Comparison");
		
		gr4->GetXaxis()->SetTitle("Ni Counts (Calibrated)");
		gr4->GetYaxis()->SetTitle("Brookhaven Counts");
		gr4->GetYaxis()->SetTitleOffset(1.45);
		gr4->SetTitle("Ni/Brookhaven Counts Comparison (Edited)");		

	TF1* fit1 = new TF1("fit1","pol1",90,8000);
	TF1* fit2 = new TF1("fit2","pol1",90,2000);
	TF1* fit3 = new TF1("fit3","pol1",2,110);
	TF1* fit4 = new TF1("fit4","pol1",2,30);

	TCanvas *c = new TCanvas("c","c",600,700);
		c->cd(2,2);
		cd->(0);
			gr1->Draw("AP");
			gr1->Fit(fit1,"RN");
			fit1->Draw("same");
		cd->(1);
			gr2->Draw("AP");
			gr2->Fit(fit2,"RN");
			fit2->Draw("same");
		cd->(2);
			gr3->Draw("AP");
			gr3->Fit(fit3,"RN");
			fit3->Draw("same");
		cd->(3);
			gr4->Draw("AP");
			gr4->Fit(fit4,"RN");
			fit4->Draw("same");
				
	return 0;
}
