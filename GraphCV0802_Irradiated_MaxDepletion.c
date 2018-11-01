int GraphCV0802_Irradiated_MaxDepletion()


{
	TGraphErrors *gr1 = new TGraphErrors("Diode3_CV_0802_10kHz.txt");
		gr1->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
		gr1->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 3 Irradiated C-V 08/02");
		gr1->SetLineColor(kBlue);
		

	TF1* fit1 = new TF1("fit1","pol1",1.0,3.8);
	TF1* fit2 = new TF1("fit2","pol1",3.9,4.9);	
	fit1->SetParameter(1,-1);

	TCanvas *c1a = new TCanvas("c1","c1",600,700);
		gr1->Draw("ALP");
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

	/*TF1* fit3 = new TF1("fit3","[1]*x+[0]",4.19,4.7); //Extrapolates fit lines (Cosmetic).
	TF1* fit4 = new TF1("fit4","[1]*x+[0]",4.3,4.61);
	fit3->SetParameter(0,c1);
	fit3->SetParameter(1,m1);
	fit4->SetParameter(0,c2);
	fit4->SetParameter(1,m2);
	
		fit3->Draw("same");
		fit4->Draw("same");*/		
	
	double Intersect = (c2-c1)/(m1-m2); //Intersect of fit lines on x axis.
	double e1 = ec2/(m1-m2);
	double e2 = ec1/(m1-m2);
	double e3 = em1*(c2-c1)/(pow(m1-m2,2));
	double e4 = em2*(c2-c1)/(pow(m1-m2,2));
	double eIntersect = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);

	std::cout << "x Intersect = " << Intersect << " +/- " << eIntersect << std::endl;
	std::cout << "Max Depletion Voltage = " << -exp(Intersect) << " +/- " << exp(Intersect)*eIntersect <<std::endl; //Log scale so take exponents.
	std::cout << "Percentage Error = " << 100*exp(Intersect)*eIntersect/exp(Intersect) << "%" << std::endl;	
	
return 0;
}
