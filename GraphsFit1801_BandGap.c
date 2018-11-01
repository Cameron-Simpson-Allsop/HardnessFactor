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

Current ExtractCurrent(TString txtName="", TString graphTitle="", double voltage = -90.8)//Function to fit curves and extract current from fits at user given voltage.
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

	std::cout << p0g << " +/- " << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
}

void EvaluateBandgapEnergy(std::vector<Current> Currents)//Function to evalute band gap energy. Defines vector 'Currents'
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
	for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
	{
		x.push_back(1.0/Currents[i].temperature); //Puts variable x into vector (1/temperature).
		ex.push_back((1.0/pow(Currents[i].temperature,2))*Currents[i].temp_error); //Same but errors.
		
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
		TString title = Form("Photodiode 24: Leakage Current Temperature Dependence %fV" , Currents[0].voltage); //Uses string to automatically change voltage in title to given voltage.
		gv->SetTitle(title);
		gv->SetLineColorAlpha(1,0.5);
		TGaxis::SetMaxDigits(3);			
		gv->Draw("AP");
		
		//TF1* fit = new TF1("fit","pol1");
		TF1* fit1 = new TF1("fit1","pol1", 2.9E-3,3.4E-3);
		//TF1* fit2 = new TF1("fit2","pol1", 3.36E-3,3.6E-3);
		//fit2->SetLineColor(kBlue);
		gv->Fit(fit1,"RN");
		//gv->Fit(fit2,"RN");
		fit1->Draw("same");
		//fit2->Draw("same");		

		double m = fit1->GetParameter(1);
		double me = fit1->GetParError(1);
		//double m1 = fit2->GetParameter(1);
		//double me1 = fit2->GetParError(1);
		
		std::cout << "|================================|" << std::endl;
		std::cout << "|Eg = (" << m*2*8.6173303e-5*(-1.) << " +/- " << me*2*8.6173303e-5 << ") eV" << " |" << std::endl;
		std::cout << "|================================|" << std::endl;
		//std::cout << "Eg (from low temperatures) = (" << m1*2*8.6173303e-5*(-1.) << " +/- " << me1*2*8.6173303e-5 << ") eV" << std::endl;
		//std::cout << "Average = (" << (m*2*8.6173303e-5*(-1.) + m1*2*8.6173303e-5*(-1.))/2. << " +/- " << pow(pow(m*2*8.6173303e-5*(-1.)*me1*2*8.6173303e-5/2,2) + pow(m1*2*8.6173303e-5*(-1.)*me*2*8.6173303e-5/2,2),0.5) << ") eV" << std::endl; 

}

