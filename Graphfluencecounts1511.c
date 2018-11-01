int Graphfluencecounts1511()


{
	TGraphErrors *gr1 = new TGraphErrors("RawCounts_vs_AssumedFluence_1511.txt");
	TGraphErrors *gr2 = new TGraphErrors("CalibratedCounts_vs_Fluence_1511.txt");
	TGraphErrors *gr3 = new TGraphErrors("Ni_vs_Brookhaven.txt");
	TGraphErrors *gr5 = new TGraphErrors("calcfluence_vs_assumedfluence_1511.txt");
	TGraphErrors *gr6 = new TGraphErrors("BrookhavenCounts_vs_Fluence_1511.txt");

		gr1->GetXaxis()->SetTitle("Ni Counts (Raw)");
		gr1->GetYaxis()->SetTitle("Assumed Proton Fluence (p/cm^2)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Assumed Proton Fluence vs Ni Counts");
		gr1->SetLineColor(kBlue);	

		gr2->GetXaxis()->SetTitle("Ni Counts (Calibrated)");
		gr2->GetYaxis()->SetTitle("Calculated Proton Fluence (p/cm^2)");
		gr2->GetYaxis()->SetTitleOffset(1.45);
		gr2->SetTitle("Calculated Proton Fluence vs Ni Counts");
		gr2->SetLineColor(kBlue);		

		gr3->GetXaxis()->SetTitle("Ni Counts (Calibrated)");
		gr3->GetYaxis()->SetTitle("Brookhaven Counts");
		gr3->GetYaxis()->SetTitleOffset(1.45);
		gr3->SetTitle("Ni/Brookhaven Counts Comparison");
		gr3->SetLineColor(kBlue);

		gr5->GetXaxis()->SetTitle("Calculated Fluence (p/cm^2)");
		gr5->GetYaxis()->SetTitle("Assumed Fluence (p/cm^2)");
		gr5->GetYaxis()->SetTitleOffset(1.45);
		gr5->SetTitle("Calculated Proton Fluence vs Assumed Proton Fluence");
		gr5->SetLineColor(kBlue);

		gr6->GetXaxis()->SetTitle("Brookhaven Counts");
		gr6->GetYaxis()->SetTitle("Calculated Proton Fluence (p/cm^2)");
		gr6->GetYaxis()->SetTitleOffset(1.45);
		gr6->SetTitle("Calculated Proton Fluence vs Brookhaven Counts");
		gr6->SetLineColor(kBlue);

	TF1* fit1 = new TF1("fit1","pol1",300,8000);
	TF1* fit2 = new TF1("fit2","pol1",3,100);
	TF1* fit3 = new TF1("fit3","pol1",2,110);
	TF1* fit5 = new TF1("fit5","pol1",0,6E14);
	TF1* fit6 = new TF1("fit6","pol1",10,410);	

	fit1->SetParameter(1,1E9);
	fit2->SetParameter(1,5E11);
	fit5->SetParameter(1,1E-2);
	fit6->SetParameter(1,1E12);		

	TCanvas *c = new TCanvas("c","c",600,700);
		c->Divide(2,3);
		c->cd(1);
			gr1->Draw("AP");
			gr1->Fit(fit1,"RN");
			fit1->Draw("same");
		c->cd(2);
			gr2->Draw("AP");
			gr2->Fit(fit2,"RN");
			fit2->Draw("same");
		c->cd(3);
			gr3->Draw("AP");
			gr3->Fit(fit3,"RN");
			fit3->Draw("same");		
		c->cd(4);
			gr5->Draw("AP");
			gr5->Fit(fit5,"RN");
			fit5->Draw("same");
		c->cd(5);
			gr6->Draw("AP");
			gr6->Fit(fit6,"RN");
			fit6->Draw("same");

	TCanvas *c1 = new TCanvas("c1","c1",600,700);
			gr6->Draw("AP");
			gr6->Fit(fit6,"RN");
			fit6->Draw("same");
				
	return 0;
}
