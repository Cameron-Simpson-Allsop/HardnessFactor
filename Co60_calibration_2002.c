void Co60_calibration_2002()
{
	
	ifstream file;
	file.open("Co60_calibration_2002.txt");
	

double c = 0.;
double ec = 0.;
double n = 0.;
double ctot = 0.;
double ectotsquared = 0.;
double ectot = 0.;	

while(!file.eof())
{
    	double Pos2, Pos1, ePos2, ePos1;
	file >> Pos2 >> Pos1 >> ePos2 >> ePos1;

	c = Pos1/Pos2;
	ec = pow(pow(ePos1/Pos2,2) + pow(Pos1/pow(Pos2,2),2)*ePos2,0.5);
	n = n + 1.;
	ctot = ctot + c;
	ectotsquared = pow(ec,2) + ectotsquared;
	ectot = pow(ectotsquared,0.5);

	std::cout << "Calibration Factor " << n << " = " << c << " +/- " << ec << std::endl; 
	
}
	
	std::cout << "========================================" << std::endl;
	std::cout << "Calibration Factor Average = " << ctot/n << " +/- " << ectot/n << std::endl;
	std::cout << "========================================" << std::endl; 

	TGraphErrors *Co = new TGraphErrors("Co60_calibration_2002.txt");
		Co->GetXaxis()->SetTitle("Counts at Position 1 - Counter");
		Co->GetYaxis()->SetTitle("Counts at Position 2 - Calibrated");
		Co->SetTitle("Co60 calibration test 20/02");
		Co->SetMarkerStyle(3);		
	
	TF1* fit = new TF1("fit1","pol1", 400, 550);
	
	TCanvas *canvas = new TCanvas("canvas","canvas",600,700);
		Co->Draw("AP");
		Co->Fit(fit,"RN");
		fit->Draw("same");

	double c1 = fit->GetParameter(1);
	double ec1 = fit->GetParError(1);

	std::cout << "Gradient of Fit = " << c1 << " +/- " << ec1 << std::endl;

}
