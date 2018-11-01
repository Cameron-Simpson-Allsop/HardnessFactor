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

Current ExtractIrradiatedCurrent(TString txtName="", TString graphTitle="", double voltage = -91)//Function to fit curves and extract current from fits at user given voltage.
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
	I.mean = abs(p1g*voltage+p0g)/*-Inon*/;
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
	
	TCanvas *fluence = new TCanvas("fluence","fluence",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlue);
		g5->SetMarkerStyle(33);
		g5->GetXaxis()->SetTitle("Fluence (p/cm^2)");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->GetYaxis()->SetTitleOffset(1.3);
		g5->SetTitle("Change in Leakage Current vs Proton Fluence");
		
		g5->Draw("AP");
		
}

void EvaluateDiodes() //Function to define relevant files and corresponging parameters.
{
	std::cout << "=================================================================" << std::endl;
	std::vector<Current> Is; //Defines vector Is using previously defined function.

	Current Ia = ExtractIrradiatedCurrent("Diode_5_Anneal_0mins_2411.txt","Diode 5 I-V curve, 0 mins of Annealing"); // Irradiated Current
	Double_t Inon = ExtractNonIrradiatedCurrent_Inon("Diode_5_1_0711.txt","Diode 5 Unirradiated I-V curve"); //Non Irradiated Current
	Double_t Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_5_1_0711.txt","Diode 5 Unirradiated I-V curve"); //Non Irradiated Current Error	
	Ia.mean = Ia.mean - Inon;
	Ia.error = pow(Ia.error*Ia.error + Inonerror*Inonerror,0.5);
	Ia.fluence = 0;
	Ia.fluence_error = 0.1;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
	
	/*
	Current Ib = ExtractIrradiatedCurrent("file","title"); // Irradiated Current
	Double_t Inon = ExtractNonIrradiatedCurrent_Inon("file","title"); //Non
	Double_t Inonerror = ExtractNonIrradiatedCurrent_Inonerror("file","title");	
	Ib.mean = Ib.mean - Inon;
	Ib.error = pow(Ib.error*Ib.error + Inonerror*Inonerror,0.5);
	Ib.fluence = 0;
	Ib.fluence_error = 0.1;
	Is.push_back(Ib);
	*/

	std::cout << "================================================================="<<std::endl;
	std::cout << "|" << "Delta I (nA) \t     Delta I Error (nA)" << "|" << std::endl;
	std::cout << "|" << Ia.mean << "\t\t\t\t" << Ia.error << "|" << std::endl; 
	//std::cout << "|" << Ib.mean << "\t\t\t\t" << Ib.error << "|" << std::endl;

	PlotDiode(Is);
	
}

void GraphAnnealingPrelim()
{	


	EvaluateDiodes(); 

}
