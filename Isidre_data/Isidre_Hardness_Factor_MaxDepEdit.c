#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

struct CurrentWarmSetA{ 
	float mean = 0;
	float error = 0;
	float fluence = 0;
	float fluence_error = 0;
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


double ExtractNonIrradiatedCurrent_Inon(TString txtName="", TString graphTitle ="", double voltage = 10.)
{
	TGraphErrors *g1 = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	TF1* fit1 = new TF1("fit1","pol1", 0,300); //Fits 1st order poly within range
	g1->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);
	double Inon = abs(p1g*voltage+p0g);
	std::cout << "Inon = " << Inon << std::endl;

	return Inon;
}

double ExtractNonIrradiatedCurrent_Inonerror(TString txtName="", TString graphTitle ="", double voltage = 10.)
{
	TGraphErrors *g1 = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g1->GetXaxis()->SetTitle("Voltage(-V)");
	g1->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g1->GetYaxis()->SetTitleOffset(1.45);
	g1->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", 0,300); //Fits 1st order poly within range
	g1->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	TGaxis::SetMaxDigits(3);
	canvas->SetRightMargin(1);
	g1->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->SetLineColor(kRed);
	fit1->Draw("same"); //Plots defined fit.

	double Inonerror = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	std::cout << "Inonerror = " << Inonerror << std::endl;

	return Inonerror;
}

CurrentWarmSetA ExtractIrradiatedCurrentWA(TString txtName="", TString graphTitle="", double voltage = 10.)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(-V)");
	g->GetYaxis()->SetTitle("Leakage Current (-nA)");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);

	TF1* fit1 = new TF1("fit1","pol1", 4,15); //Fits 1st order poly within range
	g->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	//g->GetXaxis()->SetRangeUser(0,20);
	double p0g = fit1->GetParameter(0); //Assigns fit parameters.
	double p0ge = fit1->GetParError(0);
	double p1g = fit1->GetParameter(1);
	double p1ge = fit1->GetParError(1);

	TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
	fit1->SetLineColor(kRed);
	fit1->Draw("same"); //Plots defined fit.

	CurrentWarmSetA I; //Calculate variables within the 'Current' structure.
	I.mean = abs(p1g*voltage+p0g);
	I.error = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
	I.voltage = voltage;

	std::cout << p0g << "+/-" << p0ge << "  " << fit1->Eval(I.voltage) << "  " << I.mean << std::endl; //Prints parameters as a check. Eval function used as a concordancy check for I.mean
	
	return I;
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

	//TF1* fit1 = new TF1("fit1","[0]*x", 0,2e14); mx fit
	//fit1->SetParameter(0,1e-12);
	TF1* fit1 = new TF1("fit1","pol1", 0,2e14); //pol1 fit
	fit1->SetParameter(1,1e-12);
	fit1->SetParameter(0,0);
	TCanvas *Fluence = new TCanvas("Isidre Current v Fluence","Isidre Current v Fluence",600,700);
	Fluence->SetRightMargin(1);
	Fluence->SetTopMargin(1);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlack);
		g5->SetMarkerStyle(20);
		g5->SetMarkerSize(2);
		g5->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->SetTitle("");
		g5->GetYaxis()->SetRangeUser(0,3e4);
		g5->GetXaxis()->SetRangeUser(0,2e14);
		g5->Fit(fit1,"RN");
		
		fit1->SetLineColor(kRed);
		//fit1->SetLineStyle(7);
		
		TGaxis::SetMaxDigits(3);

		g5->Draw("AP");
		fit1->Draw("same");

	double l = 0.5; //p cm^2
	double w = 0.03; //cm

	//double theta = fit1->GetParameter(0); //nA cm^2
	//double etheta = fit1->GetParError(0); //mx fit

	double theta = fit1->GetParameter(1); //nA cm^2
	double etheta = fit1->GetParError(1); //pol1 fit

	double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1
	double ealpha = pow(10,-9)*etheta/(l*l*w);

	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double k = alpha/alphan;
	double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

	std::cout << "Isidre Alpha = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "Isidre Hardness Factor = " << k << " +/- " << ek << std::endl;
	//std::cout << theta << " " << etheta << std::endl; 		
}

