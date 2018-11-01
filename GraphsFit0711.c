int GraphsFit0711()

{
	TCanvas *c1 = new TCanvas("c1","c1",600,700);

	TGraphErrors *gr1 = new TGraphErrors("diode2_0711_33C.txt");
	TGraphErrors *gr2 = new TGraphErrors("diode2_0711_37C.txt");
	TGraphErrors *gr3 = new TGraphErrors("diode2_0711_40C.txt");
	TGraphErrors *gr4 = new TGraphErrors("diode2_0711_43C.txt");
	
		gr1->GetXaxis()->SetTitle("Voltage(V)");
		gr1->GetYaxis()->SetTitle("Leakage Current (nA)");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Photodiode 2: 33C 7/11");		
				
		gr2->GetXaxis()->SetTitle("Voltage(V)");
		gr2->GetYaxis()->SetTitle("Leakage Current (nA)");
		gr2->GetYaxis()->SetTitleOffset(1.45);
		gr2->SetTitle("Photodiode 2: 37C 7/11");
		
		gr3->GetXaxis()->SetTitle("Voltage(V)");
		gr3->GetYaxis()->SetTitle("Leakage Current (nA)");
		gr3->GetYaxis()->SetTitleOffset(1.45);
		gr3->SetTitle("Photodiode 2: 40C 7/11");
		
		gr4->GetXaxis()->SetTitle("Voltage(V)");
		gr4->GetYaxis()->SetTitle("Leakage Current (nA)");
		gr4->GetYaxis()->SetTitleOffset(1.45);
		gr4->SetTitle("Photodiode 2: 43C 7/11");		
	
		TF1* fit1 = new TF1("fit1","pol1", -120,-40);
		TF1* fit2 = new TF1("fit2","pol1", -120,-40);
		TF1* fit3 = new TF1("fit3","pol1", -120,-40);
		TF1* fit4 = new TF1("fit4","pol1", -120,-40);
			
		c1->Divide(2,2);
		c1->cd(1);
		gr1->Draw("AP");
		gr1->Fit(fit1,"R");
		c1->cd(2);
		gr2->Draw("AP");
		gr2->Fit(fit2,"R");
		c1->cd(3);
		gr3->Draw("AP");
		gr3->Fit(fit3,"R");
		c1->cd(4);
		gr4->Draw("AP");
		gr4->Fit(fit4,"R");	
	
		
		std::cout<< "====================================" <<std::endl;
		
		double p0gr1 = fit1->GetParameter(0);
		double p0gr1e = fit1->GetParError(0);
		double p1gr1 = fit1->GetParameter(1);
		double p1gr1e = fit1->GetParError(1);
		
		double p0gr2 = fit2->GetParameter(0);
		double p0gr2e = fit2->GetParError(0);
		double p1gr2 = fit2->GetParameter(1);
		double p1gr2e = fit2->GetParError(1);
		
		double p0gr3 = fit3->GetParameter(0);
		double p0gr3e = fit3->GetParError(0);
		double p1gr3 = fit3->GetParameter(1);
		double p1gr3e = fit3->GetParError(1);
		
		double p0gr4 = fit4->GetParameter(0);
		double p0gr4e = fit4->GetParError(0);
		double p1gr4 = fit4->GetParameter(1);
		double p1gr4e = fit4->GetParError(1);
		
		const int n1 = 11;
		double v = -92.;
		
		double Igr1 = abs(p1gr1*v+p0gr1);
		double Igr2 = abs(p1gr2*v+p0gr2);
		double Igr3 = abs(p1gr3*v+p0gr3);
		double Igr4 = abs(p1gr4*v+p0gr4);
		
		/*double Igr1 = fit1->Eval(-92.);
		double Igr2 = fit2->Eval(-92.);
		double Igr3 = fit3->Eval(-92.);
		double Igr4 = fit4->Eval(-92.);*/
		
		double Igr1e = pow(v*v*p1gr1e*p1gr1e + p0gr1e*p0gr1e + p1gr1*p1gr1*0.05*0.05,0.5);
		double Igr2e = pow(v*v*p1gr2e*p1gr2e + p0gr2e*p0gr2e + p1gr2*p1gr2*0.05*0.05,0.5);
		double Igr3e = pow(v*v*p1gr3e*p1gr3e + p0gr3e*p0gr3e + p1gr3*p1gr3*0.05*0.05,0.5);
		double Igr4e = pow(v*v*p1gr4e*p1gr4e + p0gr4e*p0gr4e + p1gr4*p1gr4*0.05*0.05,0.5);
		
		std::cout << p0gr1 << "+/-" << p0gr1e << "   " << fit1->Eval(v) << "  " << Igr1 << std::endl;
				
		const Int_t n2 = 4;
		Double_t T[n2]  = {306.25,311,313.15,316.2};
		Double_t I[n2]  = {Igr1,Igr2,Igr3,Igr4};
		Double_t eT[n2] = {0.15,0.2,0.15,0.2};
		
		double x1 = 1/T[0];
		double x2 = 1/T[1];
		double x3 = 1/T[2];
		double x4 = 1/T[3];
		double x1e = (1/(T[0]*T[0]))*eT[0];
		double x2e = (1/(T[1]*T[1]))*eT[1];
		double x3e = (1/(T[2]*T[2]))*eT[2];
		double x4e = (1/(T[3]*T[3]))*eT[3];
		
		double y1 = log(I[0]/(T[0]*T[0]));
		double y2 = log(I[1]/(T[1]*T[1]));
		double y3 = log(I[2]/(T[2]*T[2]));
		double y4 = log(I[3]/(T[3]*T[3]));
		double y1e = pow(pow((Igr1e/Igr1),2)+pow((2*0.05)/T[0],2),0.5);
		double y2e = pow(pow((Igr2e/Igr2),2)+pow((2*0.05)/T[1],2),0.5);
		double y3e = pow(pow((Igr3e/Igr3),2)+pow((2*0.05)/T[2],2),0.5);
		double y4e = pow(pow((Igr4e/Igr4),2)+pow((2*0.05)/T[3],2),0.5);
		
		Double_t y[n2] = {y1,y2,y3,y4};
		Double_t x[n2] = {x1,x2,x3,x4};
		Double_t ex[n2] = {x1e,x2e,x3e,x4e};
		Double_t ey[n2] = {y1e,y2e,y3e,y4e};
			
		TCanvas *c2 = new TCanvas("c5","c5",600,700);
		TGraphErrors *grv = new TGraphErrors(n2,x,y,ex,ey);
			grv->SetMarkerColor(1);
			grv->SetMarkerStyle(33);
			grv->GetXaxis()->SetTitle("1/T (K^-1)");
			grv->GetYaxis()->SetTitle("ln(I/T^2) (ln(nA/K^2))");
			grv->GetYaxis()->SetTitleOffset(1.3);
			grv->SetTitle("Photodiode 2: Leakage Current Temperature Dependence (92V)");
			grv->SetLineColorAlpha(1,0.5);
					
		grv->Draw("AP");
		
		TF1* fit5 = new TF1("fit5","pol1", 1/T[0],1/T[3]);
		grv->Fit(fit5);
		
		double m = fit5->GetParameter(1);
		double me = fit5->GetParError(1);
		
		std::cout<< m <<" "<< me << std::endl;
		std::cout<< "Eg = (" << m*2*8.6173303e-5*(-1) << " +/- " << me*2*8.6173303e-5 << ") eV" << std::endl;
		
	return 0;
}
