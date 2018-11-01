int thermom_vs_thermocoup_0512()


{
	TGraphErrors *gr1 = new TGraphErrors("thermometer_vs_thermocouple_0412.txt");
		gr1->GetXaxis()->SetTitle("Thermometer (deg C)");
		gr1->GetYaxis()->SetTitle("Thermocouple (deg C)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Thermocouple Temperature vs Thermometer Temperature");
		gr1->SetLineColor(kBlue);
		
	TF1 *fit = new TF1("fit","pol1",10,81);
	fit->SetParameter(0,0);
	fit->SetParameter(1,1);
		
	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		gr1->Draw("AP");
		gr1->Fit(fit,"RN");
		fit->Draw("same");
		
return 0;
}
