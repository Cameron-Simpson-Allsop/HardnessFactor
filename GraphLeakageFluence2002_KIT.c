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
	
	std::vector<double> logx,logy,elogx,elogy; //defines vector with variables x, y, ex, ey.
		for(unsigned int n(0); n<Currents.size(); n++) //Scans 'Currents' for variables  
		{
			logx.push_back(log(Currents[n].fluence)); //Puts variable x into vector.
			elogx.push_back(Currents[n].fluence_error/Currents[n].fluence); //Same but errors.
		
			logy.push_back(log(Currents[n].mean)); 
			elogy.push_back(Currents[n].error/Currents[n].mean);

		}

	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
	TGraphErrors *g = new TGraphErrors(logx.size(), &(logx[0]), &(logy[0]), &(elogx[0]), &(elogy[0]));

		g5->SetMarkerStyle(20);
		g5->SetMarkerSize(1.5);
		g5->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		g5->GetYaxis()->SetTitle("Irradiated Leakage Current (-nA)");
		g5->SetTitle("");

		g->SetMarkerStyle(20);
		g->SetMarkerSize(1.5);
		g->GetXaxis()->SetTitle("ln[Fluence] (ln[pcm^{-2}])");
		g->GetYaxis()->SetTitle("ln[Irradiated Leakage Current] (ln[-nA])");
		g->SetTitle("");

	TF1* fit1 = new TF1("fit1","pol1", 0,2e14);
	fit1->SetParameter(1,5e-11);
	TF1* fit2 = new TF1("fit2","pol1", 0,35);
	fit2->SetParameter(1,2);
		
		fit1->SetLineColor(kBlack);
		fit1->SetLineStyle(1);
		fit2->SetLineColor(kBlack);
		fit2->SetLineStyle(1);

	TCanvas *Fluence = new TCanvas("Fluence","Fluence",600,700);
		//Fluence->Divide(1,2);
	Fluence->SetRightMargin(1);
	//Fluence->cd(1)
		//g5->GetXaxis()->SetRangeUser(0,2.e14);
		//g5->GetYaxis()->SetRangeUser(0,4.e4);
		TGaxis::SetMaxDigits(3);
		g5->Fit(fit1,"RN");		
		g5->Draw("AP");
		fit1->Draw("same");

	TCanvas *Fluence1 = new TCanvas("Fluence1","Fluence1",600,700);
	//Fluence->cd(2);
	Fluence1->SetRightMargin(1);
		//TGaxis::SetMaxDigits(2);
		//gPad->SetLogx();
		//gPad->SetLogy();
		g->Fit(fit2,"RN");		
		g->Draw("AP");
		fit2->Draw("same");
		

	double l = 0.265; //p cm^2
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

	double percentage_error = 0.15;
	double KIT_hardness_factor = 2.0;

	Current Ia = ExtractIrradiatedCurrent("KIT_1_s_Anneal_80mins_1902.txt","KIT Diode 1s I-V curve, 80 mins of Annealing"); // Irradiated Current	
	Ia.fluence = 1.0e13/KIT_hardness_factor;
	Ia.fluence_error = Ia.fluence*percentage_error;
	Is.push_back(Ia); //Puts variable Ia into vector Is.

	Current Ib = ExtractIrradiatedCurrent("KIT_2_s_Anneal_80mins_1902.txt","KIT Diode 2s I-V curve, 80 mins of Annealing"); // Irradiated Current	
	Ib.fluence = 1.0e14/KIT_hardness_factor;
	Ib.fluence_error = Ib.fluence*percentage_error;
	Is.push_back(Ib); //Puts variable Ia into vector Is.

	Current Ic = ExtractIrradiatedCurrent("KIT_3_Anneal_80mins_1902.txt","KIT Diode 3 I-V curve, 80 mins of Annealing"); // Irradiated Current	
	Ic.fluence = 3.0e14/KIT_hardness_factor;
	Ic.fluence_error = Ic.fluence*percentage_error;
	Is.push_back(Ic); //Puts variable Ia into vector Is.

	Current Id = ExtractIrradiatedCurrent("KIT_4_s_Anneal_80mins_1902.txt","KIT Diode 4s I-V curve, 80 mins of Annealing"); // Irradiated Current	
	Id.fluence = 1.0e15/KIT_hardness_factor;
	Id.fluence_error = Id.fluence*percentage_error;
	Is.push_back(Id); //Puts variable Ia into vector Is.  
	
	std::cout << "==============================================================================================="<<std::endl;
	std::cout << "|" << "Delta I (nA) \t     Delta I Error (nA) \t    Fluence (pcm^-2) \tFluence Error (pcm^-2)" << "|" << std::endl;
	std::cout << "|" << Ia.mean << "\t\t\t" << Ia.error << "\t\t\t" << Ia.fluence << "\t\t   " << Ia.fluence_error << "|" << std::endl; 
	std::cout << "|" << Ib.mean << "\t\t\t" << Ib.error << "\t\t\t" << Ib.fluence << "\t\t   " << Ib.fluence_error << "|" << std::endl;
	std::cout << "|" << Ic.mean << "\t\t\t" << Ic.error << "\t\t\t" << Ic.fluence << "\t\t   " << Ic.fluence_error << "|" << std::endl;
	//std::cout << "|" << Id.mean << "\t\t\t" << Id.error << "\t\t\t" << Id.fluence << "\t\t   " << Id.fluence_error << "|" << std::endl;
	std::cout << "==============================================================================================="<<std::endl;

	PlotDiode(Is);
	
}

void GraphLeakageFluence2002_KIT()
{	

	rootlogonATLAS();
	EvaluateDiodes(); 

}