void EvaluateDiodes() //Function to define relevant files and corresponging parameters.
{
	std::cout << "=================================================================" << std::endl;
	std::vector<CurrentWarmSetA> IsWA;	

	double sys_fluence_error = 0.07; //7%
	double k = 1.; //hardness factor
	
	CurrentWarmSetA Ia = ExtractIrradiatedCurrentWA("W332-C4_irr.txt"); 
	Double_t Inon = ExtractNonIrradiatedCurrent_Inon("W332-C4_nonirr.txt");
	Double_t Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-C4_nonirr.txt");	
	Ia.mean = Ia.mean - Inon;
	Ia.error = pow(Ia.error*Ia.error + Inonerror*Inonerror,0.5);
	Ia.fluence = 7.44e12/k;
	Ia.fluence_error = Ia.fluence*sys_fluence_error;
	IsWA.push_back(Ia);
	
	CurrentWarmSetA Ib = ExtractIrradiatedCurrentWA("W332-F2_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-F2_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-F2_nonirr.txt");	
	Ib.mean = Ib.mean - Inon;
	Ib.error = pow(Ib.error*Ib.error + Inonerror*Inonerror,0.5);
	Ib.fluence = 9.66e13/k;
	Ib.fluence_error = Ib.fluence*sys_fluence_error;
	IsWA.push_back(Ib);

	CurrentWarmSetA Ic = ExtractIrradiatedCurrentWA("W332-F8_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-F8_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-F8_nonirr.txt");	
	Ic.mean = Ic.mean - Inon;
	Ic.error = pow(Ic.error*Ic.error + Inonerror*Inonerror,0.5);
	Ic.fluence = 2.41e13/k;
	Ic.fluence_error = Ic.fluence*sys_fluence_error;
	IsWA.push_back(Ic);

	CurrentWarmSetA Id = ExtractIrradiatedCurrentWA("W332-M10_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-M10_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-M10_nonirr.txt");	
	Id.mean = Id.mean - Inon;
	Id.error = pow(Id.error*Id.error + Inonerror*Inonerror,0.5);
	Id.fluence = 1.09e12/k;
	Id.fluence_error = Id.fluence*sys_fluence_error;
	IsWA.push_back(Id);
	
	CurrentWarmSetA Ie = ExtractIrradiatedCurrentWA("W332-M12_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-M12_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-M12_nonirr.txt");	
	Ie.mean = Ie.mean - Inon;
	Ie.error = pow(Ie.error*Ie.error + Inonerror*Inonerror,0.5);
	Ie.fluence = 9.66e13/k;
	Ie.fluence_error = Ie.fluence*sys_fluence_error;
	IsWA.push_back(Ie);

	CurrentWarmSetA If = ExtractIrradiatedCurrentWA("W332-M4_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-M4_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-M4_nonirr.txt");
	If.mean = If.mean - Inon;
	If.error = pow(If.error*If.error + Inonerror*Inonerror,0.5);
	If.fluence = 1.09e12/k;
	If.fluence_error = If.fluence*sys_fluence_error;
	IsWA.push_back(If);
	
	CurrentWarmSetA Ig = ExtractIrradiatedCurrentWA("W332-M6_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-M6_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-M6_nonirr.txt");	
	Ig.mean = Ig.mean - Inon;
	Ig.error = pow(Ig.error*Ig.error + Inonerror*Inonerror,0.5);
	Ig.fluence = 2.41e13/k;
	Ig.fluence_error = Ig.fluence*sys_fluence_error;
	IsWA.push_back(Ig);

	CurrentWarmSetA Ih = ExtractIrradiatedCurrentWA("W332-M7_irr.txt"); 
	Inon = ExtractNonIrradiatedCurrent_Inon("W332-M7_nonirr.txt");
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("W332-M7_nonirr.txt");	
	Ih.mean = Ih.mean - Inon;
	Ih.error = pow(Ih.error*Ih.error + Inonerror*Inonerror,0.5);
	Ih.fluence = 7.44e12/k;
	Ih.fluence_error = Ih.fluence*sys_fluence_error;
	IsWA.push_back(Ih);

	
	
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
	
	PlotDiode(IsWA);	
	
}	

void Isidre_Hardness_Factor_MaxDepEdit()
{	
	rootlogonATLAS();
	EvaluateDiodes();
	std::cout << "Note: Uses a max depletion voltage value of 10V (from Isidre's C-V measurements)" << std::endl;
}
