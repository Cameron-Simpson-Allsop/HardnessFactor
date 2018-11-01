#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

struct Current{ //Defines variables within the structure 'Current'.
	float mean = 0;
	float error = 0;
	float fluence = 0;
	float fluence_error = 0;
	float voltage = 0;
};


double ExtractNonIrradiatedCurrent_Inon(TString txtName="", TString graphTitle ="", double voltage = -91)
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

double ExtractNonIrradiatedCurrent_Inonerror(TString txtName="", TString graphTitle ="", double voltage = -91)
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

	TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g1->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.

	double Inonerror = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	std::cout << "Inonerror = " << Inonerror << std::endl;

	return Inonerror;
}

Current ExtractIrradiatedCurrent(TString txtName="", TString graphTitle="", double voltage = -91.0)//Function to fit curves and extract current from fits at user given voltage.
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

	TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->Draw("same"); //Plots defined fit.

	Current I; //Calculate variables within the 'Current' structure.
	I.mean = abs(p1g*voltage+p0g);
	I.error = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	I.voltage = voltage;

	std::cout << p0g << "+/-" << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
}

void PlotDiode(std::vector<Current> Currents)
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
		for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
		{
			x.push_back(Currents[i].fluence); //Puts variable x into vector.
			ex.push_back(Currents[i].fluence_error); //Same but errors.
		
			y.push_back(Currents[i].mean); 
			ey.push_back(Currents[i].error);

		}

	TF1* fit1 = new TF1("fit1","pol1", 0,8e12);
	fit1->SetParameter(1,5e-11);
	TCanvas *Fluence = new TCanvas("Fluence","Fluence",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlue);
		g5->SetMarkerStyle(33);
		g5->GetXaxis()->SetTitle("Fluence (p/cm^2)");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->GetYaxis()->SetTitleOffset(1.1);
		g5->SetTitle("Change in Leakage Current vs Proton Fluence");
		g5->Fit(fit1,"RN");
		
		//Fluence->SetGrid();
		TGaxis::SetMaxDigits(3);
		gStyle->SetOptStat(0);
		g5->GetXaxis()->SetNdivisions(15);
   		g5->GetYaxis()->SetNdivisions(15);
		
		g5->Draw("A*");
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

	std::cout << "alpha(protons) = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "hardness factor = " << k << " +/- " << ek << std::endl; 		
}

void EvaluateDiodes() //Function to define relevant files and corresponging parameters.
{
	std::cout << "=================================================================" << std::endl;
	std::vector<Current> Is; //Defines vector Is using previously defined function.
	
	double c = 112.67;
	double error_c = 0.55238 + 5.358;
	double sys_error = 0.134;

	/*std::cout << "Enter Ni foil calibration factor..." << std::endl;
	std::cin >> c;
	std::cout << "Enter Ni foil calibration factor error..." << std::endl;
	std::cin >> error_c;*/

	Current Ia = ExtractIrradiatedCurrent("Diode_5_Anneal_80mins_2411.txt","Diode 5 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Double_t Inon = ExtractNonIrradiatedCurrent_Inon("Diode_5_1_0711.txt","Diode 5 Unirradiated I-V curve"); //Non Irradiated Current
	Double_t Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_5_1_0711.txt","Diode 5 Unirradiated I-V curve"); //Non Irradiated Current Error	
	Ia.mean = Ia.mean - Inon;
	Ia.error = pow(Ia.error*Ia.error + Inonerror*Inonerror,0.5);
	Ia.fluence = 1.29927e14/c;
	Ia.fluence_error = Ia.fluence*sys_error;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
	
	Current Ib = ExtractIrradiatedCurrent("Diode_3_Anneal_80mins_3011.txt","Diode 3 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_3_1_0711.txt","Diode 3 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_3_1_0711.txt","Diode 3 Unirradiated I-V curve");	
	Ib.mean = Ib.mean - Inon;
	Ib.error = pow(Ib.error*Ib.error + Inonerror*Inonerror,0.5);
	Ib.fluence = 5.89938e14/c;
	Ib.fluence_error = Ib.fluence*sys_error;
	Is.push_back(Ib);

	Current Ic = ExtractIrradiatedCurrent("Diode_4_Anneal_80mins_3011.txt","Diode 4 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_4_1_0711.txt","Diode 4 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_4_1_0711.txt","Diode 4 Unirradiated I-V curve");	
	Ic.mean = Ic.mean - Inon;
	Ic.error = pow(Ic.error*Ic.error + Inonerror*Inonerror,0.5);
	Ic.fluence = 5.26885e13/c;
	Ic.fluence_error = Ic.fluence*sys_error;
	Is.push_back(Ic);

	Current Id = ExtractIrradiatedCurrent("Diode_8_Anneal_80mins_3011.txt","Diode 8 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_8_1_0711.txt","Diode 8 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_8_1_0711.txt","Diode 8 Unirradiated I-V curve");	
	Id.mean = Id.mean - Inon;
	Id.error = pow(Id.error*Id.error + Inonerror*Inonerror,0.5);
	Id.fluence = 1.29543e14/c;
	Id.fluence_error = Id.fluence*sys_error;
	Is.push_back(Id);

	Current Ie = ExtractIrradiatedCurrent("Diode_15_Anneal_80mins_3011.txt","Diode 15 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_15_1_0911.txt","Diode 15 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_15_1_0911.txt","Diode 15 Unirradiated I-V curve");	
	Ie.mean = Ie.mean - Inon;
	Ie.error = pow(Ie.error*Ie.error + Inonerror*Inonerror,0.5);
	Ie.fluence = 2.28207e13/c;
	Ie.fluence_error = Ie.fluence*sys_error;
	Is.push_back(Ie);
	
	

	std::cout << "==============================================================================================="<<std::endl;
	std::cout << "|" << "Delta I (nA) \t     Delta I Error (nA) \t    Fluence (pcm^-2) \tFluence Error (pcm^-2)" << "|" << std::endl;
	std::cout << "|" << Ia.mean << "\t\t\t" << Ia.error << "\t\t\t" << Ia.fluence << "\t\t   " << Ia.fluence_error << "|" << std::endl; 
	std::cout << "|" << Ib.mean << "\t\t\t" << Ib.error << "\t\t\t" << Ib.fluence << "\t\t   " << Ib.fluence_error << "|" << std::endl;
	std::cout << "|" << Ic.mean << "\t\t\t" << Ic.error << "\t\t\t" << Ic.fluence << "\t\t   " << Ic.fluence_error << "|" << std::endl;
	std::cout << "|" << Id.mean << "\t\t\t" << Id.error << "\t\t\t" << Id.fluence << "\t\t   " << Id.fluence_error << "|" << std::endl;
	std::cout << "|" << Ie.mean << "\t\t\t" << Ie.error << "\t\t\t" << Ie.fluence << "\t\t   " << Ie.fluence_error << "|" << std::endl;
	std::cout << "==============================================================================================="<<std::endl;

	PlotDiode(Is);
	
}

void GraphLeakageFluence3011_sys()
{	


	EvaluateDiodes(); 

}
