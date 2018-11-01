void CV1502_irradiated()
{
	TGraphErrors *gr1 = new TGraphErrors("Diode4_CV_1502_10kHz_irradiated.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode6_CV_1502_10kHz_irradiated.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode8_CV_1502_10kHz_irradiated.txt");
	TGraphErrors *gr4 = new TGraphErrors("Diode15_CV_1502_10kHz_irradiated.txt");
	
	TF1* fitD41 = new TF1("fit1","pol1",1.0,4.3);
	TF1* fitD42 = new TF1("fit2","pol1",4.4,5.3);	
	fitD41->SetParameter(1,-1.5);
	fitD42->SetParameter(1,-1);

	TF1* fitD61 = new TF1("fit1","pol1",1.0,4.5);
	TF1* fitD62 = new TF1("fit2","pol1",4.55,5.15);	
	fitD61->SetParameter(1,-1);
	fitD62->SetParameter(1,-1);

	TF1* fitD81 = new TF1("fit1","pol1",1.0,4.0);
	TF1* fitD82 = new TF1("fit2","pol1",4.1,5.0);	
	fitD81->SetParameter(1,-2);
	fitD82->SetParameter(1,-1);

	TF1* fitD151 = new TF1("fit1","pol1",1.0,4.1);
	TF1* fitD152 = new TF1("fit2","pol1",4.4,5.2);	
	fitD151->SetParameter(1,-1);
	fitD152->SetParameter(1,-1);

	TCanvas *D4 = new TCanvas("D4","D4",600,700);
		gr1->Draw("ALP");
		gr1->Fit(fitD41,"RN");
		gr1->Fit(fitD42,"RN");
		fitD41->Draw("same");
		fitD42->Draw("same");
	
	TCanvas *D6 = new TCanvas("D6","D6",600,700);
		gr2->Draw("ALP");
		gr2->Fit(fitD61,"RN");
		gr2->Fit(fitD62,"RN");
		fitD61->Draw("same");
		fitD62->Draw("same");

	TCanvas *D8 = new TCanvas("D8","D8",600,700);
		gr3->Draw("ALP");
		gr3->Fit(fitD81,"RN");
		gr3->Fit(fitD82,"RN");
		fitD81->Draw("same");
		fitD82->Draw("same");

	TCanvas *D15 = new TCanvas("D15","D15",600,700);
		gr4->Draw("ALP");
		gr4->Fit(fitD151,"RN");
		gr4->Fit(fitD152,"RN");
		fitD151->Draw("same");
		fitD152->Draw("same");

	double cD41 = fitD41->GetParameter(0);
	double mD41 = fitD41->GetParameter(1);
	double cD42 = fitD42->GetParameter(0);
	double mD42 = fitD42->GetParameter(1);
	double ecD41 = fitD41->GetParError(0);
	double emD41 = fitD41->GetParError(1);
	double ecD42 = fitD42->GetParError(0);
	double emD42 = fitD42->GetParError(1);
    double IntersectD4 = (cD42-cD41)/(mD41-mD42); 
	double eD41 = ecD42/(mD41-mD42);
	double eD42 = ecD41/(mD41-mD42);
	double eD43 = emD41*(cD42-cD41)/(pow(mD41-mD42,2));
	double eD44 = emD42*(cD42-cD41)/(pow(mD41-mD42,2));
    double eIntersectD4 = pow(eD41*eD41+eD42*eD42+eD43*eD43+eD44*eD44,0.5);

	double cD61 = fitD61->GetParameter(0);
	double mD61 = fitD61->GetParameter(1);
	double cD62 = fitD62->GetParameter(0);
	double mD62 = fitD62->GetParameter(1);
	double ecD61 = fitD61->GetParError(0);
	double emD61 = fitD61->GetParError(1);
	double ecD62 = fitD62->GetParError(0);
	double emD62 = fitD62->GetParError(1);
    double IntersectD6 = (cD62-cD61)/(mD61-mD62); 
	double eD61 = ecD62/(mD61-mD62);
	double eD62 = ecD61/(mD61-mD62);
	double eD63 = emD61*(cD62-cD61)/(pow(mD61-mD62,2));
	double eD64 = emD62*(cD62-cD61)/(pow(mD61-mD62,2));
    double eIntersectD6 = pow(eD61*eD61+eD62*eD62+eD63*eD63+eD64*eD64,0.5);

	double cD81 = fitD81->GetParameter(0);
	double mD81 = fitD81->GetParameter(1);
	double cD82 = fitD82->GetParameter(0);
	double mD82 = fitD82->GetParameter(1);
	double ecD81 = fitD81->GetParError(0);
	double emD81 = fitD81->GetParError(1);
	double ecD82 = fitD82->GetParError(0);
	double emD82 = fitD82->GetParError(1);
    double IntersectD8 = (cD82-cD81)/(mD81-mD82); 
	double eD81 = ecD82/(mD81-mD82);
	double eD82 = ecD81/(mD81-mD82);
	double eD83 = emD81*(cD82-cD81)/(pow(mD81-mD82,2));
	double eD84 = emD82*(cD82-cD81)/(pow(mD81-mD82,2));
    double eIntersectD8 = pow(eD81*eD81+eD82*eD82+eD83*eD83+eD84*eD84,0.5);

	double cD151 = fitD151->GetParameter(0);
	double mD151 = fitD151->GetParameter(1);
	double cD152 = fitD152->GetParameter(0);
	double mD152 = fitD152->GetParameter(1);
	double ecD151 = fitD151->GetParError(0);
	double emD151 = fitD151->GetParError(1);
	double ecD152 = fitD152->GetParError(0);
	double emD152 = fitD152->GetParError(1);
    double IntersectD15 = (cD152-cD151)/(mD151-mD152); 
	double eD151 = ecD152/(mD151-mD152);
	double eD152 = ecD151/(mD151-mD152);
	double eD153 = emD151*(cD152-cD151)/(pow(mD151-mD152,2));
	double eD154 = emD152*(cD152-cD151)/(pow(mD151-mD152,2));
    double eIntersectD15 = pow(eD151*eD151+eD152*eD152+eD153*eD153+eD154*eD154,0.5);

	double VD4 = -exp(IntersectD4);
	double VD4e = exp(IntersectD4)*eIntersectD4;

	double VD6 = -exp(IntersectD6);
	double VD6e = exp(IntersectD6)*eIntersectD6;

	double VD8 = -exp(IntersectD8);
	double VD8e = exp(IntersectD8)*eIntersectD8;

	double VD15 = -exp(IntersectD15);
	double VD15e = exp(IntersectD15)*eIntersectD15;

	const Int_t n = 4;
	Double_t y[n] = {VD4, VD6, VD8, VD15};
	Double_t x[n] = {6.29e11, 1.55e12, 1.55e12, 2.72e11};
	Double_t ey[n] = {VD4e, VD6e, VD8e, VD15e};
	Double_t ex[n] = {0.06e11, 0.02e12, 0.02e12, 0.03e11};

	TF1* fit = new TF1("fit","pol1",2.0e11,2.0e12);
	TCanvas *Results = new TCanvas("Results","Results",600,700);
	TGraphErrors *Result = new TGraphErrors(n,x,y,ex,ey);
		Result->SetTitle("Max Depletion Voltage vs Proton Fluence 15/02");
		Result->GetXaxis()->SetTitle("Fluence (p/cm^2)");
		Result->GetYaxis()->SetTitle("Max Depletion Voltage (V)");
		Result->SetMarkerStyle(24);
		Result->Fit(fit,"RN");
		
		TLatex *latex1 = new TLatex(Result->GetX()[0], Result->GetY()[0],"Diode 4");
		TLatex *latex2 = new TLatex(Result->GetX()[1], Result->GetY()[1],"Diode 6");
		TLatex *latex3 = new TLatex(Result->GetX()[2], Result->GetY()[2],"Diode 8");
		TLatex *latex4 = new TLatex(Result->GetX()[3], Result->GetY()[3],"Diode 15");
		Result->GetListOfFunctions()->Add(latex1);
		Result->GetListOfFunctions()->Add(latex2);
		Result->GetListOfFunctions()->Add(latex3);
		Result->GetListOfFunctions()->Add(latex4);
		latex1->SetTextSize(0.03); 
		latex2->SetTextSize(0.03); 
		latex3->SetTextSize(0.03); 
		latex4->SetTextSize(0.03); 

		Result->Draw("AP");
		fit->Draw("same");
	

	std::cout << "Diode 4 Max Depletion Voltage = " << VD4 << " +/- " << VD4e << " V" << std::endl;
	std::cout << "Diode 6 Max Depletion Voltage = " << VD6 << " +/- " << VD6e << " V" << std::endl;
	std::cout << "Diode 8 Max Depletion Voltage = " << VD8 << " +/- " << VD8e << " V" << std::endl;
	std::cout << "Diode 15 Max Depletion Voltage = " << VD15 << " +/- " << VD15e << " V" << std::endl;
	
}
