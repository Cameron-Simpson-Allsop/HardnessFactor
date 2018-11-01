void CV2202_irradiated()
{
	TGraphErrors *gr1 = new TGraphErrors("Diode7_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode9_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode10_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr4 = new TGraphErrors("Diode14_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr5 = new TGraphErrors("DiodeKIT1s_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr6 = new TGraphErrors("Diode24_CV_2301_10kHz.txt");
	
	TF1* fitD41 = new TF1("fit1","pol1",1.0,4.3);
	TF1* fitD42 = new TF1("fit2","pol1",4.4,5.0);	
	fitD41->SetParameter(1,-1.5);
	fitD42->SetParameter(1,-0.5);

	TF1* fitD61 = new TF1("fit1","pol1",1.0,4.5);
	TF1* fitD62 = new TF1("fit2","pol1",4.55,5.15);	
	fitD61->SetParameter(1,-1);
	fitD62->SetParameter(1,-1);

	TF1* fitD81 = new TF1("fit1","pol1",1.0,3.8);
	TF1* fitD82 = new TF1("fit2","pol1",4.1,5.0);	
	fitD81->SetParameter(1,-1.5);
	fitD82->SetParameter(1,-1);

	TF1* fitD151 = new TF1("fit1","pol1",1.0,4.1);
	TF1* fitD152 = new TF1("fit2","pol1",4.4,5.2);	
	fitD151->SetParameter(1,-1);
	fitD152->SetParameter(1,-1);

	TF1* fitDKIT1 = new TF1("fit1","pol1",1.0,3.9);
	TF1* fitDKIT2 = new TF1("fit2","pol1",4.0,4.5);	
	fitDKIT1->SetParameter(1,-0.5);
	fitDKIT2->SetParameter(1,-0.3);
	fitDKIT2->SetParameter(0,2.5);

	TF1* fitD241 = new TF1("fitD241","pol1",2.8,4.5);
	TF1* fitD242 = new TF1("fitD242","pol1",4.6,5.3);	
	fitD241->SetParameter(1,-1);
	fitD241->SetParameter(1,-1);

	TCanvas *D4 = new TCanvas("D7","D7",600,700);//7
		gr1->Draw("ALP");
		gr1->Fit(fitD41,"RN");
		gr1->Fit(fitD42,"RN");
		fitD41->Draw("same");
		fitD42->Draw("same");
	
	TCanvas *D6 = new TCanvas("D9","D9",600,700);//9
		gr2->Draw("ALP");
		gr2->Fit(fitD61,"RN");
		gr2->Fit(fitD62,"RN");
		fitD61->Draw("same");
		fitD62->Draw("same");

	TCanvas *D8 = new TCanvas("D10","D10",600,700);//10
		gr3->Draw("ALP");
		gr3->Fit(fitD81,"RN");
		gr3->Fit(fitD82,"RN");
		fitD81->Draw("same");
		fitD82->Draw("same");

	TCanvas *D15 = new TCanvas("D14","D14",600,700);//14
		gr4->Draw("ALP");
		gr4->Fit(fitD151,"RN");
		gr4->Fit(fitD152,"RN");
		fitD151->Draw("same");
		fitD152->Draw("same");
	
	TCanvas *DKIT = new TCanvas("DKIT","DKIT",600,700);//KIT
		gr5->Draw("ALP");
		gr5->Fit(fitDKIT1,"RN");
		gr5->Fit(fitDKIT2,"RN");
		fitDKIT1->Draw("same");
		fitDKIT2->Draw("same");

	/*TCanvas *D24 = new TCanvas("D24","D24",600,700);//24
		gr6->Draw("ALP");
		gr6->Fit(fitDKIT1,"RN");
		gr6->Fit(fitDKIT2,"RN");
		fitD241->Draw("same");
		fitD242->Draw("same");*/

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

	double cDKIT1 = fitDKIT1->GetParameter(0);
	double mDKIT1 = fitDKIT1->GetParameter(1);
	double cDKIT2 = fitDKIT2->GetParameter(0);
	double mDKIT2 = fitDKIT2->GetParameter(1);
	double ecDKIT1 = fitDKIT1->GetParError(0);
	double emDKIT1 = fitDKIT1->GetParError(1);
	double ecDKIT2 = fitDKIT2->GetParError(0);
	double emDKIT2 = fitDKIT2->GetParError(1);
    double IntersectDKIT = (cDKIT2-cDKIT1)/(mDKIT1-mDKIT2); 
	double eDKIT1 = ecDKIT2/(mDKIT1-mDKIT2);
	double eDKIT2 = ecDKIT1/(mDKIT1-mDKIT2);
	double eDKIT3 = emDKIT1*(cDKIT2-cDKIT1)/(pow(mDKIT1-mDKIT2,2));
	double eDKIT4 = emD152*(cDKIT2-cDKIT1)/(pow(mDKIT1-mDKIT2,2));
    double eIntersectDKIT = pow(eDKIT1*eDKIT1+eDKIT2*eDKIT2+eDKIT3*eDKIT3+eDKIT4*eDKIT4,0.5);

	/*double cD241 = fitD241->GetParameter(0);
	double mD241 = fitD241->GetParameter(1);
	double cD242 = fitD242->GetParameter(0);
	double mD242 = fitD242->GetParameter(1);
	double ecD241 = fitD241->GetParError(0);
	double emD241 = fitD241->GetParError(1);
	double ecD242 = fitD242->GetParError(0);
	double emD242 = fitD242->GetParError(1);
    double IntersectD24 = (cD242-cD241)/(mD241-mD242); 
	double eD241 = ecD242/(mD241-mD242);
	double eD242 = ecD241/(mD241-mD242);
	double eD243 = emD241*(cD242-cD241)/(pow(mD241-mD242,2));
	double eD244 = emD242*(cD242-cD241)/(pow(mD241-mD242,2));
    double eIntersectD24 = pow(eD241*eD241+eD242*eD242+eD243*eD243+eD244*eD244,0.5);*/

	double VD4 = -exp(IntersectD4);
	double VD4e = exp(IntersectD4)*eIntersectD4;

	double VD6 = -exp(IntersectD6);
	double VD6e = exp(IntersectD6)*eIntersectD6;

	double VD8 = -exp(IntersectD8);
	double VD8e = exp(IntersectD8)*eIntersectD8;

	double VD15 = -exp(IntersectD15);
	double VD15e = exp(IntersectD15)*eIntersectD15;
	
	double VDKIT = -exp(IntersectDKIT);
	double VDKITe = exp(IntersectDKIT)*eIntersectDKIT;
	
	/*double VD24 = -exp(IntersectD24);
	double VD24e = exp(IntersectD24)*eIntersectD24;*/

	double VD24 = -97.1892, VD24e = 3.95294;

	double calibration = 112.67;
	double calibration_error = 0.55238 + 5.358;

	double rawfluence1 = 1.30e14;
	double rawfluence2 = 5.27e13;
	double rawfluence3 = 5.90e14;
	double rawfluence4 = 2.28e13;
	double rawfluenceKIT = 5.0e12;
	
	double erawfluence1 = 84297588525.2318;
	double erawfluence2 = 74998109020.2371;
	double erawfluence3 = 90393110979.9842;
	double erawfluence4 = 81418286762.212;

	double sys_error = 0.134;

	double fluence1 = rawfluence1/calibration;
	double fluence2 = rawfluence2/calibration;
	double fluence3 = rawfluence3/calibration;
	double fluence4 = rawfluence4/calibration;
	
	double efluence1 = pow(pow(erawfluence1/calibration,2) + pow(rawfluence1*calibration_error/pow(calibration,2),2),0.5);
	double efluence2 = pow(pow(erawfluence2/calibration,2) + pow(rawfluence2*calibration_error/pow(calibration,2),2),0.5);
	double efluence3 = pow(pow(erawfluence3/calibration,2) + pow(rawfluence3*calibration_error/pow(calibration,2),2),0.5);
	double efluence4 = pow(pow(erawfluence4/calibration,2) + pow(rawfluence4*calibration_error/pow(calibration,2),2),0.5);
	double erawfluenceKIT = rawfluenceKIT*sys_error;

	double efluencesys1 = pow(pow(efluence1,2) + pow(fluence1*sys_error,2),0.5);
	double efluencesys2 = pow(pow(efluence2,2) + pow(fluence2*sys_error,2),0.5);
	double efluencesys3 = pow(pow(efluence3,2) + pow(fluence3*sys_error,2),0.5);
	double efluencesys4 = pow(pow(efluence4,2) + pow(fluence4*sys_error,2),0.5);	

	const Int_t n = 5;
	Double_t y[n] = {VD4, VD6, VD8, VD15, VD24};
	Double_t x[n] = {fluence1, fluence2, fluence3, fluence4, 0};//fluences
	Double_t ey[n] = {VD4e, VD6e, VD8e, VD15e, VD24};
	Double_t ex[n] = {efluencesys1, efluencesys2, efluencesys3, efluencesys4, 0};

	const Int_t i = 1;
	Double_t yKIT[i] = {VDKIT};
	Double_t xKIT[i] = {rawfluenceKIT};//fluences
	Double_t eKITy[i] = {VDKITe};
	Double_t eKITx[i] = {erawfluenceKIT};

	TCanvas *Results = new TCanvas("Results","Results",600,700);
	TGraphErrors *Result1 = new TGraphErrors(n,x,y,ex,ey);
	TGraphErrors *Result2 = new TGraphErrors(i,xKIT,yKIT,eKITx,eKITy);
		TGaxis::SetMaxDigits(3);
		Result1->SetTitle("");
		Result1->GetXaxis()->SetTitle("Fluence #left(pcm^{-2}#right)");
		Result1->GetYaxis()->SetTitle("Max. Depletion Voltage (V)");
		Result1->SetMarkerStyle(20);
		Result2->SetMarkerStyle(24);
		
		/*TLatex *latex1 = new TLatex(Result->GetX()[0], Result->GetY()[0],"Diode 7");
		TLatex *latex2 = new TLatex(Result->GetX()[1], Result->GetY()[1],"Diode 9");
		TLatex *latex3 = new TLatex(Result->GetX()[2], Result->GetY()[2],"Diode 10");
		TLatex *latex4 = new TLatex(Result->GetX()[3], Result->GetY()[3],"Diode 14");
		TLatex *latex5 = new TLatex(Result->GetX()[4], Result->GetY()[4],"Diode KIT 1s");
		TLatex *latex6 = new TLatex(Result->GetX()[5], Result->GetY()[5],"Diode 24");
		Result->GetListOfFunctions()->Add(latex1);
		Result->GetListOfFunctions()->Add(latex2);
		Result->GetListOfFunctions()->Add(latex3);
		Result->GetListOfFunctions()->Add(latex4);
		Result->GetListOfFunctions()->Add(latex5);
		Result->GetListOfFunctions()->Add(latex6);
		latex1->SetTextSize(0.02); 
		latex2->SetTextSize(0.02); 
		latex3->SetTextSize(0.02); 
		latex4->SetTextSize(0.02);
		latex5->SetTextSize(0.02);
		latex6->SetTextSize(0.02);*/  

		Result1->Draw("AP");
		Result2->Draw("psame");

	 TLegend *legend = new TLegend(0.15,0.75,0.35,0.85);
   		legend->AddEntry(Result1,"MC40 Diodes","p");
   		legend->AddEntry(Result2,"KIT Diode","p");
   		legend->Draw();

	

	std::cout << "Diode 7 Max Depletion Voltage = " << VD4 << " +/- " << VD4e << " V" << std::endl;
	std::cout << "Diode 9 Max Depletion Voltage = " << VD6 << " +/- " << VD6e << " V" << std::endl;
	std::cout << "Diode 10 Max Depletion Voltage = " << VD8 << " +/- " << VD8e << " V" << std::endl;
	std::cout << "Diode 14 Max Depletion Voltage = " << VD15 << " +/- " << VD15e << " V" << std::endl;
	std::cout << "Diode KIT_1_s Max Depletion Voltage = " << VDKIT << " +/- " << VDKITe << " V" << std::endl;
	std::cout << "Diode 24 Max Depletion Voltage = " << VD24 << " +/- " << VD24e << " V" << std::endl;
	//std::cout << "Gradient = " << fit->GetParameter(1) << " +/- " << fit->GetParError(1) << std::endl;
	
}
