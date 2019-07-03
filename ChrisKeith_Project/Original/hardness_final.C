void hardness_final(){
	//UPDATE FILES AND FLUENCES - in order of spreadsheet
	vector<TString> CFiles = {"Diode_A30_CV.txt", "Diode_B13_CV.txt", "Diode_A23_CV.txt", "Diode_A34_CV.txt", "Diode_B10_CV.txt", "Diode_A13_CV.txt", "Diode_A21_CV.txt", "Diode_A28_CV.txt", "Diode_A22_CV.txt", "Diode_B7_CV.txt", "Diode_A26_CV.txt", "Diode_A19_CV.txt", "Diode_A20_CV.txt", "Diode_A25_CV.txt", "Diode_B6_CV.txt", "Diode_B8_CV.txt", "Diode_B14_CV.txt", "Diode_A27_CV.txt", "Diode_A17_CV.txt", "Diode_B5_CV.txt", "Diode_B11_CV.txt", "Diode_A33_CV.txt", "Diode_B4_CV.txt", "Diode_A35_CV.txt"};
	vector<TString> IFiles = {"Diode_A30_IV.txt", "Diode_B13_IV.txt", "Diode_A23_IV.txt", "Diode_A34_IV.txt", "Diode_B10_IV.txt", "Diode_A13_IV.txt", "Diode_A21_IV.txt", "Diode_A28_IV.txt", "Diode_A22_IV.txt", "Diode_B7_IV.txt", "Diode_A26_IV.txt", "Diode_A19_IV.txt", "Diode_A20_IV.txt", "Diode_A25_IV.txt", "Diode_B6_IV.txt", "Diode_B8_IV.txt", "Diode_B14_IV.txt", "Diode_A27_IV.txt", "Diode_A17_IV.txt", "Diode_B5_IV.txt", "Diode_B11_IV.txt", "Diode_A33_IV.txt", "Diode_B4_IV.txt", "Diode_A35_IV.txt"};
	vector<TString> IrradCFiles = {"Irrad_Diode_A30_CV.txt", "Irrad_Diode_B13_CV.txt", "Irrad_Diode_A23_CV.txt", "Irrad_Diode_A34_CV.txt", "Irrad_Diode_B10_CV.txt", "Irrad_Diode_A13_CV.txt", "Irrad_Diode_A21_CV.txt", "Irrad_Diode_A28_CV.txt", "Irrad_Diode_A22_CV.txt", "Irrad_Diode_B7_CV.txt", "Irrad_Diode_A26_CV.txt", "Irrad_Diode_A19_CV.txt", "Irrad_Diode_A20_CV.txt", "Irrad_Diode_A25_CV.txt", "Irrad_Diode_B6_CV.txt", "Irrad_Diode_B8_CV.txt", "Irrad_Diode_B14_CV.txt", "Irrad_Diode_A27_CV.txt", "Irrad_Diode_A17_CV.txt", "Irrad_Diode_B5_CV.txt", "Irrad_Diode_B11_CV.txt", "Irrad_Diode_A33_CV.txt", "Irrad_Diode_B4_CV.txt", "Irrad_Diode_A35_CV.txt"};
	vector<TString> IrradIFiles = {"Irrad_Diode_A30_IV.txt", "Irrad_Diode_B13_IV.txt", "Irrad_Diode_A23_IV.txt", "Irrad_Diode_A34_IV.txt", "Irrad_Diode_B10_IV.txt", "Irrad_Diode_A13_IV.txt", "Irrad_Diode_A21_IV.txt", "Irrad_Diode_A28_IV.txt", "Irrad_Diode_A22_IV.txt", "Irrad_Diode_B7_IV.txt", "Irrad_Diode_A26_IV.txt", "Irrad_Diode_A19_IV.txt", "Irrad_Diode_A20_IV.txt", "Irrad_Diode_A25_IV.txt", "Irrad_Diode_B6_IV.txt", "Irrad_Diode_B8_IV.txt", "Irrad_Diode_B14_IV.txt", "Irrad_Diode_A27_IV.txt", "Irrad_Diode_A17_IV.txt", "Irrad_Diode_B5_IV.txt", "Irrad_Diode_B11_IV.txt", "Irrad_Diode_A33_IV.txt", "Irrad_Diode_B4_IV.txt", "Irrad_Diode_A35_IV.txt"};
	
	vector<TString> CFilesOutput = {"Diode_A30_CV.pdf", "Diode_B13_CV.pdf", "Diode_A23_CV.pdf", "Diode_A34_CV.pdf", "Diode_B10_CV.pdf", "Diode_A13_CV.pdf", "Diode_A21_CV.pdf", "Diode_A28_CV.pdf", "Diode_A22_CV.pdf", "Diode_B7_CV.pdf", "Diode_A26_CV.pdf", "Diode_A19_CV.pdf", "Diode_A20_CV.pdf", "Diode_A25_CV.pdf", "Diode_B6_CV.pdf", "Diode_B8_CV.pdf", "Diode_B14_CV.pdf", "Diode_A27_CV.pdf", "Diode_A17_CV.pdf", "Diode_B5_CV.pdf", "Diode_B11_CV.pdf", "Diode_A33_CV.pdf", "Diode_B4_CV.pdf", "Diode_A35_CV.pdf"};
	vector<TString> IFilesOutput = {"Diode_A30_IV.pdf", "Diode_B13_IV.pdf", "Diode_A23_IV.pdf", "Diode_A34_IV.pdf", "Diode_B10_IV.pdf", "Diode_A13_IV.pdf", "Diode_A21_IV.pdf", "Diode_A28_IV.pdf", "Diode_A22_IV.pdf", "Diode_B7_IV.pdf", "Diode_A26_IV.pdf", "Diode_A19_IV.pdf", "Diode_A20_IV.pdf", "Diode_A25_IV.pdf", "Diode_B6_IV.pdf", "Diode_B8_IV.pdf", "Diode_B14_IV.pdf", "Diode_A27_IV.pdf", "Diode_A17_IV.pdf", "Diode_B5_IV.pdf", "Diode_B11_IV.pdf", "Diode_A33_IV.pdf", "Diode_B4_IV.pdf", "Diode_A35_IV.pdf"};
	vector<TString> IrradCFilesOutput = {"Irrad_Diode_A30_CV.pdf", "Irrad_Diode_B13_CV.pdf", "Irrad_Diode_A23_CV.pdf", "Irrad_Diode_A34_CV.pdf", "Irrad_Diode_B10_CV.pdf", "Irrad_Diode_A13_CV.pdf", "Irrad_Diode_A21_CV.pdf", "Irrad_Diode_A28_CV.pdf", "Irrad_Diode_A22_CV.pdf", "Irrad_Diode_B7_CV.pdf", "Irrad_Diode_A26_CV.pdf", "Irrad_Diode_A19_CV.pdf", "Irrad_Diode_A20_CV.pdf", "Irrad_Diode_A25_CV.pdf", "Irrad_Diode_B6_CV.pdf", "Irrad_Diode_B8_CV.pdf", "Irrad_Diode_B14_CV.pdf", "Irrad_Diode_A27_CV.pdf", "Irrad_Diode_A17_CV.pdf", "Irrad_Diode_B5_CV.pdf", "Irrad_Diode_B11_CV.pdf", "Irrad_Diode_A33_CV.pdf", "Irrad_Diode_B4_CV.pdf", "Irrad_Diode_A35_CV.pdf"};
	vector<TString> IrradIFilesOutput = {"Irrad_Diode_A30_IV.pdf", "Irrad_Diode_B13_IV.pdf", "Irrad_Diode_A23_IV.pdf", "Irrad_Diode_A34_IV.pdf", "Irrad_Diode_B10_IV.pdf", "Irrad_Diode_A13_IV.pdf", "Irrad_Diode_A21_IV.pdf", "Irrad_Diode_A28_IV.pdf", "Irrad_Diode_A22_IV.pdf", "Irrad_Diode_B7_IV.pdf", "Irrad_Diode_A26_IV.pdf", "Irrad_Diode_A19_IV.pdf", "Irrad_Diode_A20_IV.pdf", "Irrad_Diode_A25_IV.pdf", "Irrad_Diode_B6_IV.pdf", "Irrad_Diode_B8_IV.pdf", "Irrad_Diode_B14_IV.pdf", "Irrad_Diode_A27_IV.pdf", "Irrad_Diode_A17_IV.pdf", "Irrad_Diode_B5_IV.pdf", "Irrad_Diode_B11_IV.pdf", "Irrad_Diode_A33_IV.pdf", "Irrad_Diode_B4_IV.pdf", "Irrad_Diode_A35_IV.pdf"};
	
	vector<double> Temp = {22.5, 23.2, 23.8, 24.4, 23.0, 23.3, 23.6, 21.7, 24.0, 23.0, 23.8, 23.1, 23.8, 23.9, 22.8, 22.9, 23.1, 23.8, 22.9, 22.9, 23.6, 24.1, 22.6, 23.9};
	vector<double> IrradTemp = {22.0, 22.2, 22.7, 22.5, 22.8, 21.1, 22.3, 22.4, 22.2, 22.5, 22.7, 20.9, 22.5, 21.8, 22.0, 22.0, 21.6, 22.2, 21.9, 22.2, 22.7, 22.0, 22.3, 22.4};
	
	vector<double> Flux = {1.632476E+13, 1.632476E+13, 7.468142E+12, 7.468142E+12, 3.308547E+12, 3.308547E+12, 1.085514E+12, 1.085514E+12, 5.759165E+11, 5.759165E+11, 2.963700E+11, 2.963700E+11, 6.629542E+13, 6.629542E+13, 3.522630E+13, 3.522630E+13, 8.802586E+12, 8.802586E+12, 5.117908E+12, 5.117908E+12, 1.388061E+12, 1.388061E+12, 7.776403E+11, 7.776403E+11};
	vector<double> FluxErr = {2.832364E+12, 2.832364E+12, 1.309618E+12, 1.309618E+12, 5.989873E+11, 5.989873E+11, 2.040548E+11, 2.040548E+11, 1.121750E+11, 1.121750E+11, 6.174985E+10, 6.174985E+10, 1.149082E+13, 1.149082E+13, 6.202810E+12, 6.202810E+12, 1.578380E+12, 1.578380E+12, 9.250379E+11, 9.250379E+11, 2.695016E+11, 2.695016E+11, 1.621034E+11, 1.621034E+11}; //15%
	
	double VdOffsetMin = 0;
	double VdOffsetMax = 1;
	//short for singular outputs, up to 70-90 for offset plot
	
	int VdOffsetPoints = (VdOffsetMax - VdOffsetMin)*1;
	
	vector<double> VdOffset(VdOffsetPoints + 1);
	
	for(int i = 0; i < VdOffsetPoints + 1; i++){
		VdOffset[i] = VdOffsetMin + i*((VdOffsetMax - VdOffsetMin)/VdOffsetPoints);
	}
	
	int NFiles = CFiles.size();
	
	int NOffsets = VdOffset.size();
	
	vector<vector<double>> CLnV, CLnC, CLnVErr, CLnCErr, IVol, ICurr, IVolErr, ICurrErr;
	vector<vector<double>> IrradCLnV, IrradCLnC, IrradCLnVErr, IrradCLnCErr, IrradIVol, IrradICurr, IrradIVolErr, IrradICurrErr;
	
	vector<double> CPoints, IPoints, LnVd, LnVdErr, Vd, VdErr, VdEval, p1, p2, CGrad1, CGrad1Err, CGrad2, CGrad2Err, I_VdEval, I_VdEvalErr;
	vector<double> IrradCPoints, IrradIPoints, IrradLnVd, IrradLnVdErr, IrradVd, IrradVdErr, IrradVdEval, Irradp1, Irradp2, IrradCGrad1, IrradCGrad1Err, IrradCGrad2, IrradCGrad2Err, IrradI_VdEval, IrradI_VdEvalErr;
	vector<double> dCurr, dCurrErr;
	vector<double> Grad, GradErr, Alpha, AlphaErr, Kappa, KappaErr;
	
	
	for(int i = 0; i < NFiles; i++){
		double col1, col2, col3;
		double tCPoints, tIPoints, tIrradCPoints, tIrradIPoints;
		double T_R = 293.15, E = 1.12, k_B = 8.617e-5, TempOffset = 0.7, TempErr = 0.2;
		double T, Scaling, ScalingErr;
		
		vector<double> tCLnV, tCLnC, tCLnCErr, tIVol, tICurr, tICurrErr;
		vector<double> tIrradCLnV, tIrradCLnC, tIrradCLnCErr, tIrradIVol, tIrradICurr, tIrradICurrErr;
		
		ifstream CFile(CFiles[i]), IFile(IFiles[i]), IrradCFile(IrradCFiles[i]), IrradIFile(IrradIFiles[i]);
		
		
		//Initial
		while(CFile >> col1 >> col2 >> col3){
			tCLnV.push_back(col1);
			tCLnC.push_back(col2);
			tCLnCErr.push_back(col3);
		}
		
		CFile.close();
		
		tCPoints = tCLnV.size();
		
		double VErrValue = 0.05;
		double LnVErrValue = log(VErrValue);
		
		vector<double> tCLnVErr (tCPoints, LnVErrValue);
		
		CLnV.push_back(tCLnV);
		CLnC.push_back(tCLnC);
		CLnVErr.push_back(tCLnVErr);
		CLnCErr.push_back(tCLnCErr);
		CPoints.push_back(tCPoints);
		
		while(IFile >> col1 >> col2 >> col3){
			tIVol.push_back(col1);
			tICurr.push_back(col2);
			tICurrErr.push_back(col3);
		}
		
		IFile.close();
		
		tIPoints = tIVol.size();
		
		vector<double> tIVolErr (tIPoints, VErrValue);
		
		T = 273.15 + Temp[i] + TempOffset;
		
		Scaling = T_R/T*T_R/T*exp((-E/(2*k_B))*(1/T_R - 1/T));
		ScalingErr = TempErr*-(T_R*T_R*(E+4*k_B*T)*exp(-(E*(1/T_R - 1/T))/(2*k_B)))/(2*k_B*T*T*T*T);
		
		for(int j = 0; j < tIPoints; j++){
			double ICurrUnscaled = tICurr[j];
			double ICurrErrUnscaled = tICurrErr[j];
			
			double ICurrScaled = ICurrUnscaled*Scaling;
			double ICurrErrScaled = sqrt(ICurrErrUnscaled*ICurrErrUnscaled*Scaling*Scaling + ScalingErr*ScalingErr*ICurrUnscaled*ICurrUnscaled);
			
			tICurr[j] = ICurrScaled;
			tICurrErr[j] = ICurrErrScaled;
		}
		
		IVol.push_back(tIVol);
		ICurr.push_back(tICurr);
		IVolErr.push_back(tIVolErr);
		ICurrErr.push_back(tICurrErr);
		IPoints.push_back(tIPoints);
		
		
		
		
		
		//Irrad
		while(IrradCFile >> col1 >> col2 >> col3){
			tIrradCLnV.push_back(col1);
			tIrradCLnC.push_back(col2);
			tIrradCLnCErr.push_back(col3);
		}
		
		IrradCFile.close();
		
		tIrradCPoints = tIrradCLnV.size();
		
		vector<double> tIrradCLnVErr (tIrradCPoints, LnVErrValue);
		
		IrradCLnV.push_back(tIrradCLnV);
		IrradCLnC.push_back(tIrradCLnC);
		IrradCLnVErr.push_back(tIrradCLnVErr);
		IrradCLnCErr.push_back(tIrradCLnCErr);
		IrradCPoints.push_back(tIrradCPoints);
		
		while(IrradIFile >> col1 >> col2 >> col3){
			tIrradIVol.push_back(col1);
			tIrradICurr.push_back(col2);
			tIrradICurrErr.push_back(col3);
		}
		
		IrradIFile.close();
		
		tIrradIPoints = tIrradIVol.size();
		
		vector<double> tIrradIVolErr (tIrradIPoints, VErrValue);
		
		T = 273.15 + IrradTemp[i] + TempOffset;
		
		Scaling = T_R/T*T_R/T*exp((-E/(2*k_B))*(1/T_R - 1/T));
		ScalingErr = TempErr*-(T_R*T_R*(E+4*k_B*T)*exp(-(E*(1/T_R - 1/T))/(2*k_B)))/(2*k_B*T*T*T*T);
		
		for(int j = 0; j < tIrradIPoints; j++){
			double IrradICurrUnscaled = tIrradICurr[j];
			double IrradICurrErrUnscaled = tIrradICurrErr[j];
			
			double IrradICurrScaled = IrradICurrUnscaled*Scaling;
			double IrradICurrErrScaled = sqrt(IrradICurrErrUnscaled*IrradICurrErrUnscaled*Scaling*Scaling + ScalingErr*ScalingErr*IrradICurrUnscaled*IrradICurrUnscaled);
			
			tIrradICurr[j] = IrradICurrScaled;
			tIrradICurrErr[j] = IrradICurrErrScaled;
		}
		
		IrradIVol.push_back(tIrradIVol);
		IrradICurr.push_back(tIrradICurr);
		IrradIVolErr.push_back(tIrradIVolErr);
		IrradICurrErr.push_back(tIrradICurrErr);
		IrradIPoints.push_back(tIrradIPoints);
	}
	
	
	
	
	for(int k = 0; k < NOffsets; k++){
		double CurrentOffset = VdOffset[k];
		ostringstream CurrentOffsetValue;
		CurrentOffsetValue << fixed;
		CurrentOffsetValue << setprecision(0);
		CurrentOffsetValue << CurrentOffset;
		string CurrentOffsetString = CurrentOffsetValue.str();
		
		
	for(int i = 0; i < NFiles; i++){
		//Initial
		
		TCanvas * CCanvas = new TCanvas("CCanvas","Ln(C) vs. Ln(V)",600,600);
		CCanvas->SetGrid();
		CCanvas->SetLeftMargin(0.15);
		CCanvas->SetBottomMargin(0.15);
		
		TGraphErrors * CGraph = new TGraphErrors(CPoints[i],&CLnV[i][0],&CLnC[i][0],&CLnVErr[i][0],&CLnCErr[i][0]);
		CGraph->SetMarkerStyle(20);
		CGraph->SetMarkerColor(1);
		CGraph->SetLineColor(1);
		CGraph->SetTitle("Ln(C) vs. Ln(V)");
		CGraph->GetXaxis()->SetTitle("Ln(V) /Ln|V|");
		CGraph->GetYaxis()->SetTitle("Ln(C) /Ln(pF)");
		CGraph->GetXaxis()->SetTitleOffset(1.5);
		CGraph->GetYaxis()->SetTitleOffset(1.5);
		
		int FitMax = 0;
		while(CLnC[i][FitMax]>CLnC[i][FitMax+1] || CLnC[i][FitMax+1]>CLnC[i][FitMax+2] || CLnC[i][FitMax+2]>CLnC[i][FitMax+3]){
			if(FitMax+6<CLnC[i].size()) FitMax++;
			else break;
		}
		
		//TF1 * CLine1 = new TF1("CLine1", "pol1", CLnV[i][2], CLnV[i][12]);
		//TF1 * CLine2 = new TF1("CLine2", "pol1", CLnV[i][FitMax-10], CLnV[i][FitMax]);
		TF1 * CLine1 = new TF1("CLine1", "pol1", CLnV[i][3], CLnV[i][9]);
		TF1 * CLine2 = new TF1("CLine2", "pol1", CLnV[i][FitMax-10], CLnV[i][FitMax]);
		
		CLine1->SetParameter(0,3.3);
		CLine1->SetParameter(1,-0.5);
		CLine2->SetParameter(0,2.5);
		CLine2->SetParameter(1,-0.2);
		
		CGraph->Fit("CLine1", "R Q N S");
		CLine1->SetRange(CLnV[i][2], CLnV[i][FitMax]);
		CLine1->SetLineColor(2);

		TVirtualFitter * CLine1Fit = TVirtualFitter::GetFitter();
		TMatrixD CLine1Cov(2,2,CLine1Fit->GetCovarianceMatrix());
		double Ck1ErrSquare = CLine1Fit->GetCovarianceMatrixElement(0,0);
		double Cm1ErrSquare = CLine1Fit->GetCovarianceMatrixElement(1,1);
		double Ccov1 = CLine1Fit->GetCovarianceMatrixElement(0,1);
		
		double Ck1Err = sqrt(Ck1ErrSquare);
		double Cm1Err = sqrt(Cm1ErrSquare);
		
		double tp1 = Ccov1/(Ck1Err*Cm1Err);
		
		
		CGraph->Fit("CLine2", "R Q N S");
		CLine2->SetRange(CLnV[i][2], CLnV[i][FitMax]);
		CLine2->SetLineColor(4);

		TVirtualFitter * CLine2Fit = TVirtualFitter::GetFitter();
		TMatrixD CLine2Cov(2,2,CLine2Fit->GetCovarianceMatrix());
		double Ck2ErrSquare = CLine2Fit->GetCovarianceMatrixElement(0,0);
		double Cm2ErrSquare = CLine2Fit->GetCovarianceMatrixElement(1,1);
		double Ccov2 = CLine2Fit->GetCovarianceMatrixElement(0,1);
		
		double Ck2Err = sqrt(Ck2ErrSquare);
		double Cm2Err = sqrt(Cm2ErrSquare);
		
		double tp2 = Ccov2/(Ck2Err*Cm2Err);
		
		double Ck1 = CLine1->GetParameter(0);
		double Cm1 = CLine1->GetParameter(1);
		double Ck2 = CLine2->GetParameter(0);
		double Cm2 = CLine2->GetParameter(1);

		double Cpartialk1 = 1.0/(Cm2-Cm1);
		double Cpartialk2 = 1.0/(Cm1-Cm2);
		double Cpartialm1 = (Ck1-Ck2)/((Cm2-Cm1)*(Cm2-Cm1));
		double Cpartialm2 = (Ck2-Ck1)/((Cm1-Cm2)*(Cm1-Cm2));
		
		double tLnVd = (Ck2-Ck1)/(Cm1-Cm2);
		double tLnVdErr = sqrt(Ck1ErrSquare*Cpartialk1*Cpartialk1 + Ck2ErrSquare*Cpartialk2*Cpartialk2 + Cm1ErrSquare*Cpartialm1*Cpartialm1 + Cm2ErrSquare*Cpartialm2*Cpartialm2 + 2*Ccov1*Cpartialk1*Cpartialm1 + 2*Ccov2*Cpartialk2*Cpartialm2);
		
		double tVd = -exp(tLnVd);
		double tVdErr = fabs(tVd)*tLnVdErr;
		
		double tVdEval = tVd - CurrentOffset;
		
		//double tVdErr = 5.1;
		
		//double tVdEval = -90.8;
		
		p1.push_back(tp1);
		p2.push_back(tp2);
		CGrad1.push_back(Cm1);
		CGrad1Err.push_back(Cm1Err);
		CGrad2.push_back(Cm2);
		CGrad2Err.push_back(Cm2Err);
		LnVd.push_back(tLnVd);
		LnVdErr.push_back(tLnVdErr);
		Vd.push_back(tVd);
		VdErr.push_back(tVdErr);
		VdEval.push_back(tVdEval);
		

		CGraph->Draw("AP");
		CLine1->Draw("SAME");
		CLine2->Draw("SAME");
		
		CCanvas->Print(CFilesOutput[i]);
		
		
		
		TCanvas * ICanvas = new TCanvas("ICanvas","Reverse IV",600,600);
		ICanvas->SetGrid();
		ICanvas->SetLeftMargin(0.15);
		ICanvas->SetBottomMargin(0.15);
		
		TGraphErrors * IGraph = new TGraphErrors(IPoints[i],&IVol[i][0],&ICurr[i][0],&IVolErr[i][0],&ICurrErr[i][0]);
		IGraph->SetMarkerStyle(20);
		IGraph->SetMarkerColor(1);
		IGraph->SetLineColor(1);
		IGraph->SetTitle("Reverse IV");
		IGraph->GetXaxis()->SetTitle("Voltage /V");
		IGraph->GetYaxis()->SetTitle("Current /A");
		IGraph->GetXaxis()->SetTitleOffset(1.5);
		IGraph->GetYaxis()->SetTitleOffset(1.5);
		
		int VTarget = 0;
		//while(IVol[i][VTarget] > Vd[i]){
		while(IVol[i][VTarget] > VdEval[i]){
			VTarget++;
		}
		
		int IMax = VTarget;
		int IMin = VTarget;
		for(int j = VTarget-4; j <= VTarget+3; j++){
			if(ICurr[i][j] > ICurr[i][IMax]){
				IMax = j;
			}
			if(ICurr[i][j] <= ICurr[i][IMin]){
				IMin = j;
			}
		}
		
		IGraph->GetXaxis()->SetRangeUser(IVol[i][VTarget+3], IVol[i][VTarget-4]);
		IGraph->GetYaxis()->SetRangeUser(ICurr[i][IMin]-1.5*ICurrErr[i][IMin],ICurr[i][IMax]+1.5*ICurrErr[i][IMax]);
		
		TF1 * IFit = new TF1("IFit", "[0]+[1]*sqrt(fabs(x))", IVol[i][VTarget+2], IVol[i][VTarget-3]);
		
		IFit->SetParameter(0,-1.82e-11);
		IFit->SetParameter(1,-1.82e-11);

		IGraph->Fit("IFit", "R Q N");
		IFit->SetRange(IVol[i][VTarget+2], IVol[i][VTarget-3]);
		IFit->SetLineColor(2);
		
		double Ik = IFit->GetParameter(0);
		double Im = IFit->GetParameter(1);
		double IkErr = IFit->GetParError(0);
		double ImErr = IFit->GetParError(1);
		
		double Ipartialk = 1;
		//double Ipartialm = sqrt(fabs(Vd[i]));
		//double IpartialVd = Im/(2.0*sqrt(fabs(Vd[i])));
		double Ipartialm = sqrt(fabs(VdEval[i]));
		double IpartialVdEval = Im/(2.0*sqrt(fabs(VdEval[i])));
		
		//double tI_Vd = Ik + Im*sqrt(fabs(Vd[i]));
		//double tI_VdErr = sqrt(ImErr*ImErr*Ipartialm*Ipartialm + VdErr[i]*VdErr[i]*IpartialVd*IpartialVd);
		double tI_VdEval = Ik + Im*sqrt(fabs(VdEval[i]));
		double tI_VdEvalErr = sqrt(ImErr*ImErr*Ipartialm*Ipartialm + VdErr[i]*VdErr[i]*IpartialVdEval*IpartialVdEval);
		
		//I_Vd.push_back(tI_Vd);
		//I_VdErr.push_back(tI_VdErr);
		I_VdEval.push_back(tI_VdEval);
		I_VdEvalErr.push_back(tI_VdEvalErr);
		
		IGraph->Draw("AP");
		IFit->Draw("SAME");
		
		ICanvas->Print(IFilesOutput[i]);
		
		
		
		
		
		
		
		//Irrad
		TCanvas * IrradCCanvas = new TCanvas("IrradCCanvas","Ln(C) vs. Ln(V)",600,600);
		IrradCCanvas->SetGrid();
		IrradCCanvas->SetLeftMargin(0.15);
		IrradCCanvas->SetBottomMargin(0.15);
		
		TGraphErrors * IrradCGraph = new TGraphErrors(IrradCPoints[i],&IrradCLnV[i][0],&IrradCLnC[i][0],&IrradCLnVErr[i][0],&IrradCLnCErr[i][0]);
		IrradCGraph->SetMarkerStyle(20);
		IrradCGraph->SetMarkerColor(1);
		IrradCGraph->SetLineColor(1);
		IrradCGraph->SetTitle("Ln(C) vs. Ln(V)");
		IrradCGraph->GetXaxis()->SetTitle("Ln(V) /Ln|V|");
		IrradCGraph->GetYaxis()->SetTitle("Ln(C) /Ln(pF)");
		IrradCGraph->GetXaxis()->SetTitleOffset(1.5);
		IrradCGraph->GetYaxis()->SetTitleOffset(1.5);
		
		
		int IrradFitMax = 0;
		while(IrradCLnC[i][IrradFitMax]>IrradCLnC[i][IrradFitMax+1] || IrradCLnC[i][IrradFitMax+1]>IrradCLnC[i][IrradFitMax+2] || IrradCLnC[i][IrradFitMax+2]>IrradCLnC[i][IrradFitMax+3]){
			if(IrradFitMax+6<IrradCLnC[i].size()) IrradFitMax++;
			else break;
		}
		
		
		//TF1 * IrradCLine1 = new TF1("IrradCLine1", "pol1", IrradCLnV[i][2], IrradCLnV[i][12]);
		//TF1 * IrradCLine2 = new TF1("IrradCLine2", "pol1", IrradCLnV[i][IrradFitMax-10], IrradCLnV[i][IrradFitMax]);
		TF1 * IrradCLine1 = new TF1("IrradCLine1", "pol1", IrradCLnV[i][3], IrradCLnV[i][9]);
		TF1 * IrradCLine2 = new TF1("IrradCLine2", "pol1", IrradCLnV[i][IrradFitMax-10], IrradCLnV[i][IrradFitMax]);
		
		IrradCLine1->SetParameter(0,3.3);
		IrradCLine1->SetParameter(1,-0.5);
		IrradCLine2->SetParameter(0,2.5);
		IrradCLine2->SetParameter(1,-0.2);
		
		IrradCGraph->Fit("IrradCLine1", "R Q N S");
		IrradCLine1->SetRange(IrradCLnV[i][2], IrradCLnV[i][IrradFitMax]);
		IrradCLine1->SetLineColor(2);

		TVirtualFitter * IrradCLine1Fit = TVirtualFitter::GetFitter();
		TMatrixD IrradCLine1Cov(2,2,IrradCLine1Fit->GetCovarianceMatrix());
		double IrradCk1ErrSquare = IrradCLine1Fit->GetCovarianceMatrixElement(0,0);
		double IrradCm1ErrSquare = IrradCLine1Fit->GetCovarianceMatrixElement(1,1);
		double IrradCcov1 = IrradCLine1Fit->GetCovarianceMatrixElement(0,1);
		
		double IrradCk1Err = sqrt(IrradCk1ErrSquare);
		double IrradCm1Err = sqrt(IrradCm1ErrSquare);
		
		double tIrradp1 = IrradCcov1/(IrradCk1Err*IrradCm1Err);
		
		
		IrradCGraph->Fit("IrradCLine2", "R Q N S");
		IrradCLine2->SetRange(IrradCLnV[i][2], IrradCLnV[i][IrradFitMax]);
		IrradCLine2->SetLineColor(4);

		TVirtualFitter * IrradCLine2Fit = TVirtualFitter::GetFitter();
		TMatrixD IrradCLine2Cov(2,2,IrradCLine2Fit->GetCovarianceMatrix());
		double IrradCk2ErrSquare = IrradCLine2Fit->GetCovarianceMatrixElement(0,0);
		double IrradCm2ErrSquare = IrradCLine2Fit->GetCovarianceMatrixElement(1,1);
		double IrradCcov2 = IrradCLine2Fit->GetCovarianceMatrixElement(0,1);
		
		double IrradCk2Err = sqrt(IrradCk2ErrSquare);
		double IrradCm2Err = sqrt(IrradCm2ErrSquare);
		
		double tIrradp2 = IrradCcov2/(IrradCk2Err*IrradCm2Err);
		
		double IrradCk1 = IrradCLine1->GetParameter(0);
		double IrradCm1 = IrradCLine1->GetParameter(1);
		double IrradCk2 = IrradCLine2->GetParameter(0);
		double IrradCm2 = IrradCLine2->GetParameter(1);

		double IrradCpartialk1 = 1.0/(IrradCm2-IrradCm1);
		double IrradCpartialk2 = 1.0/(IrradCm1-IrradCm2);
		double IrradCpartialm1 = (IrradCk1-IrradCk2)/((IrradCm2-IrradCm1)*(IrradCm2-IrradCm1));
		double IrradCpartialm2 = (IrradCk2-IrradCk1)/((IrradCm1-IrradCm2)*(IrradCm1-IrradCm2));
		
		double tIrradLnVd = (IrradCk2-IrradCk1)/(IrradCm1-IrradCm2);
		double tIrradLnVdErr = sqrt(IrradCk1ErrSquare*IrradCpartialk1*IrradCpartialk1 + IrradCk2ErrSquare*IrradCpartialk2*IrradCpartialk2 + IrradCm1ErrSquare*IrradCpartialm1*IrradCpartialm1 + IrradCm2ErrSquare*IrradCpartialm2*IrradCpartialm2 + 2*IrradCcov1*IrradCpartialk1*IrradCpartialm1 + 2*IrradCcov2*IrradCpartialk2*IrradCpartialm2);
		
		double tIrradVd = -exp(tIrradLnVd);
		double tIrradVdErr = fabs(tIrradVd)*tIrradLnVdErr;
		
		double tIrradVdEval = tIrradVd - CurrentOffset;
		
		//double tIrradVdErr = 5.1;
		
		//double tIrradVdEval = -90.8;
		
		Irradp1.push_back(tIrradp1);
		Irradp2.push_back(tIrradp2);
		IrradCGrad1.push_back(IrradCm1);
		IrradCGrad1Err.push_back(IrradCm1Err);
		IrradCGrad2.push_back(IrradCm2);
		IrradCGrad2Err.push_back(IrradCm2Err);
		IrradLnVd.push_back(tIrradLnVd);
		IrradLnVdErr.push_back(tIrradLnVdErr);
		IrradVd.push_back(tIrradVd);
		IrradVdErr.push_back(tIrradVdErr);
		IrradVdEval.push_back(tIrradVdEval);
		

		IrradCGraph->Draw("AP");
		IrradCLine1->Draw("SAME");
		IrradCLine2->Draw("SAME");
		
		IrradCCanvas->Print(IrradCFilesOutput[i]);
		
		
		
		TCanvas * IrradICanvas = new TCanvas("IrradICanvas","Reverse IV",600,600);
		IrradICanvas->SetGrid();
		IrradICanvas->SetLeftMargin(0.15);
		IrradICanvas->SetBottomMargin(0.15);
		
		TGraphErrors * IrradIGraph = new TGraphErrors(IrradIPoints[i],&IrradIVol[i][0],&IrradICurr[i][0],&IrradIVolErr[i][0],&IrradICurrErr[i][0]);
		IrradIGraph->SetMarkerStyle(20);
		IrradIGraph->SetMarkerColor(1);
		IrradIGraph->SetLineColor(1);
		IrradIGraph->SetTitle("Reverse IV");
		IrradIGraph->GetXaxis()->SetTitle("Voltage /V");
		IrradIGraph->GetYaxis()->SetTitle("Current /A");
		IrradIGraph->GetXaxis()->SetTitleOffset(1.5);
		IrradIGraph->GetYaxis()->SetTitleOffset(1.5);
		
		int IrradVTarget = 0;
		//while(IrradIVol[i][IrradVTarget] > IrradVd[i]){
		while(IrradIVol[i][IrradVTarget] > IrradVdEval[i]){
			IrradVTarget++;
		}
		
		int IrradIMax = IrradVTarget;
		int IrradIMin = IrradVTarget;
		for(int j = IrradVTarget-4; j <= IrradVTarget+3; j++){
			if(IrradICurr[i][j] > IrradICurr[i][IrradIMax]){
				IrradIMax = j;
			}
			if(IrradICurr[i][j] <= IrradICurr[i][IrradIMin]){
				IrradIMin = j;
			}
		}
		
	        		
		IrradIGraph->GetXaxis()->SetRangeUser(IrradIVol[i][IrradVTarget+3], IrradIVol[i][IrradVTarget-4]);
		IrradIGraph->GetYaxis()->SetRangeUser(IrradICurr[i][IrradIMin]-1.5*IrradICurrErr[i][IrradIMin],IrradICurr[i][IrradIMax]+1.5*IrradICurrErr[i][IrradIMax]);
		
		TF1 * IrradIFit = new TF1("IrradIFit", "[0]+[1]*sqrt(fabs(x))", IrradIVol[i][IrradVTarget+2], IrradIVol[i][IrradVTarget-3]);
		
		IrradIFit->SetParameter(0,-1.82e-11);
		IrradIFit->SetParameter(1,-1.82e-11);

		IrradIGraph->Fit("IrradIFit", "R Q N");
		IrradIFit->SetRange(IrradIVol[i][IrradVTarget+2], IrradIVol[i][IrradVTarget-3]);
		IrradIFit->SetLineColor(2);
		
		double IrradIk = IrradIFit->GetParameter(0);
		double IrradIm = IrradIFit->GetParameter(1);
		double IrradIkErr = IrradIFit->GetParError(0);
		double IrradImErr = IrradIFit->GetParError(1);

		double IrradIpartialk = 1;
		//double IrradIpartialm = sqrt(fabs(IrradVd[i]));
		//double IrradIpartialVd = IrradIm/(2.0*sqrt(fabs(IrradVd[i])));
		double IrradIpartialm = sqrt(fabs(IrradVdEval[i]));
		double IrradIpartialVdEval = IrradIm/(2.0*sqrt(fabs(IrradVdEval[i])));
		
		//double tIrradI_Vd = IrradIk + IrradIm*sqrt(fabs(IrradVd[i]));
		//double tIrradI_VdErr = sqrt(IrradImErr*IrradImErr*IrradIpartialm*IrradIpartialm + IrradVdErr[i]*IrradVdErr[i]*IrradIpartialVd*IrradIpartialVd);
		double tIrradI_VdEval = IrradIk + IrradIm*sqrt(fabs(IrradVdEval[i]));
		double tIrradI_VdEvalErr = sqrt(IrradImErr*IrradImErr*IrradIpartialm*IrradIpartialm + IrradVdErr[i]*IrradVdErr[i]*IrradIpartialVdEval*IrradIpartialVdEval);
		
		//IrradI_Vd.push_back(tIrradI_Vd);
		//IrradI_VdErr.push_back(tIrradI_VdErr);
		IrradI_VdEval.push_back(tIrradI_VdEval);
		IrradI_VdEvalErr.push_back(tIrradI_VdEvalErr);
		
		
		IrradIGraph->Draw("AP");
		IrradIFit->Draw("SAME");
		
		IrradICanvas->Print(IrradIFilesOutput[i]);
		
		
		
		//Compare at unirradiated Vd
		//double I_VdCompare = IrradIk + IrradIm*sqrt(fabs(Vd[i]));
		double I_VdEvalCompare = IrradIk + IrradIm*sqrt(fabs(VdEval[i]));

		
		//double I_VdCompareErr = sqrt(IrradIkErr*IrradIkErr*IrradIpartialk*IrradIpartialk + IrradImErr*IrradImErr*IrradIpartialm*IrradIpartialm + VdErr[i]*VdErr[i]*IpartialVd*IpartialVd);
		double I_VdEvalCompareErr = sqrt(IrradIkErr*IrradIkErr*IrradIpartialk*IrradIpartialk + IrradImErr*IrradImErr*IrradIpartialm*IrradIpartialm + VdErr[i]*VdErr[i]*IpartialVdEval*IpartialVdEval);
		
		//double tdCurr =  tI_Vd - I_VdCompare;
		//double tdCurrErr = sqrt(I_VdCompareErr*I_VdCompareErr + tI_VdErr*tI_VdErr);
		double tdCurr =  tI_VdEval - I_VdEvalCompare;
		double tdCurrErr = sqrt(I_VdEvalCompareErr*I_VdEvalCompareErr + tI_VdEvalErr*tI_VdEvalErr);
		
		
		dCurr.push_back(tdCurr);
		dCurrErr.push_back(tdCurrErr);
	}
	///*
	ofstream Output;
	stringstream OutputStringStream;
	OutputStringStream << "InitialDeterminedValues_" << CurrentOffsetString << ".txt";
	const string OutputString = OutputStringStream.str();
	const char* OutputName = OutputString.c_str();
	Output.open(OutputName);
	Output<<"Input"<<"\t"<<"Vd /V"<<"\t"<<"VdErr /V"<<"\t"<<"VdEval /V"<<"\t"<<"p1"<<"\t"<<"p2"<<"\t"<<"CGrad1"<<"\t"<<"CGrad1Err"<<"\t"<<"CGrad2"<<"\t"<<"CGrad2Err"<<"\t"<<"I_VdEval /A"<<"\t"<<"I_VdEvalErr /A"<<endl;
	for(int i = 0; i < NFiles; i++){
		Output<<CFiles[i]<<"\t"<<Vd[i]<<"\t"<<VdErr[i]<<"\t"<<VdEval[i]<<"\t"<<p1[i]<<"\t"<<p2[i]<<"\t"<<CGrad1[i]<<"\t"<<CGrad1Err[i]<<"\t"<<CGrad2[i]<<"\t"<<CGrad2Err[i]<<"\t"<<I_VdEval[i]<<"\t"<<I_VdEvalErr[i]<<endl;
	}
	Output.close();
	
	
	ofstream IrradOutput;
	stringstream IrradOutputStringStream;
	IrradOutputStringStream << "IrradDeterminedValues_" << CurrentOffsetString << ".txt";
	const string IrradOutputString = IrradOutputStringStream.str();
	const char* IrradOutputName = IrradOutputString.c_str();
	IrradOutput.open(IrradOutputName);
	IrradOutput<<"Input"<<"\t"<<"Vd /V"<<"\t"<<"VdErr /V"<<"\t"<<"VdEval /V"<<"\t"<<"p1"<<"\t"<<"p2"<<"\t"<<"CGrad1"<<"\t"<<"CGrad1Err"<<"\t"<<"CGrad2"<<"\t"<<"CGrad2Err"<<"\t"<<"I_VdEval /A"<<"\t"<<"I_VdEvalErr /A"<<endl;
	for(int i = 0; i < NFiles; i++){
		IrradOutput<<IrradCFiles[i]<<"\t"<<IrradVd[i]<<"\t"<<IrradVdErr[i]<<"\t"<<IrradVdEval[i]<<"\t"<<Irradp1[i]<<"\t"<<Irradp2[i]<<"\t"<<IrradCGrad1[i]<<"\t"<<IrradCGrad1Err[i]<<"\t"<<IrradCGrad2[i]<<"\t"<<IrradCGrad2Err[i]<<"\t"<<IrradI_VdEval[i]<<"\t"<<IrradI_VdEvalErr[i]<<endl;
	}
	IrradOutput.close();
	//*/
	
	double alpha, alphaErr, kappa, kappaErr;
	
	TCanvas * dICanvas = new TCanvas("dICanvas","Delta I vs. Flux",600,600);
	dICanvas->SetGrid();
	dICanvas->SetLeftMargin(0.15);
	dICanvas->SetBottomMargin(0.15);
	
	TGraphErrors * dIGraph = new TGraphErrors(NFiles,&Flux[0],&dCurr[0],&FluxErr[0],&dCurrErr[0]);
	//TGraphErrors * dIGraph = new TGraphErrors(NFiles,&Flux[0],&dCurr[0],0,0);
	dIGraph->SetMarkerStyle(20);
	dIGraph->SetMarkerColor(1);
	dIGraph->SetLineColor(1);
	dIGraph->SetTitle("Delta I vs. Flux");
	dIGraph->GetXaxis()->SetTitle("Flux /pcm^{2}");
	dIGraph->GetYaxis()->SetTitle("Delta I /A");
	dIGraph->GetXaxis()->SetTitleOffset(1.5);
	dIGraph->GetYaxis()->SetTitleOffset(1.5);
	
	double MaxFlux = *max_element(Flux.begin(), Flux.end());
	double MinFlux = *min_element(Flux.begin(), Flux.end());
	
	TF1 * dIFit = new TF1("dIFit", "pol1", MinFlux, MaxFlux);
	
	dIFit->FixParameter(0,0);
	//dIFit->SetParameter(0,3.6E-9);
	dIFit->SetParameter(1,1.3E-19);
	
	dIGraph->Fit("dIFit", "R Q N");
	dIFit->SetRange(MinFlux, MaxFlux);
	dIFit->SetLineColor(2);
	
	/*
	//Covariance info necessary if not forced to be zero intercept
	TVirtualFitter * dIFitter = TVirtualFitter::GetFitter();
	TMatrixD dICovariance(2,2,dIFitter->GetCovarianceMatrix());
	double dIkErrSquare = dIFitter->GetCovarianceMatrixElement(0,0);
	double dImErrSquare = dIFitter->GetCovarianceMatrixElement(1,1);
	double dIcov = dIFitter->GetCovarianceMatrixElement(0,1);
	*/
	
	double dIk = dIFit->GetParameter(0);
	double dIm = dIFit->GetParameter(1);
	
	double dIkErr = dIFit->GetParError(0);
	double dImErr = dIFit->GetParError(1);
	
	//double dIp = dIcov/(dIkErr*dImErr);
	
	
	//Dimensions in cm
	double width = 0.03;
	double length = 0.265;
	double volume = width*length*length;
	
	alpha = dIm/volume;
	alphaErr = dImErr/volume;
	
	double alpha_neq = 3.99e-17;
	double alpha_neqErr = 0.03e-17;
	
	double alphaPartial = 1/alpha_neq;
	double alpha_neqPartial = -alpha/(alpha_neq*alpha_neq);
	
	
	kappa = alpha/alpha_neq;
	kappaErr = sqrt(alphaErr*alphaErr*alphaPartial*alphaPartial + alpha_neqErr*alpha_neqErr*alpha_neqPartial*alpha_neqPartial); //+ 2*dIcov*alphaPartial*alpha_neqPartial not right, covaraince between m and k, not these two
	
	//dICanvas->SetLogx();
	//dICanvas->SetLogy();
	dIGraph->Draw("AP");
	dIFit->Draw("SAME");
	///*
	stringstream DeltaI_vs_FluxStringStream;
	DeltaI_vs_FluxStringStream << "DeltaI_vs_Flux_" << CurrentOffsetString << ".pdf";
	const string DeltaI_vs_FluxString = DeltaI_vs_FluxStringStream.str();
	const char* DeltaI_vs_FluxName = DeltaI_vs_FluxString.c_str();
	
	dICanvas->Print(DeltaI_vs_FluxName);
	
	ofstream Hardness;
	stringstream HardnessStringStream;
	HardnessStringStream << "HardnessValues_" << CurrentOffsetString << ".txt";
	const string HardnessString = HardnessStringStream.str();
	const char* HardnessName = HardnessString.c_str();
	Hardness.open(HardnessName);
	Hardness<<"Current related damage factor "<<alpha<<" +/- "<<alphaErr<<endl;
	Hardness<<"Hardness factor "<<kappa<<" +/- "<<kappaErr<<endl;
	//Hardness<<"p "<<dIp<<endl;
	Hardness.close();
	//*/
	
	Grad.push_back(dIm);
	GradErr.push_back(dImErr);
	Alpha.push_back(alpha);
	AlphaErr.push_back(alphaErr);
	Kappa.push_back(kappa);
	KappaErr.push_back(kappaErr);
	
	
	
	//Clearing initialised vectors for offset looping
	p1.clear();
	p2.clear();
	LnVd.clear();
	LnVdErr.clear();
	Vd.clear();
	VdErr.clear();
	VdEval.clear();
	I_VdEval.clear();
	I_VdEvalErr.clear();
	
	Irradp1.clear();
	Irradp2.clear();
	IrradLnVd.clear();
	IrradLnVdErr.clear();
	IrradVd.clear();
	IrradVdErr.clear();
	IrradVdEval.clear();
	IrradI_VdEval.clear();
	IrradI_VdEvalErr.clear();
	
	dCurr.clear();
	dCurrErr.clear();
	}
	
	
	TCanvas * EvalGradCanvas = new TCanvas("EvalGradCanvas","Gradient vs. Evaluation Offset",600,600);
	EvalGradCanvas->SetGrid();
	EvalGradCanvas->SetLeftMargin(0.15);
	EvalGradCanvas->SetBottomMargin(0.15);
	
	TGraphErrors * EvalGradGraph = new TGraphErrors(NOffsets,&VdOffset[0],&Grad[0],0,&GradErr[0]);
	EvalGradGraph->SetMarkerStyle(20);
	EvalGradGraph->SetMarkerColor(1);
	EvalGradGraph->SetLineColor(1);
	EvalGradGraph->SetTitle("Gradient vs. Evaluation Offset");
	EvalGradGraph->GetXaxis()->SetTitle("Evaluation Offset /V");
	EvalGradGraph->GetYaxis()->SetTitle("Gradient");
	EvalGradGraph->GetXaxis()->SetTitleOffset(1.5);
	EvalGradGraph->GetYaxis()->SetTitleOffset(1.5);
	
	double MaxOffset = *max_element(VdOffset.begin(), VdOffset.end());
	double MinOffset = *min_element(VdOffset.begin(), VdOffset.end());
	
	EvalGradGraph->Draw("AC");
	EvalGradGraph->GetXaxis()->SetRangeUser(MinOffset, MaxOffset);
	EvalGradGraph->Draw("AC");
	EvalGradCanvas->Update();
	
	EvalGradCanvas->Print("EvaluationVoltageGrad.pdf");
	
	
	
	TCanvas * EvalAlphaCanvas = new TCanvas("EvalAlphaCanvas","Alpha vs. Evaluation Offset",600,600);
	EvalAlphaCanvas->SetGrid();
	EvalAlphaCanvas->SetLeftMargin(0.15);
	EvalAlphaCanvas->SetBottomMargin(0.15);
	
	TGraphErrors * EvalAlphaGraph = new TGraphErrors(NOffsets,&VdOffset[0],&Alpha[0],0,&AlphaErr[0]);
	EvalAlphaGraph->SetMarkerStyle(20);
	EvalAlphaGraph->SetMarkerColor(1);
	EvalAlphaGraph->SetLineColor(1);
	EvalAlphaGraph->SetTitle("Alpha vs. Evaluation Offset");
	EvalAlphaGraph->GetXaxis()->SetTitle("Evaluation Offset /V");
	EvalAlphaGraph->GetYaxis()->SetTitle("Alpha");
	EvalAlphaGraph->GetXaxis()->SetTitleOffset(1.5);
	EvalAlphaGraph->GetYaxis()->SetTitleOffset(1.5);
	
	EvalAlphaGraph->Draw("AC");
	EvalAlphaGraph->GetXaxis()->SetRangeUser(MinOffset, MaxOffset);
	EvalAlphaGraph->Draw("AC");
	EvalAlphaCanvas->Update();
	
	EvalAlphaCanvas->Print("EvaluationVoltageAlpha.pdf");
	
	
	
	TCanvas * EvalKappaCanvas = new TCanvas("EvalKappaCanvas","Hardness vs. Evaluation Offset",600,600);
	EvalKappaCanvas->SetGrid();
	EvalKappaCanvas->SetLeftMargin(0.15);
	EvalKappaCanvas->SetBottomMargin(0.15);
	
	TGraphErrors * EvalKappaGraph = new TGraphErrors(NOffsets,&VdOffset[0],&Kappa[0],0,&KappaErr[0]);
	EvalKappaGraph->SetMarkerStyle(20);
	EvalKappaGraph->SetMarkerColor(1);
	EvalKappaGraph->SetLineColor(1);
	EvalKappaGraph->SetTitle("Hardness vs. Evaluation Offset");
	EvalKappaGraph->GetXaxis()->SetTitle("Evaluation Offset /V");
	EvalKappaGraph->GetYaxis()->SetTitle("Hardness");
	EvalKappaGraph->GetXaxis()->SetTitleOffset(1.5);
	EvalKappaGraph->GetYaxis()->SetTitleOffset(1.5);
	
	EvalKappaGraph->Draw("AC");
	EvalKappaGraph->GetXaxis()->SetRangeUser(MinOffset, MaxOffset);
	EvalKappaGraph->Draw("AC");
	EvalKappaCanvas->Update();
	
	EvalKappaCanvas->Print("EvaluationVoltageKappa.pdf");
	
	
	
	
	ofstream Evaluation;
	Evaluation.open("EvaluationVoltageValues.txt");
	Evaluation<<"VdOffset /V"<<"\t"<<"Grad"<<"\t"<<"GradErr"<<"\t"<<"Alpha"<<"\t"<<"AlphaErr"<<"\t"<<"Kappa"<<"\t"<<"KappaErr"<<endl;
	for(int i = 0; i < NOffsets; i++){
		Evaluation<<VdOffset[i]<<"\t"<<Grad[i]<<"\t"<<GradErr[i]<<"\t"<<Alpha[i]<<"\t"<<AlphaErr[i]<<"\t"<<Kappa[i]<<"\t"<<KappaErr[i]<<endl;
	}
	Evaluation.close();
	
	
	
}
