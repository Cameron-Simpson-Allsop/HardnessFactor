#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

struct CurrentWarmSetB{ 
	float mean = 0;
	float error = 0;
	float fluence = 0;
	float fluence_error = 0;
	float voltage = 0;
};

struct CurrentWarmSetA{ 
	float mean = 0;
	float error = 0;
	float fluence = 0;
	float fluence_error = 0;
	float voltage = 0;
};

struct CurrentColdSetB{ 
	float mean = 0;
	float error = 0;
	float fluence = 0;
	float fluence_error = 0;
	float voltage = 0;
};

struct CurrentColdSetA{ 
	float mean = 0;
	float error = 0;
	float fluence = 0;
	float fluence_error = 0;
	float voltage = 0;
};

double ExtractNonIrradiatedCurrent_Inon(TString txtName="", TString graphTitle ="", double voltage = -91.)
{
	TGraphErrors *g1 = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	TF1* fit1 = new TF1("fit1","pol1", -110,-40); //Fits 1st order poly within range
	g1->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);
	double Inon = abs(p1g*voltage+p0g);
	std::cout << "Inon = " << Inon << std::endl;

	return Inon;
}

double ExtractNonIrradiatedCurrent_Inonerror(TString txtName="", TString graphTitle ="", double voltage = -91.)
{
	TGraphErrors *g1 = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g1->GetXaxis()->SetTitle("Voltage(V)");
	g1->GetYaxis()->SetTitle("Leakage Current (nA)");
	g1->GetYaxis()->SetTitleOffset(1.45);
	g1->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -110,-40); //Fits 1st order poly within range
	g1->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	/*TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g1->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.*/

	double Inonerror = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	std::cout << "Inonerror = " << Inonerror << std::endl;

	return Inonerror;
}

CurrentWarmSetB ExtractIrradiatedCurrentWB(TString txtName="", TString graphTitle="", double voltage = -91.)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -100,-75); //Fits 1st order poly within range
	g->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	/*TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.*/

	CurrentWarmSetB I; //Calculate variables within the 'Current' structure.
	I.mean = abs(p1g*voltage+p0g);
	I.error = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	I.voltage = voltage;

	std::cout << p0g << "+/-" << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
}

CurrentWarmSetA ExtractIrradiatedCurrentWA(TString txtName="", TString graphTitle="", double voltage = -91.)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -100,-75); //Fits 1st order poly within range
	g->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	/*TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.*/

	CurrentWarmSetA I; //Calculate variables within the 'Current' structure.
	I.mean = abs(p1g*voltage+p0g);
	I.error = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	I.voltage = voltage;

	std::cout << p0g << "+/-" << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
}

CurrentColdSetB ExtractIrradiatedCurrentCB(TString txtName="", TString graphTitle="", double voltage = -91.)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -100,-75); //Fits 1st order poly within range
	g->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	/*TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.*/

	CurrentColdSetB I; //Calculate variables within the 'Current' structure.
	I.mean = abs(p1g*voltage+p0g);
	I.error = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	I.voltage = voltage;

	std::cout << p0g << "+/-" << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
}

CurrentColdSetA ExtractIrradiatedCurrentCA(TString txtName="", TString graphTitle="", double voltage = -91.)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -100,-75); //Fits 1st order poly within range
	g->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	/*TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.*/

	CurrentColdSetA I; //Calculate variables within the 'Current' structure.
	I.mean = abs(p1g*voltage+p0g);
	I.error = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	I.voltage = voltage;

	std::cout << p0g << "+/-" << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
}

void PlotDiode(std::vector<CurrentWarmSetB> Currents)
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
		for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
		{
			x.push_back(Currents[i].fluence); //Puts variable x into vector.
			ex.push_back(Currents[i].fluence_error); //Same but errors.
		
			y.push_back(Currents[i].mean); 
			ey.push_back(Currents[i].error);

		}

	TF1* fit1 = new TF1("fit1","pol1", 0,5.5e12);
	fit1->SetParameter(1,5e-11);
	TCanvas *Fluence = new TCanvas("FluenceWB","FluenceWB",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlack);
		g5->SetMarkerStyle(20);
		g5->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->SetTitle("");
		g5->Fit(fit1,"RN");
		fit1->SetLineColor(kBlack);
		
		TGaxis::SetMaxDigits(3);
		
		g5->Draw("AP");
		fit1->Draw("same");

	double l = 0.256; //p cm^2
	double w = 0.03; //cm

	double theta = fit1->GetParameter(1); //nA cm^2 
	double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1

	double etheta = fit1->GetParError(1);
	double ealpha = pow(10,-9)*etheta/(l*l*w);

	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double k = alpha/alphan;
	double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

	//std::cout << "alpha (warm set B) = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "hardness factor (warm set B) = " << k << " +/- " << ek << std::endl; 		
}

