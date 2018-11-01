#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"

#include "iostream"

struct Current{ //Defines variables within the structure 'Current'.
	float mean = 0;
	float error = 0;
	float time = 0;
	float time_error = 0;
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


Current ExtractCurrent(TString txtName="", TString graphTitle="", double voltage = -91)//Function to fit curves and extract current from fits at user given voltage.
{
	TGraphErrors *g = new TGraphErrors(txtName); //Sets graph parameters with errors.		
	g->GetXaxis()->SetTitle("Voltage(V)");
	g->GetYaxis()->SetTitle("Leakage Current (nA)");
	g->SetTitle("");

	TF1* fit1 = new TF1("fit1","pol1", -110,-65); //Fits 1st order poly within range
	g->Fit(fit1,"RN"); //R = within given range. N = Don't plot.
	fit1->SetLineColor(kBlack);
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

void PlotDiode5(std::vector<Current> Currents)
{
	std::vector<double> x,y,ex,ey; //defines vector with variables x, y, ex, ey.
		for(unsigned int i(0); i<Currents.size(); i++) //Scans 'Currents' for variables  
		{
			x.push_back(Currents[i].time); //Puts variable x into vector.
			ex.push_back(Currents[i].time_error); //Same but errors.
		
			y.push_back(Currents[i].mean); 
			ey.push_back(Currents[i].error);

		}
	
	TCanvas *Diode5 = new TCanvas("Diode5","Diode5",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlue);
		g5->SetMarkerStyle(33);
		g5->GetXaxis()->SetTitle("Annealing Time (mins)");
		g5->GetYaxis()->SetTitle("Leakage Current (-nA)");
		g5->SetTitle("Diode 5 Annealing: 60C for 80mins at 91V");
		
		//Diode5->SetGrid();
		TGaxis::SetMaxDigits(3);
		gStyle->SetOptStat(0);
		g5->GetXaxis()->SetNdivisions(15);
   		g5->GetYaxis()->SetNdivisions(15);

		g5->Draw("AP");
	
	TCanvas *PrettyGraph = new TCanvas("PrettyGraph","PrettyGraph",600,700);
		g5->SetMarkerStyle(20);
		g5->SetMarkerColor(kBlack);
		g5->SetTitle("");
		g5->Draw("AP");
		PrettyGraph->SetRightMargin(1);
		
}

void EvaluateDiode5() //Function to define relevant files and corresponging parameters.
{
	std::vector<Current> Is; //Defines vector Is using previously defined function.

	Current Ia = ExtractCurrent("Diode_5_Anneal_0mins_2411.txt","Diode 5 I-V curve, 0 mins of Annealing");//("filename","title") for string.
	Ia.time = 0;
	Ia.time_error = 0.1;
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
	std::cout << "Ia = " << Ia.mean << " +/- " << Ia.error << std::endl;

	Current Ib = ExtractCurrent("Diode_5_Anneal_10mins_2411.txt","Diode 5 I-V curve, 10 mins of Annealing");//("filename","title") for string.
	Ib.time = 10;
	Ib.time_error = 0.1;
	Is.push_back(Ib); //Puts variable Ia into vector Is. 
	std::cout << "Ib = " << Ib.mean << " +/- " << Ib.error << std::endl;

	Current Ic = ExtractCurrent("Diode_5_Anneal_20mins_2411.txt","Diode 5 I-V curve, 20 mins of Annealing");//("filename","title") for string.
	Ic.time = 20;
	Ic.time_error = 0.1;
	Is.push_back(Ic); //Puts variable Ia into vector Is. 
	std::cout << "Ic = " << Ic.mean << " +/- " << Ic.error << std::endl;

	Current Id = ExtractCurrent("Diode_5_Anneal_30mins_2411.txt","Diode 5 I-V curve, 30 mins of Annealing");//("filename","title") for string.
	Id.time = 30;
	Id.time_error = 0.1;
	Is.push_back(Id); //Puts variable Ia into vector Is. 
	std::cout << "Id = " << Id.mean << " +/- " << Id.error << std::endl;

	Current Ie = ExtractCurrent("Diode_5_Anneal_40mins_2411.txt","Diode 5 I-V curve, 40 mins of Annealing");//("filename","title") for string.
	Ie.time = 40;
	Ie.time_error = 0.1;
	Is.push_back(Ie); //Puts variable Ia into vector Is. 
	std::cout << "Ie = " << Ie.mean << " +/- " << Ie.error << std::endl;

	Current If = ExtractCurrent("Diode_5_Anneal_50mins_2411.txt","Diode 5 I-V curve, 50 mins of Annealing");//("filename","title") for string.
	If.time = 50;
	If.time_error = 0.1;
	Is.push_back(If); //Puts variable Ia into vector Is. 
	std::cout << "If = " << If.mean << " +/- " << If.error << std::endl;

	Current Ig = ExtractCurrent("Diode_5_Anneal_60mins_2411.txt","Diode 5 I-V curve, 60 mins of Annealing");//("filename","title") for string.
	Ig.time = 60;
	Ig.time_error = 0.1;
	Is.push_back(Ig); //Puts variable Ia into vector Is. 
	std::cout << "Ig = " << Ig.mean << " +/- " << Ig.error << std::endl;

	Current Ih = ExtractCurrent("Diode_5_Anneal_70mins_2411.txt","Diode 5 I-V curve, 70 mins of Annealing");//("filename","title") for string.
	Ih.time = 70;
	Ih.time_error = 0.1;
	Is.push_back(Ih); //Puts variable Ia into vector Is. 
	std::cout << "Ih = " << Ih.mean << " +/- " << Ih.error << std::endl;
	
	Current Ii = ExtractCurrent("Diode_5_Anneal_80mins_2411.txt","Diode 5 I-V curve, 80 mins of Annealing");//("filename","title") for string.
	Ii.time = 80;
	Ii.time_error = 0.1;
	Is.push_back(Ii); //Puts variable Ia into vector Is. 
	std::cout << "Ii = " << Ii.mean << " +/- " << Ii.error << std::endl;

	PlotDiode5(Is);
	
}

void GraphAnnealing2411()
{	

	rootlogonATLAS();
	EvaluateDiode5(); //Applies previously defined function.


}
