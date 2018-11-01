int GraphsCV2011()


{
	TGraphErrors *gr1 = new TGraphErrors("CV_Diode_2_5kHz_2011.txt");
	TGraphErrors *gr2 = new TGraphErrors("CV_Diode_2_10kHz_2011.txt");
	TGraphErrors *gr3 = new TGraphErrors("CV_Diode_2_30kHz_2011.txt");
	TGraphErrors *gr4 = new TGraphErrors("CV_Diode_2_100kHz_2011.txt");
		gr1->GetXaxis()->SetTitle("ln(V) (ln(-v))");
		gr1->GetYaxis()->SetTitle("ln(C) (ln(pF))");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 2 C-V 20/11");
		gr1->SetLineColor(kBlue);
		gr2->SetLineColor(kRed);
		gr3->SetLineColor(kGreen);
		gr4->SetLineColor(kMagenta);
	
	TF1 *fit1 = new TF1("fit1","pol1",2.3,4.5);
	TF1 *fit2 = new TF1("fit2","pol1",2.3,4.5);
	TF1 *fit3 = new TF1("fit3","pol1",2.3,4.5);
	TF1 *fit4 = new TF1("fit4","pol1",2.3,4.5);
		
	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		gr1->Draw("ALP");
		gr1->Fit(fit1,"RN");
		//fit1->Draw("same");
		
		gr2->Draw("same");
		gr2->Fit(fit2,"RN");
		//fit2->Draw("same");

		gr3->Draw("same");
		gr3->Fit(fit3,"RN");
		//fit3->Draw("same");

		gr4->Draw("same");
		gr4->Fit(fit4,"RN");
		//fit4->Draw("same");

	
	auto legend = new TLegend(0.6,0.7,0.88,0.9);
		legend->SetHeader("Legend");
		legend->AddEntry(gr1,"5kHz","l");
		legend->AddEntry(gr2,"10kHz","l");
		legend->AddEntry(gr3,"30kHz","l");
		legend->AddEntry(gr4,"100kHz","l");
		legend->Draw();
return 0;
}