void EvaluateDiode2() //Function to define relevant files and corresponging parameters.
{
	std::vector<Current> Is; //Defines vector Is using previously defined function.

	Current Ia = ExtractCurrent("Diode_24_BandGap_1601_10_8C.txt","Photodiode 24: 10.8C 16/01");//("filename","title") for string.
	Ia.temperature = 283.8;
	Ia.temp_error = 0.1;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
		
	Current Ib = ExtractCurrent("Diode_24_BandGap_1601_15_1C.txt","Photodiode 24: 15.1C 16/01");
	Ib.temperature = 288.1;
	Ib.temp_error = 0.1;
	Is.push_back(Ib); 
	
	Current Ic = ExtractCurrent("Diode_24_BandGap_1601_20_0C.txt","Photodiode 24: 20.0C 16/01");
	Ic.temperature = 293.0;
	Ic.temp_error = 0.1;
	Is.push_back(Ic); 
	
	Current Id = ExtractCurrent("Diode_24_BandGap_1601_25_2C.txt","Photodiode 24: 25.2C 16/01");
	Id.temperature = 298.2;
	Id.temp_error = 0.1;
	Is.push_back(Id); 
		
	Current Ie = ExtractCurrent("Diode_24_BandGap_1601_30_3C.txt","Photodiode 24: 30.3C 16/01");
	Ie.temperature = 303.3;
	Ie.temp_error = 0.1;
	Is.push_back(Ie); 
	
	Current If = ExtractCurrent("Diode_24_BandGap_1601_35_0C.txt","Photodiode 24: 35.0C 16/01");
	If.temperature = 308.0;
	If.temp_error = 0.1;
	Is.push_back(If); 
	
	Current Ig = ExtractCurrent("Diode_24_BandGap_1601_40_0C.txt","Photodiode 24: 40.0C 16/01");
	Ig.temperature = 313.0;
	Ig.temp_error = 0.1;
	Is.push_back(Ig); 
	
	Current Ih = ExtractCurrent("Diode_24_BandGap_1601_45_3C.txt","Photodiode 24: 45.3C 16/01");
	Ih.temperature = 318.3;
	Ih.temp_error = 0.1;
	Is.push_back(Ih); 

	Current Ii = ExtractCurrent("Diode_24_BandGap_1601_50_1C.txt","Photodiode 24: 50.1C 16/01");
	Ii.temperature = 323.1;
	Ii.temp_error = 0.1;
	Is.push_back(Ii); 
	
	Current Ij = ExtractCurrent("Diode_24_BandGap_1601_55_1C.txt","Photodiode 24: 55.1C 16/01");
	Ij.temperature = 328.1;
	Ij.temp_error = 0.1;
	Is.push_back(Ij); 
	
	Current Ik = ExtractCurrent("Diode_24_BandGap_1601_60_1C.txt","Photodiode 24: 60.1C 16/01");
	Ik.temperature = 333.1;
	Ik.temp_error = 0.1;
	Is.push_back(Ik); 
		
	Current Il = ExtractCurrent("Diode_24_BandGap_1601_21_4C.txt","Photodiode 24: 21.4C 16/01");
	Il.temperature = 294.4;
	Il.temp_error = 0.1;
	Is.push_back(Il); 
	
	std::cout << "Ia = " << Ia.mean << " +/- " << Ia.error << std::endl;
	std::cout << "Ib = " << Ib.mean << " +/- " << Ib.error << std::endl;
	std::cout << "Ic = " << Ic.mean << " +/- " << Ic.error << std::endl;
	std::cout << "Id = " << Id.mean << " +/- " << Id.error << std::endl;
	std::cout << "Ie = " << Ie.mean << " +/- " << Ie.error << std::endl;
	std::cout << "If = " << If.mean << " +/- " << If.error << std::endl;
	std::cout << "Ig = " << Ig.mean << " +/- " << Ig.error << std::endl;
	std::cout << "Ih = " << Ih.mean << " +/- " << Ih.error << std::endl;
	std::cout << "Ii = " << Ii.mean << " +/- " << Ii.error << std::endl;
	std::cout << "Ij = " << Ij.mean << " +/- " << Ij.error << std::endl;
	std::cout << "Ik = " << Ik.mean << " +/- " << Ik.error << std::endl;
	std::cout << "Il = " << Il.mean << " +/- " << Il.error << std::endl;
	
	EvaluateBandgapEnergy(Is); //Applies previously defined function.

	
}

/*void EvaluateDiode2() //Function to define relevant files and corresponging parameters.
{
	std::vector<Current> Is; //Defines vector Is using previously defined function.
	
	Current Ia;
	Ia.mean = 1.18E-10; 
	Ia.error = Ia.mean/10.;
	Ia.temperature = 283.8;
	Ia.temp_error = 0.1;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
	
	Current Ib;
	Ib.mean = 1.41E-10; 		
	Ib.error = Ib.mean/10.;
	Ib.temperature = 288.1;
	Ib.temp_error = 0.1;
	Is.push_back(Ib); 

	Current Ic;
	Ic.mean = 2.65E-10;	
	Ic.error = Ic.mean/10.;
	Ic.temperature = 293.0;
	Ic.temp_error = 0.1;
	Is.push_back(Ic); 
	
	Current Id;
	Id.mean = 2.54E-10;
	Id.error = Id.mean/10.;
	Id.temperature = 298.2;
	Id.temp_error = 0.1;
	Is.push_back(Id);
	
	Current Ie;
	Ie.mean = 0.39481766E-9;
	Ie.error = Ie.mean/10.;
	Ie.temperature = 303.3;
	Ie.temp_error = 0.1;
	Is.push_back(Ie);

	Current If;
	If.mean = 0.4387696E-9;
	If.error = If.mean/10.;
	If.temperature = 308.0;
	If.temp_error = 0.1;
	Is.push_back(If);
	
	Current Ig;
	Ig.mean = 1.17418094E-9;
	Ig.error = Ig.mean/10.;
	Ig.temperature = 313.0;
	Ig.temp_error = 0.1;
	Is.push_back(If);
	
	Current Ih;
	Ih.mean = 2.3757352E-9;
	Ih.error = Ih.mean/10.;
	Ih.temperature = 318.3;
	Ih.temp_error = 0.1;
	Is.push_back(Ih);      
		
	EvaluateBandgapEnergy(Is); //Applies previously defined function.

}*/

void GraphsFit1801_BandGap()
{	
	EvaluateDiode2(); //Applies previously defined function.
}