void PlotDiode(std::vector<CurrentWarmSetA> Currents)
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
		for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
		{
			x.push_back(Currents[i].fluence); //Puts variable x into vector.
			ex.push_back(Currents[i].fluence_error); //Same but errors.
		
			y.push_back(Currents[i].mean); 
			ey.push_back(Currents[i].error);

		}

	TF1* fit1 = new TF1("fit1","pol1", 0,5.5e12);
	fit1->SetParameter(1,5e-11);
	TCanvas *Fluence = new TCanvas("FluenceWA","FluenceWA",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlack);
		g5->SetMarkerStyle(20);
		g5->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->SetTitle("");
		g5->Fit(fit1,"RN");
		fit1->SetLineColor(kBlack);
		
		TGaxis::SetMaxDigits(2);

		g5->Draw("AP");
		fit1->Draw("same");

	double l = 0.256; //p cm^2
	double w = 0.03; //cm

	double theta = fit1->GetParameter(1); //nA cm^2 
	double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1

	double etheta = fit1->GetParError(1);
	double ealpha = pow(10,-9)*etheta/(l*l*w);

	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double k = alpha/alphan;
	double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

	//std::cout << "alpha (warm set A) = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "hardness factor (warm set A) = " << k << " +/- " << ek << std::endl; 		
}

void PlotDiode(std::vector<CurrentColdSetB> Currents)
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
		for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
		{
			x.push_back(Currents[i].fluence); //Puts variable x into vector.
			ex.push_back(Currents[i].fluence_error); //Same but errors.
		
			y.push_back(Currents[i].mean); 
			ey.push_back(Currents[i].error);

		}

	TF1* fit1 = new TF1("fit1","pol1", 0,5.5e12);
	fit1->SetParameter(1,5e-11);
	TCanvas *Fluence = new TCanvas("FluenceCB","FluenceCB",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlack);
		g5->SetMarkerStyle(20);
		g5->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->SetTitle("");
		g5->Fit(fit1,"RN");
		fit1->SetLineColor(kBlack);
		
		TGaxis::SetMaxDigits(3);

		g5->Draw("AP");
		fit1->Draw("same");

	double l = 0.256; //p cm^2
	double w = 0.03; //cm

	double theta = fit1->GetParameter(1); //nA cm^2 
	double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1

	double etheta = fit1->GetParError(1);
	double ealpha = pow(10,-9)*etheta/(l*l*w);

	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double k = alpha/alphan;
	double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

	//std::cout << "alpha (cold set B) = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "hardness factor (cold set B) = " << k << " +/- " << ek << std::endl; 		
}

void PlotDiode(std::vector<CurrentColdSetA> Currents)
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
		for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
		{
			x.push_back(Currents[i].fluence); //Puts variable x into vector.
			ex.push_back(Currents[i].fluence_error); //Same but errors.
		
			y.push_back(Currents[i].mean); 
			ey.push_back(Currents[i].error);

		}

	TF1* fit1 = new TF1("fit1","pol1", 0,5.5e12);
	fit1->SetParameter(1,5e-11);
	TCanvas *Fluence = new TCanvas("FluenceCA","FluenceCA",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlack);
		g5->SetMarkerStyle(20);
		g5->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->SetTitle("");
		g5->Fit(fit1,"RN");
		fit1->SetLineColor(kBlack);
		
		TGaxis::SetMaxDigits(2);

		g5->Draw("AP");
		fit1->Draw("same");

	double l = 0.256; //p cm^2
	double w = 0.03; //cm

	double theta = fit1->GetParameter(1); //nA cm^2 
	double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1

	double etheta = fit1->GetParError(1);
	double ealpha = pow(10,-9)*etheta/(l*l*w);

	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double k = alpha/alphan;
	double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

	//std::cout << "alpha (cold set A) = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "hardness factor (cold set A) = " << k << " +/- " << ek << std::endl; 		
}

