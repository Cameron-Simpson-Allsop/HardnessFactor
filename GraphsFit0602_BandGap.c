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

void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14) 
{

TStyle* atlasStyle= new TStyle("ATLAS","Atlas style");

// use plain black on white colors
Int_t icol=0;
atlasStyle->SetFrameBorderMode(icol);
atlasStyle->SetCanvasBorderMode(icol);
atlasStyle->SetPadBorderMode(icol);
atlasStyle->SetPadColor(icol);
atlasStyle->SetCanvasColor(icol);
atlasStyle->SetStatColor(icol);
//atlasStyle->SetFillColor(icol);

// set the paper & margin sizes
atlasStyle->SetPaperSize(20,26);
atlasStyle->SetPadTopMargin(0.05);
atlasStyle->SetPadRightMargin(0.05);
atlasStyle->SetPadBottomMargin(0.16);
atlasStyle->SetPadLeftMargin(0.12);

// use large fonts
//Int_t font=72;
Int_t font=42;
Double_t tsize=0.05;
atlasStyle->SetTextFont(font);


atlasStyle->SetTextSize(tsize);
atlasStyle->SetLabelFont(font,"x");
atlasStyle->SetTitleFont(font,"x");
atlasStyle->SetLabelFont(font,"y");
atlasStyle->SetTitleFont(font,"y");
atlasStyle->SetLabelFont(font,"z");
atlasStyle->SetTitleFont(font,"z");

atlasStyle->SetLabelSize(tsize,"x");
atlasStyle->SetTitleSize(tsize,"x");
atlasStyle->SetLabelSize(tsize,"y");
atlasStyle->SetTitleSize(tsize,"y");
atlasStyle->SetLabelSize(tsize,"z");
atlasStyle->SetTitleSize(tsize,"z");


//use bold lines and markers
if ( atlasmarker ) {
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
}
atlasStyle->SetHistLineWidth(2.);
atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

//get rid of X error bars and y error bar caps
//atlasStyle->SetErrorX(0.001);

//do not display any of the standard histogram decorations
atlasStyle->SetOptTitle(0);
//atlasStyle->SetOptStat(1111);
atlasStyle->SetOptStat(0);
//atlasStyle->SetOptFit(1111);
atlasStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
atlasStyle->SetPadTickX(1);
atlasStyle->SetPadTickY(1);

//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);

// DLA overrides
atlasStyle->SetPadLeftMargin(left_margin);
atlasStyle->SetPadBottomMargin(0.13);
atlasStyle->SetTitleYOffset(ytoff);
atlasStyle->SetTitleXOffset(1.0);

 const Int_t NRGBs = 5;
 const Int_t NCont = 255;
 
 Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
 Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
 Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
 Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
 TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
 atlasStyle->SetNumberContours(NCont);

// Enforce the style.
gROOT->SetStyle("ATLAS");
gROOT->ForceStyle();
}

Current ExtractCurrent(TString txtName="", TString graphTitle="", double voltage = -90.8)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", -120,-20); //Fits 1st order poly within range
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
		c2->SetRightMargin(1);
		gv->SetMarkerColor(1);
		gv->SetMarkerStyle(20);
		gv->GetXaxis()->SetTitle("#frac{1}{T} (K^{-1})");
		gv->GetXaxis()->SetTitleOffset(1.2);
		gv->GetYaxis()->SetTitle("ln#left[#frac{I}{T^{2}}#right] #left(ln#left[nAK^{-2}#right]#right)");
		//TString title = Form("Photodiode 24: Leakage Current Temperature Dependence %fV" , Currents[0].voltage); //Uses string to automatically change voltage in title to given voltage.
		//gv->SetTitle(title);
		gv->SetTitle("");
		gv->SetLineColorAlpha(1,0.5);
		TGaxis::SetMaxDigits(3);
		gv->GetXaxis()->SetRangeUser(3.25e-3,3.5e-3);
		gv->GetYaxis()->SetTitleOffset(1.2);			
		gv->Draw("AP");
		
		TF1* fit2 = new TF1("fit2","pol1", 3.25E-3,3.5E-3);
		fit2->SetLineColor(kBlack);
		gv->Fit(fit2,"RN");
		fit2->Draw("same");		

		double m2 = fit2->GetParameter(1);
		double me2 = fit2->GetParError(1);

		std::cout << "|==========================================|" << std::endl;
		std::cout << "|Eg = (" << m2*2*8.6173303e-5*(-1.) << " +/- " << me2*2*8.6173303e-5 << ") eV" << "  |" << std::endl;
		std::cout << "|==========================================|" << std::endl;
		
}

void EvaluateDiode2() //Function to define relevant files and corresponging parameters.
{
	std::vector<Current> Is; //Defines vector Is using previously defined function.

	Current Ia = ExtractCurrent("Diode_24_BandGap_0602__10_1C.txt","Photodiode 24: 10.1C 06/02");//("filename","title") for string.
	Ia.temperature = 283.1;
	Ia.temp_error = 0.1;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
		
	/*Current Ib = ExtractCurrent("Diode_24_BandGap_0602__15C.txt","Photodiode 24: 15C 06/02");
	Ib.temperature = 288.0;
	Ib.temp_error = 0.1;
	Is.push_back(Ib);*/ 
	
	Current Ic = ExtractCurrent("Diode_24_BandGap_0602__15_1C.txt","Photodiode 24: 15.1C 06/02");
	Ic.temperature = 288.1;
	Ic.temp_error = 0.1;
	Is.push_back(Ic);
	
	Current Id = ExtractCurrent("Diode_24_BandGap_0602__20C.txt","Photodiode 24: 20C 06/02");
	Id.temperature = 293.0;
	Id.temp_error = 0.1;
	Is.push_back(Id);
	
	Current Ie = ExtractCurrent("Diode_24_BandGap_0602__25C.txt","Photodiode 24: 25C 06/02");
	Ie.temperature = 298.0;
	Ie.temp_error = 0.1;
	Is.push_back(Ie);
	
	Current If = ExtractCurrent("Diode_24_BandGap_0602__30C.txt","Photodiode 24: 30C 06/02");
	If.temperature = 303.0;
	If.temp_error = 0.1;
	Is.push_back(If);
	
	Current Ig = ExtractCurrent("Diode_24_BandGap_0602__35C.txt","Photodiode 24: 35C 06/02");
	Ig.temperature = 308.0;
	Ig.temp_error = 0.1;
	Is.push_back(Ig);	
	
	//std::cout << "Ia = " << Ia.mean << " +/- " << Ia.error << std::endl;
	//std::cout << "Ib = " << Ib.mean << " +/- " << Ib.error << std::endl;
	std::cout << "Ic = " << Ic.mean << " +/- " << Ic.error << std::endl;
	std::cout << "Id = " << Id.mean << " +/- " << Id.error << std::endl;
	std::cout << "Ie = " << Ie.mean << " +/- " << Ie.error << std::endl;
	std::cout << "If = " << If.mean << " +/- " << If.error << std::endl;
	//std::cout << "Ig = " << Ig.mean << " +/- " << Ig.error << std::endl;
		
	EvaluateBandgapEnergy(Is); //Applies previously defined function.

	
}

void GraphsFit0602_BandGap()
{	
	rootlogonATLAS();
	EvaluateDiode2(); //Applies previously defined function.
}
