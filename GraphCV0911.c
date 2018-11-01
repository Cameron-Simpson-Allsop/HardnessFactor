int GraphCV0911()


{
	TGraphErrors *gr1 = new TGraphErrors("Preliminary_CV_Diode_5_0911_Edited.txt");
		gr1->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
		gr1->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 5 Preliminary C-V 09/11");
		gr1->SetLineColor(kBlue);
		

	TF1* fit1 = new TF1("fit1","pol1",3.6,4.6);
	TF1* fit2 = new TF1("fit2","pol1",4.65,5.4);	

	TCanvas *c1a = new TCanvas("c1","c1",600,700);
		gr1->Draw("ALP");
		//gr2->Draw("same");
		gr1->Fit(fit1,"RN");
		gr1->Fit(fit2,"RN");
		fit1->Draw("same");
		fit2->Draw("same");		

	double c1 = fit1->GetParameter(0);
	double m1 = fit1->GetParameter(1);
	double c2 = fit2->GetParameter(0);
	double m2 = fit2->GetParameter(1);
	
	double ec1 = fit1->GetParError(0);
	double em1 = fit1->GetParError(1);
	double ec2 = fit2->GetParError(0);
	double em2 = fit2->GetParError(1);

	TF1* fit3 = new TF1("fit3","[1]*x+[0]",4.59,4.7);
	TF1* fit4 = new TF1("fit4","[1]*x+[0]",4.39,4.65);
	fit3->SetParameter(0,c1);
	fit3->SetParameter(1,m1);
	fit4->SetParameter(0,c2);
	fit4->SetParameter(1,m2);
	
		fit3->Draw("same");
		fit4->Draw("same");		
	
	double Intercept = (c2-c1)/(m1-m2);
	double e1 = ec2/(m1-m2);
	double e2 = ec1/(m1-m2);
	double e3 = em1*(c2-c1)/(pow(m1-m2,2));
	double e4 = em2*(c2-c1)/(pow(m1-m2,2));
	double eIntercept = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);

	std::cout << "x Intercept = " << Intercept << " +/- " << eIntercept << std::endl;
	std::cout << "Max Depletion Voltage = " << exp(Intercept) << " +/- " << exp(Intercept)*eIntercept <<std::endl;	
	
return 0;
}