void EvaluateDiodes() //Function to define relevant files and corresponging parameters.
{
	std::cout << "=================================================================" << std::endl;
	std::vector<CurrentWarmSetB> IsWB;
	std::vector<CurrentWarmSetA> IsWA;
	std::vector<CurrentColdSetB> IsCB;
	std::vector<CurrentColdSetA> IsCA;	

	double c = 112.67;
	double error_c = 0.55238 + 5.358;
	double sys_fluence_error = 0.134;

	//Warm Set B

	CurrentWarmSetB Ia = ExtractIrradiatedCurrentWB("Diode26_IV_irradiated_0603.txt","Diode 26 irradiated"); 
	Double_t Inon = ExtractNonIrradiatedCurrent_Inon("Diode26_IV_2602.txt","Diode 26 non-irradiated");
	Double_t Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode26_IV_2602.txt","Diode 26 non-irradiated");	
	Ia.mean = Ia.mean - Inon;
	Ia.error = pow(Ia.error*Ia.error + Inonerror*Inonerror,0.5);
	Ia.fluence = 6.52E+13/c;
	Ia.fluence_error = pow(pow(4.30E+12/c,2.)+pow((Ia.fluence*error_c)/(c*c),2.) + pow(Ia.fluence*sys_fluence_error,2.),0.5);
	IsWB.push_back(Ia);

	CurrentWarmSetB Ib = ExtractIrradiatedCurrentWB("Diode28_IV_irradiated_0603.txt","Diode 28 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode28_IV_2602.txt","Diode 28 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode28_IV_2602.txt","Diode 28 non-irradiated");	
	Ib.mean = Ib.mean - Inon;
	Ib.error = pow(Ib.error*Ib.error + Inonerror*Inonerror,0.5);
	Ib.fluence = 1.87E+14/c;
	Ib.fluence_error = pow(pow(5.00E+12/c,2.)+pow((Ib.fluence*error_c)/(c*c),2.) + pow(Ib.fluence*sys_fluence_error,2.),0.5);
	IsWB.push_back(Ib); 

	CurrentWarmSetB Ic = ExtractIrradiatedCurrentWB("Diode30_IV_irradiated_0603.txt","Diode 30 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode30_IV_2602.txt","Diode 30 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode30_IV_2602.txt","Diode 30 non-irradiated");	
	Ic.mean = Ic.mean - Inon;
	Ic.error = pow(Ic.error*Ic.error + Inonerror*Inonerror,0.5);
	Ic.fluence = 2.92e14/c;
	Ic.fluence_error = pow(pow(0.09e14/c,2.)+pow((Ic.fluence*error_c)/(c*c),2.) + pow(Ic.fluence*sys_fluence_error,2.),0.5);
	IsWB.push_back(Ic); 

	CurrentWarmSetB Id = ExtractIrradiatedCurrentWB("Diode32_IV_irradiated_0603.txt","Diode 32 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode32_IV_2602.txt","Diode 32 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode32_IV_2602.txt","Diode 32 non-irradiated");	
	Id.mean = Id.mean - Inon;
	Id.error = pow(Id.error*Id.error + Inonerror*Inonerror,0.5);
	Id.fluence = 3.61e14/c;
	Id.fluence_error = pow(pow(0.11e14/c,2.)+pow((Id.fluence*error_c)/(c*c),2.) + pow(Id.fluence*sys_fluence_error,2.),0.5);
	IsWB.push_back(Id); 

	CurrentWarmSetB Ie = ExtractIrradiatedCurrentWB("Diode34_IV_irradiated_0603.txt","Diode 34 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode34_IV_2602.txt","Diode 34 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode34_IV_2602.txt","Diode 34 non-irradiated");	
	Ie.mean = Ie.mean - Inon;
	Ie.error = pow(Ie.error*Ie.error + Inonerror*Inonerror,0.5);
	Ie.fluence = 5.34e14/c;
	Ie.fluence_error = pow(pow(0.12e14/c,2.)+pow((Ie.fluence*error_c)/(c*c),2.) + pow(Ie.fluence*sys_fluence_error,2.),0.5);
	IsWB.push_back(Ie);

	CurrentWarmSetB If = ExtractIrradiatedCurrentWB("Diode36_IV_irradiated_0603.txt","Diode 36 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode36_IV_2602.txt","Diode 36 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode36_IV_2602.txt","Diode 36 non-irradiated");	
	If.mean = If.mean - Inon;
	If.error = pow(If.error*If.error + Inonerror*Inonerror,0.5);
	If.fluence = 3.82e14/c;
	If.fluence_error = pow(pow(0.13e14/c,2.)+pow((If.fluence*error_c)/(c*c),2.) + pow(If.fluence*sys_fluence_error,2.),0.5);
	IsWB.push_back(If);   
	
	//Warm Set A

	CurrentWarmSetA Ig = ExtractIrradiatedCurrentWA("Diode25_IV_irradiated_0603.txt","Diode 25 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode25_IV_2602.txt","Diode 25 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode25_IV_2602.txt","Diode 25 non-irradiated");	
	Ig.mean = Ig.mean - Inon;
	Ig.error = pow(Ig.error*Ig.error + Inonerror*Inonerror,0.5);
	Ig.fluence = 6.52E+13/c;
	Ig.fluence_error = pow(pow(4.30E+12/c,2.)+pow((Ig.fluence*error_c)/(c*c),2.) + pow(Ig.fluence*sys_fluence_error,2.),0.5);
	IsWA.push_back(Ig);

	CurrentWarmSetA Ih = ExtractIrradiatedCurrentWA("Diode27_IV_irradiated_0603.txt","Diode 27 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode27_IV_2602.txt","Diode 27 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode27_IV_2602.txt","Diode 27 non-irradiated");	
	Ih.mean = Ih.mean - Inon;
	Ih.error = pow(Ih.error*Ih.error + Inonerror*Inonerror,0.5);
	Ih.fluence = 1.87E+14/c;
	Ih.fluence_error = pow(pow(5.00E+12/c,2.)+pow((Ih.fluence*error_c)/(c*c),2.) + pow(Ih.fluence*sys_fluence_error,2.),0.5);
	IsWA.push_back(Ih); 

	CurrentWarmSetA Ii = ExtractIrradiatedCurrentWA("Diode29_IV_irradiated_0603.txt","Diode 29 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode29_IV_2602.txt","Diode 29 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode29_IV_2602.txt","Diode 29 non-irradiated");	
	Ii.mean = Ii.mean - Inon;
	Ii.error = pow(Ii.error*Ii.error + Inonerror*Inonerror,0.5);
	Ii.fluence = 2.92e14/c;
	Ii.fluence_error = pow(pow(0.09e14/c,2.)+pow((Ii.fluence*error_c)/(c*c),2.) + pow(Ii.fluence*sys_fluence_error,2.),0.5);
	IsWA.push_back(Ii); 

	CurrentWarmSetA Ij = ExtractIrradiatedCurrentWA("Diode31_IV_irradiated_0603.txt","Diode 31 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode31_IV_2602.txt","Diode 31 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode31_IV_2602.txt","Diode 31 non-irradiated");	
	Ij.mean = Ij.mean - Inon;
	Ij.error = pow(Ij.error*Ij.error + Inonerror*Inonerror,0.5);
	Ij.fluence = 3.61e14/c;
	Ij.fluence_error = pow(pow(0.11e14/c,2.)+pow((Ij.fluence*error_c)/(c*c),2.) + pow(Ij.fluence*sys_fluence_error,2.),0.5);
	IsWA.push_back(Ij); 

	CurrentWarmSetA Ik = ExtractIrradiatedCurrentWA("Diode33_IV_irradiated_0603.txt","Diode 33 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode33_IV_2602.txt","Diode 34 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode33_IV_2602.txt","Diode 33 non-irradiated");	
	Ik.mean = Ik.mean - Inon;
	Ik.error = pow(Ik.error*Ik.error + Inonerror*Inonerror,0.5);
	Ik.fluence = 5.34e14/c;
	Ik.fluence_error = pow(pow(0.12e14/c,2.)+pow((Ik.fluence*error_c)/(c*c),2.) + pow(Ik.fluence*sys_fluence_error,2.),0.5);
	IsWA.push_back(Ik);

	CurrentWarmSetA Il = ExtractIrradiatedCurrentWA("Diode35_IV_irradiated_0603.txt","Diode 35 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode35_IV_2602.txt","Diode 35 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode35_IV_2602.txt","Diode 35 non-irradiated");	
	Il.mean = Il.mean - Inon;
	Il.error = pow(Il.error*Il.error + Inonerror*Inonerror,0.5);
	Il.fluence = 3.82e14/c;
	Il.fluence_error = pow(pow(0.13e14/c,2.)+pow((Il.fluence*error_c)/(c*c),2.) + pow(Il.fluence*sys_fluence_error,2.),0.5);
	IsWA.push_back(Il);

	//Cold Set B

	//Omitted stupid high fluence
	/*CurrentColdSetB Im = ExtractIrradiatedCurrentCB("Diode38_IV_irradiated_0603.txt","Diode 38 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode38_IV_2602.txt","Diode 38 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode38_IV_2602.txt","Diode 38 non-irradiated");	
	Im.mean = Im.mean - Inon;
	Im.error = pow(Im.error*Im.error + Inonerror*Inonerror,0.5);
	Im.fluence = 1.58e15/c;
	Im.fluence_error = pow(pow(0.02e15/c,2.)+pow((Im.fluence*error_c)/(c*c),2.) + pow(Im.fluence*sys_fluence_error,2.),0.5);
	IsCB.push_back(Im);*/

	CurrentColdSetB In = ExtractIrradiatedCurrentCB("Diode40_IV_irradiated_0603.txt","Diode 40 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode40_IV_2802.txt","Diode 40 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode40_IV_2802.txt","Diode 40 non-irradiated");	
	In.mean = In.mean - Inon;
	In.error = pow(In.error*Ih.error + Inonerror*Inonerror,0.5);
	In.fluence = 2.81E+14/c;
	In.fluence_error = pow(pow(0.08E+14/c,2.)+pow((In.fluence*error_c)/(c*c),2.) + pow(In.fluence*sys_fluence_error,2.),0.5);
	IsCB.push_back(In); 

	CurrentColdSetB Io = ExtractIrradiatedCurrentCB("Diode42_IV_irradiated_0603.txt","Diode 42 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode42_IV_2802.txt","Diode 42 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode42_IV_2802.txt","Diode 42 non-irradiated");	
	Io.mean = Io.mean - Inon;
	Io.error = pow(Io.error*Io.error + Inonerror*Inonerror,0.5);
	Io.fluence = 7.51e13/c;
	Io.fluence_error = pow(pow(0.41e13/c,2.)+pow((Io.fluence*error_c)/(c*c),2.) + pow(Io.fluence*sys_fluence_error,2.),0.5);
	IsCB.push_back(Io); 

	CurrentColdSetB Ip = ExtractIrradiatedCurrentCB("Diode44_IV_irradiated_0603.txt","Diode 44 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode44_IV_2802.txt","Diode 44 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode44_IV_2802.txt","Diode 44 non-irradiated");	
	Ip.mean = Ip.mean - Inon;
	Ip.error = pow(Ip.error*Ip.error + Inonerror*Inonerror,0.5);
	Ip.fluence = 1.13e14/c;
	Ip.fluence_error = pow(pow(0.04e14/c,2.)+pow((Ip.fluence*error_c)/(c*c),2.) + pow(Ip.fluence*sys_fluence_error,2.),0.5);
	IsCB.push_back(Ip); 

	CurrentColdSetB Iq = ExtractIrradiatedCurrentCB("Diode46_IV_irradiated_0603.txt","Diode 46 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode46_IV_2802.txt","Diode 46 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode46_IV_2802.txt","Diode 46 non-irradiated");	
	Iq.mean = Iq.mean - Inon;
	Iq.error = pow(Iq.error*Iq.error + Inonerror*Inonerror,0.5);
	Iq.fluence = 4.88e13/c;
	Iq.fluence_error = pow(pow(0.36e13/c,2.)+pow((Iq.fluence*error_c)/(c*c),2.) + pow(Iq.fluence*sys_fluence_error,2.),0.5);
	IsCB.push_back(Iq);

	CurrentColdSetB Ir = ExtractIrradiatedCurrentCB("Diode46_IV_irradiated_0603.txt","Diode 46 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode46_IV_2802.txt","Diode 46 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode46_IV_2802.txt","Diode 46 non-irradiated");	
	Ir.mean = Ir.mean - Inon;
	Ir.error = pow(Ir.error*Ir.error + Inonerror*Inonerror,0.5);
	Ir.fluence = 1.76e13/c;
	Ir.fluence_error = pow(pow(0.27e13/c,2.)+pow((Ir.fluence*error_c)/(c*c),2.) + pow(Ir.fluence*sys_fluence_error,2.),0.5);
	IsCB.push_back(Ir);

	//Cold Set A	
	
	//Omitted stupid high fluence
	/*CurrentColdSetA IS = ExtractIrradiatedCurrentCA("Diode37_IV_irradiated_0603.txt","Diode 37 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode37_IV_2602.txt","Diode 37 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode37_IV_2602.txt","Diode 37 non-irradiated");	
	IS.mean = IS.mean - Inon;
	IS.error = pow(IS.error*IS.error + Inonerror*Inonerror,0.5);
	IS.fluence = 1.58e15/c;
	IS.fluence_error = pow(pow(0.02e15/c,2.)+pow((IS.fluence*error_c)/(c*c),2.) + pow(IS.fluence*sys_fluence_error,2.),0.5);
	IsCA.push_back(IS);*/

	CurrentColdSetA It = ExtractIrradiatedCurrentCA("Diode39_IV_irradiated_0603.txt","Diode 39 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode39_IV_2602.txt","Diode 39 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode39_IV_2602.txt","Diode 39 non-irradiated");	
	It.mean = It.mean - Inon;
	It.error = pow(It.error*It.error + Inonerror*Inonerror,0.5);
	It.fluence = 2.81E+14/c;
	It.fluence_error = pow(pow(0.08E+14/c,2.)+pow((It.fluence*error_c)/(c*c),2.) + pow(It.fluence*sys_fluence_error,2.),0.5);
	IsCA.push_back(It); 

	CurrentColdSetA Iu = ExtractIrradiatedCurrentCA("Diode41_IV_irradiated_0603.txt","Diode 41 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode41_IV_2802.txt","Diode 41 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode41_IV_2802.txt","Diode 41 non-irradiated");	
	Iu.mean = Iu.mean - Inon;
	Iu.error = pow(Iu.error*Iu.error + Inonerror*Inonerror,0.5);
	Iu.fluence = 7.51e13/c;
	Iu.fluence_error = pow(pow(0.41e13/c,2.)+pow((Iu.fluence*error_c)/(c*c),2.) + pow(Iu.fluence*sys_fluence_error,2.),0.5);
	IsCA.push_back(Iu); 

	CurrentColdSetA Iv = ExtractIrradiatedCurrentCA("Diode43_IV_irradiated_0603.txt","Diode 43 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode43_IV_2802.txt","Diode 43 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode43_IV_2802.txt","Diode 43 non-irradiated");	
	Iv.mean = Iv.mean - Inon;
	Iv.error = pow(Iv.error*Iv.error + Inonerror*Inonerror,0.5);
	Iv.fluence = 1.13e14/c;
	Iv.fluence_error = pow(pow(0.04e14/c,2.)+pow((Iv.fluence*error_c)/(c*c),2.) + pow(Iv.fluence*sys_fluence_error,2.),0.5);
	IsCA.push_back(Iv); 

	CurrentColdSetA Iw = ExtractIrradiatedCurrentCA("Diode41_IV_irradiated_0603.txt","Diode 41 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode41_IV_2802.txt","Diode 41 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode41_IV_2802.txt","Diode 41 non-irradiated");	
	Iw.mean = Iw.mean - Inon;
	Iw.error = pow(Iw.error*Iw.error + Inonerror*Inonerror,0.5);
	Iw.fluence = 4.88e13/c;
	Iw.fluence_error = pow(pow(0.36e13/c,2.)+pow((Iw.fluence*error_c)/(c*c),2.) + pow(Iw.fluence*sys_fluence_error,2.),0.5);
	IsCA.push_back(Iw);

	CurrentColdSetA Ix = ExtractIrradiatedCurrentCA("Diode47_IV_irradiated_0603.txt","Diode 47 irradiated"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode47_IV_2802.txt","Diode 47 non-irradiated");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode47_IV_2802.txt","Diode 47 non-irradiated");	
	Ix.mean = Ix.mean - Inon;
	Ix.error = pow(Ix.error*Ix.error + Inonerror*Inonerror,0.5);
	Ix.fluence = 1.76e13/c;
	Ix.fluence_error = pow(pow(0.27e13/c,2.)+pow((Ix.fluence*error_c)/(c*c),2.) + pow(Ix.fluence*sys_fluence_error,2.),0.5);
	IsCA.push_back(Ix);
		
	std::cout << "===============================================================================================" << std::endl;
	std::cout << "|" << "Delta I (nA) \t     Delta I Error (nA) \t    Fluence (pcm^-2) \tFluence Error (pcm^-2)" << "|" << std::endl;
	std::cout << "|" << Ia.mean << "\t\t\t" << Ia.error << "\t\t\t" << Ia.fluence << "\t\t   " << Ia.fluence_error << "|" << std::endl; 
	std::cout << "|" << Ib.mean << "\t\t\t" << Ib.error << "\t\t\t" << Ib.fluence << "\t\t   " << Ib.fluence_error << "|" << std::endl;
	std::cout << "|" << Ic.mean << "\t\t\t" << Ic.error << "\t\t\t" << Ic.fluence << "\t\t   " << Ic.fluence_error << "|" << std::endl;
	std::cout << "|" << Id.mean << "\t\t\t" << Id.error << "\t\t\t" << Id.fluence << "\t\t   " << Id.fluence_error << "|" << std::endl;
	std::cout << "|" << Ie.mean << "\t\t\t" << Ie.error << "\t\t\t" << Ie.fluence << "\t\t   " << Ie.fluence_error << "|" << std::endl;
	std::cout << "|" << If.mean << "\t\t\t" << If.error << "\t\t\t" << If.fluence << "\t\t   " << If.fluence_error << "|" << std::endl;
	std::cout << "|" << Ig.mean << "\t\t\t" << Ig.error << "\t\t\t" << Ig.fluence << "\t\t   " << Ig.fluence_error << "|" << std::endl;
	std::cout << "|" << Ih.mean << "\t\t\t" << Ih.error << "\t\t\t" << Ih.fluence << "\t\t   " << Ih.fluence_error << "|" << std::endl;
	std::cout << "|" << Ii.mean << "\t\t\t" << Ii.error << "\t\t\t" << Ii.fluence << "\t\t   " << Ii.fluence_error << "|" << std::endl;
	std::cout << "|" << Ij.mean << "\t\t\t" << Ij.error << "\t\t\t" << Ij.fluence << "\t\t   " << Ij.fluence_error << "|" << std::endl;
	std::cout << "|" << Ik.mean << "\t\t\t" << Ik.error << "\t\t\t" << Ik.fluence << "\t\t   " << Ik.fluence_error << "|" << std::endl;
	std::cout << "|" << Il.mean << "\t\t\t" << Il.error << "\t\t\t" << Il.fluence << "\t\t   " << Il.fluence_error << "|" << std::endl;
	//std::cout << "|" << Im.mean << "\t\t\t" << Im.error << "\t\t\t" << Im.fluence << "\t\t   " << Im.fluence_error << "|" << std::endl;
	std::cout << "|" << In.mean << "\t\t\t" << In.error << "\t\t\t" << In.fluence << "\t\t   " << In.fluence_error << "|" << std::endl;
	std::cout << "|" << Io.mean << "\t\t\t" << Io.error << "\t\t\t" << Io.fluence << "\t\t   " << Io.fluence_error << "|" << std::endl;
	std::cout << "|" << Ip.mean << "\t\t\t" << Ip.error << "\t\t\t" << Ip.fluence << "\t\t   " << Ip.fluence_error << "|" << std::endl;
	std::cout << "|" << Iq.mean << "\t\t\t" << Iq.error << "\t\t\t" << Iq.fluence << "\t\t   " << Iq.fluence_error << "|" << std::endl;
	std::cout << "|" << Ir.mean << "\t\t\t" << Ir.error << "\t\t\t" << Ir.fluence << "\t\t   " << Ir.fluence_error << "|" << std::endl;
	//std::cout << "|" << IS.mean << "\t\t\t" << IS.error << "\t\t\t" << IS.fluence << "\t\t   " << IS.fluence_error << "|" << std::endl;
	std::cout << "|" << It.mean << "\t\t\t" << It.error << "\t\t\t" << It.fluence << "\t\t   " << It.fluence_error << "|" << std::endl;
	std::cout << "|" << Iu.mean << "\t\t\t" << Iu.error << "\t\t\t" << Iu.fluence << "\t\t   " << Iu.fluence_error << "|" << std::endl;
	std::cout << "|" << Iv.mean << "\t\t\t" << Iv.error << "\t\t\t" << Iv.fluence << "\t\t   " << Iv.fluence_error << "|" << std::endl;
	std::cout << "|" << Iw.mean << "\t\t\t" << Iw.error << "\t\t\t" << Iw.fluence << "\t\t   " << Iw.fluence_error << "|" << std::endl;
	std::cout << "|" << Ix.mean << "\t\t\t" << Ix.error << "\t\t\t" << Ix.fluence << "\t\t   " << Ix.fluence_error << "|" << std::endl;
	std::cout << "===============================================================================================" << std::endl;

	PlotDiode(IsWB);
	PlotDiode(IsWA);
	PlotDiode(IsCB);
	PlotDiode(IsCA);

	//Combined data sets
	
	const Int_t nW = 6;
	const Int_t nC = 5;
		
	//Warm Set B
	Double_t xWB[nW] = {Ia.fluence, Ib.fluence, Ic.fluence, Id.fluence, Ie.fluence, If.fluence};
	Double_t yWB[nW] = {Ia.mean, Ib.mean, Ic.mean, Id.mean, Ie.mean, If.mean};
	Double_t exWB[nW] = {Ia.fluence_error, Ib.fluence_error, Ic.fluence_error, Id.fluence_error, Ie.fluence_error, If.fluence_error};
	Double_t eyWB[nW] = {Ia.error, Ib.error, Ic.error, Id.error, Ie.error, If.error};

	//Warm Set A
	Double_t xWA[nW] = {Ig.fluence, Ih.fluence, Ii.fluence, Ij.fluence, Ik.fluence, Il.fluence};
	Double_t yWA[nW] = {Ig.mean, Ih.mean, Ii.mean, Ij.mean, Ik.mean, Il.mean};
	Double_t exWA[nW] = {Ig.fluence_error, Ih.fluence_error, Ii.fluence_error, Ij.fluence_error, Ik.fluence_error, Il.fluence_error};
	Double_t eyWA[nW] = {Ig.error, Ih.error, Ii.error, Ij.error, Ik.error, Il.error};

	//Cold Set B
	Double_t xCB[nC] = {In.fluence, Io.fluence, Ip.fluence, Iq.fluence, Ir.fluence};
	Double_t yCB[nC] = {In.mean, Io.mean, Ip.mean, Iq.mean, Ir.mean};
	Double_t exCB[nC] = {In.fluence_error, Io.fluence_error, Ip.fluence_error, Iq.fluence_error, Ir.fluence_error};
	Double_t eyCB[nC] = {In.error, Io.error, Ip.error, Iq.error, Ir.error};
	
	//Cold Set A
	Double_t xCA[nC] = {It.fluence, Iu.fluence, Iv.fluence, Iw.fluence, Ix.fluence};
	Double_t yCA[nC] = {It.mean, Iu.mean, Iv.mean, Iw.mean, Ix.mean};
	Double_t exCA[nC] = {It.fluence_error, Iu.fluence_error, Iv.fluence_error, Iw.fluence_error, Ix.fluence_error};
	Double_t eyCA[nC] = {It.error, Iu.error, Iv.error, Iw.error, Ix.error};
	
	TGraphErrors *WB = new TGraphErrors(nW,xWB,yWB,exWB,eyWB);
	TGraphErrors *WA = new TGraphErrors(nW,xWA,yWA,exWA,eyWA);
	TGraphErrors *CB = new TGraphErrors(nC,xCB,yCB,exCB,eyCB);
	TGraphErrors *CA = new TGraphErrors(nC,xCA,yCA,exCA,eyCA);
		
		WB->SetMarkerStyle(20);
		WA->SetMarkerStyle(21);
		CB->SetMarkerStyle(22);
		CA->SetMarkerStyle(34);

	TF1* fitc = new TF1("fitc","pol1", 0,5.5e12);
		fitc->SetParameter(1,5e-11);
	TF1* fitw = new TF1("fitw","pol1", 0,5.5e12);
		fitw->SetParameter(1,5e-11);
	TF1* fitall = new TF1("fitall","pol1", 0,5.5e12);
		fitall->SetParameter(1,5e-11);
		
		fitc->SetLineColor(kBlack);
		fitw->SetLineColor(kBlack);
		fitall->SetLineColor(kBlack);

		fitc->SetLineStyle(3);
		fitw->SetLineStyle(7);
		fitall->SetLineStyle(1);		
		
	TMultiGraph *warm = new TMultiGraph();
		warm->Add(WB,"p");
		warm->Add(WA,"p");
		warm->Fit(fitw,"RN");

	TMultiGraph *cold = new TMultiGraph();
		cold->Add(CB,"p");
		cold->Add(CA,"p");
		cold->Fit(fitc,"RN");
	
	TMultiGraph *all = new TMultiGraph();
		all->Add(WB,"p");
		all->Add(WA,"p");
		all->Add(CB,"p");
		all->Add(CA,"p");
		all->Fit(fitall,"RN");
	
	TF1* fit = new TF1("fit","pol1", 0,5.5e12);
		fit->SetParameter(1,5e-11);
		
	TCanvas *combined_warm = new TCanvas("combined_warm","combined_warm",600,700);
		TGaxis::SetMaxDigits(2);
		warm->Draw("AP"); 
		warm->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		warm->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		warm->SetTitle("");
		fitw->Draw("same");
		
		TLegend *legendwarm = new TLegend(0.15,0.75,0.35,0.85);
   		legendwarm->AddEntry(WA,"Warm Set A","p");
   		legendwarm->AddEntry(WB,"Warm Set B","p");
   		legendwarm->Draw();
	
	TCanvas *combined_cold = new TCanvas("combined_cold","combined_cold",600,700);
		TGaxis::SetMaxDigits(2);
		cold->Draw("AP"); 
		cold->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		cold->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		cold->SetTitle("");
		fitc->Draw("same");

		TLegend *legendcold = new TLegend(0.15,0.75,0.35,0.85);
   		legendcold->AddEntry(CA,"Cold Set A","p");
   		legendcold->AddEntry(CB,"Cold Set B","p");
   		legendcold->Draw();

	TCanvas *combined_all = new TCanvas("combined_all","combined_all",600,700);
		TGaxis::SetMaxDigits(2);
		all->Draw("AP"); 
		all->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		all->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		all->SetTitle("");
		fitall->Draw("same");
		fitc->Draw("same");
		fitw->Draw("same");

		TLegend *legendall = new TLegend(0.15,0.55,0.40,0.85);
   		legendall->AddEntry(CA,"Cold Set","p");
		legendall->AddEntry(WA,"Warm Set","p");
		legendall->AddEntry(fitc,"Fit to Cold Data","l");
		legendall->AddEntry(fitw,"Fit to Warm Data","l");
		legendall->AddEntry(fitall,"Fit to All Data","l");
   		legendall->Draw();

	double l = 0.256; //p cm^2
	double w = 0.03; //cm
	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double thetac = fitc->GetParameter(1); //nA cm^2 
	double alphac = pow(10,-9)*thetac/(l*l*w); //A cm^-1
	double ethetac = fitc->GetParError(1);
	double ealphac = pow(10,-9)*ethetac/(l*l*w);
	double kc = alphac/alphan;
	double ekc = pow(pow(ealphac/alphan,2)+pow((alphac*ealphan)/(alphan*alphan),2),0.5);

	double thetaw = fitw->GetParameter(1); //nA cm^2 
	double alphaw = pow(10,-9)*thetaw/(l*l*w); //A cm^-1
	double ethetaw = fitw->GetParError(1);
	double ealphaw = pow(10,-9)*ethetaw/(l*l*w);
	double kw = alphaw/alphan;
	double ekw = pow(pow(ealphaw/alphan,2)+pow((alphaw*ealphan)/(alphan*alphan),2),0.5);

	double thetaall = fitall->GetParameter(1); //nA cm^2 
	double alphaall = pow(10,-9)*thetaall/(l*l*w); //A cm^-1
	double ethetaall = fitall->GetParError(1);
	double ealphaall = pow(10,-9)*ethetaall/(l*l*w);
	double kall = alphaall/alphan;
	double ekall = pow(pow(ealphaall/alphan,2)+pow((alphaall*ealphan)/(alphan*alphan),2),0.5);

	std::cout << "Cold Set Hardness Factor = " << kc << " +/- " << ekc << std::endl;
	std::cout << "Warm Set Hardness Factor = " << kw << " +/- " << ekw << std::endl;
	std::cout << "Overall Hardness Factor = " << kall << " +/- " << ekall << std::endl;		
}	

void GraphLeakageFluence0603_warm_all_error()
{	
	EvaluateDiodes(); 
}
