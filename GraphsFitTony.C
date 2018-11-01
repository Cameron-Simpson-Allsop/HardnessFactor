#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"

#include "iostream"

struct Current{ //Defines variables within the structure 'Current'.
	float mean = 0;
	float error = 0;
	float temperature = 0;
	float temp_error = 0;
	float voltage = 0;
};

Current ExtractCurrent(TString txtName="", TString graphTitle="", double voltage = -92.0)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -120,-40); //Fits 1st order poly within range
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

void EvaluateBandgapEnergy(std::vector<Current> Currents)//Function to evalute band gap energy. Defines vector 'Currents'
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
	for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
	{
		x.push_back(1.0/Currents[i].temperature); //Puts variable x into vector (1/temperature).
		ex.push_back( (1.0/pow(Currents[i].temperature,2))*Currents[i].temp_error); //Same but errors.
		
		y.push_back(log((Currents[i].mean)/pow(Currents[i].temperature,2))); //Ln(Current/temperature^2)
		ey.push_back(pow(pow((Currents[i].error/Currents[i].mean),2)+pow((2*0.05)/Currents[i].temperature,2),0.5)); //Same but errors.

	}

		
				
		TCanvas *c2 = new TCanvas("c5","c5",600,700); //Defines canvas.
		TGraphErrors *gv = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0])); //Defines graph for vector 'Currents'.
		gv->SetMarkerColor(1);
		gv->SetMarkerStyle(33);
		gv->GetXaxis()->SetTitle("1/T (K^-1)");
		gv->GetYaxis()->SetTitle("ln(I/T^2) (ln(nA/K^2))");
		gv->GetYaxis()->SetTitleOffset(1.3);
		TString title = Form("Photodiode 2: Leakage Current Temperature Dependence %f" , Currents[0].voltage); //Uses string to automatically change voltage in title to given voltage.
		gv->SetTitle(title);
		gv->SetLineColorAlpha(1,0.5);
					
		gv->Draw("AP");
		
		TF1* fit = new TF1("fit","pol1");
		gv->Fit(fit,"RN");
		fit->Draw("same");		

		double m = fit->GetParameter(1);
		double me = fit->GetParError(1);
		
		std::cout<< m << " " << me << std::endl;
		std::cout<< "Eg = (" << m*2*8.6173303e-5*(-1) << " +/- " << me*2*8.6173303e-5 << ") eV" << std::endl;

}

void EvaluateDiode2() //Function to define relevant files and corresponging parameters.
{
	float Voltage = 0;
	std::cout << "Enter Voltage" <<std::endl;
	std::cin >> Voltage; //Input voltage
	std::vector<Current> Is; //Defines vector Is using previously defined function.

	Current Ia = ExtractCurrent("diode2_0711_33C.txt","Photodiode 2: 33C 7/11");//("filename","title") for string.
	Ia.temperature = 306.25;
	Ia.temp_error = 0.15;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
	std::cout << "Ia = " << Ia.mean << " +/- " << Ia.error << std::endl;

	Current Ib = ExtractCurrent("diode2_0711_37C.txt","Photodiode 2: 37C 7/11", Voltage);
	Ib.temperature = 311.;
	Ib.temp_error = 0.2;
	Is.push_back(Ib);
	std::cout << "Ib = " << Ib.mean << " +/- " << Ib.error << std::endl;

	Current Ic = ExtractCurrent("diode2_0711_40C.txt","Photodiode 2: 40C 7/11", Voltage);
	Ic.temperature = 313.15;
	Ic.temp_error = 0.15;
	Is.push_back(Ic);
	std::cout << "Ic = " << Ic.mean << " +/- " << Ic.error << std::endl;

	Current Id = ExtractCurrent("diode2_0711_43C.txt","Photodiode 2: 43C 7/11", Voltage);
	Id.temperature = 316.2;
	Id.temp_error = 0.2;
	Is.push_back(Id);
	std::cout << "Id = " << Id.mean << " +/- " << Id.error << std::endl;
	
	EvaluateBandgapEnergy(Is); //Applies previously defined function.
}

void GraphsFitTony()
{	


	EvaluateDiode2(); //Applies previously defined function.


}
