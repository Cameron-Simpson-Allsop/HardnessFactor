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

Current ExtractIrradiatedCurrent(TString txtName="", TString graphTitle="", double voltage = -91.)//Function to fit curves and extract current from fits at user given voltage.
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

	TF1* fit1 = new TF1("fit1","pol1", 0,1.5e12);
	fit1->SetParameter(1,5e-11);
	TCanvas *Fluence = new TCanvas("Fluence","Fluence",600,700);
	TGraphErrors *g5 = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
		g5->SetMarkerColor(kBlue);
		g5->SetMarkerStyle(33);
		g5->GetXaxis()->SetTitle("Fluence (p/cm^2)");
		g5->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		g5->GetYaxis()->SetTitleOffset(1.1);
		g5->SetTitle("Change in Leakage Current vs Proton Fluence 19/02 combined");
		g5->Fit(fit1,"RN");
		
		//Fluence->SetGrid();
		TGaxis::SetMaxDigits(3);
		gStyle->SetOptStat(0);
		g5->GetXaxis()->SetNdivisions(15);
   		g5->GetYaxis()->SetNdivisions(15);

		/*TLatex *latex1 = new TLatex(g5->GetX()[0], g5->GetY()[0]," A");
		TLatex *latex2 = new TLatex(g5->GetX()[1], g5->GetY()[1]," A");
		TLatex *latex3 = new TLatex(g5->GetX()[2], g5->GetY()[2]," A");
		TLatex *latex4 = new TLatex(g5->GetX()[3], g5->GetY()[3]," A");
		TLatex *latex5 = new TLatex(g5->GetX()[4], g5->GetY()[4]," A");
		TLatex *latex6 = new TLatex(g5->GetX()[5], g5->GetY()[5]," B");
		TLatex *latex7 = new TLatex(g5->GetX()[6], g5->GetY()[6]," B");
		TLatex *latex8 = new TLatex(g5->GetX()[7], g5->GetY()[7]," B");
		TLatex *latex9 = new TLatex(g5->GetX()[8], g5->GetY()[8]," B");
		TLatex *latex10 = new TLatex(g5->GetX()[9], g5->GetY()[9]," B");
		
		latex1->SetTextSize(0.02);
		latex2->SetTextSize(0.02);
		latex3->SetTextSize(0.02);
		latex4->SetTextSize(0.02);
		latex5->SetTextSize(0.02);
		latex6->SetTextSize(0.02);
		latex7->SetTextSize(0.02);
		latex8->SetTextSize(0.02);
		latex9->SetTextSize(0.02);
		latex10->SetTextSize(0.02);

		g5->GetListOfFunctions()->Add(latex1);
		g5->GetListOfFunctions()->Add(latex2);
		g5->GetListOfFunctions()->Add(latex3);
		g5->GetListOfFunctions()->Add(latex4);
		g5->GetListOfFunctions()->Add(latex5);
		g5->GetListOfFunctions()->Add(latex6);
		g5->GetListOfFunctions()->Add(latex7);
		g5->GetListOfFunctions()->Add(latex8);
		g5->GetListOfFunctions()->Add(latex9);
		g5->GetListOfFunctions()->Add(latex10);*/		

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
	double sys_fluence_error = 27./170.; //15.9%

	/*std::cout << "Enter Ni foil calibration factor..." << std::endl;
	std::cin >> c;
	std::cout << "Enter Ni foil calibration factor error..." << std::endl;
	std::cin >> error_c;*/

	Current Ia = ExtractIrradiatedCurrent("Diode_7_Anneal_80mins_1902.txt","Diode 7 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Double_t Inon = ExtractNonIrradiatedCurrent_Inon("Diode_7_1_0711.txt","Diode 7 Unirradiated I-V curve"); //Non Irradiated Current
	Double_t Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_7_1_0711.txt","Diode 7 Unirradiated I-V curve"); //Non Irradiated Current Error	
	Ia.mean = Ia.mean - Inon;
	Ia.error = pow(Ia.error*Ia.error + Inonerror*Inonerror,0.5);
	Ia.fluence = 1.30E+14/c;
	Ia.fluence_error = pow(pow(84297588525.2318/c,2.)+pow((Ia.fluence*error_c)/(c*c),2.) + pow(Ia.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ia); //Puts variable Ia into vector Is. 
	
	Current Ib = ExtractIrradiatedCurrent("Diode_9_Anneal_80mins_1902.txt","Diode 9 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_9_1_0711.txt","Diode 9 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_9_1_0711.txt","Diode 9 Unirradiated I-V curve");	
	Ib.mean = Ib.mean - Inon;
	Ib.error = pow(Ib.error*Ib.error + Inonerror*Inonerror,0.5);
	Ib.fluence = 52688503742014.2/c;
	Ib.fluence_error = pow(pow(74998109020.2371/c,2.)+pow((Ib.fluence*error_c)/(c*c),2.) + pow(Ib.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ib);

	Current Ic = ExtractIrradiatedCurrent("Diode_10_Anneal_80mins_1902.txt","Diode 10 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_10_1_0711.txt","Diode 10 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_10_1_0711.txt","Diode 10 Unirradiated I-V curve");	
	Ic.mean = Ic.mean - Inon;
	Ic.error = pow(Ic.error*Ic.error + Inonerror*Inonerror,0.5);
	Ic.fluence = 5.90E+14/c;
	Ic.fluence_error = pow(pow(90393110979.9842/c,2.)+pow((Ic.fluence*error_c)/(c*c),2.) + pow(Ic.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ic);

	Current Id = ExtractIrradiatedCurrent("Diode_14_Anneal_80mins_1902.txt","Diode 14 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_14_1_0911.txt","Diode 14 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_14_1_0911.txt","Diode 14 Unirradiated I-V curve");	
	Id.mean = Id.mean - Inon;
	Id.error = pow(Id.error*Id.error + Inonerror*Inonerror,0.5);
	Id.fluence = 2.28E+13/c;
	Id.fluence_error = pow(pow(81418286762.212/c,2.)+pow((Id.fluence*error_c)/(c*c),2.) + pow(Id.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Id);

	Current Ie = ExtractIrradiatedCurrent("Diode_6_Anneal_80mins_2811.txt","Diode 6 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_6_1_0711.txt","Diode 6 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_6_1_0711.txt","Diode 6 Unirradiated I-V curve");	
	Ie.mean = Ie.mean - Inon;
	Ie.error = pow(Ie.error*Ie.error + Inonerror*Inonerror,0.5);
	Ie.fluence = 1.30E+14/c;
	Ie.fluence_error = pow(pow(80698744095.8301/c,2.)+pow((Ie.fluence*error_c)/(c*c),2.) + pow(Ie.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ie);

	


	Current If = ExtractIrradiatedCurrent("Diode_5_Anneal_80mins_2411.txt","Diode 5 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_5_1_0711.txt","Diode 5 Unirradiated I-V curve"); //Non Irradiated Current
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_5_1_0711.txt","Diode 5 Unirradiated I-V curve"); //Non Irradiated Current Error	
	If.mean = If.mean - Inon;
	If.error = pow(If.error*If.error + Inonerror*Inonerror,0.5);
	If.fluence = 1.29927e14/c;
	If.fluence_error = pow(pow(8.430e10/c,2.)+pow((If.fluence*error_c)/(c*c),2.) + pow(If.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(If); //Puts variable Ia into vector Is. 
	
	Current Ig = ExtractIrradiatedCurrent("Diode_3_Anneal_80mins_3011.txt","Diode 3 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_3_1_0711.txt","Diode 3 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_3_1_0711.txt","Diode 3 Unirradiated I-V curve");	
	Ig.mean = Ig.mean - Inon;
	Ig.error = pow(Ig.error*Ig.error + Inonerror*Inonerror,0.5);
	Ig.fluence = 5.89938e14/c;
	Ig.fluence_error = pow(pow(9.039e10/c,2.)+pow((Ig.fluence*error_c)/(c*c),2.) + pow(Ig.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ig);

	Current Ih = ExtractIrradiatedCurrent("Diode_4_Anneal_80mins_3011.txt","Diode 4 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_4_1_0711.txt","Diode 4 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_4_1_0711.txt","Diode 4 Unirradiated I-V curve");	
	Ih.mean = Ih.mean - Inon;
	Ih.error = pow(Ih.error*Ih.error + Inonerror*Inonerror,0.5);
	Ih.fluence = 5.26885e13/c;
	Ih.fluence_error = pow(pow(7.500e10/c,2.)+pow((Ih.fluence*error_c)/(c*c),2.) + pow(Ih.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ih);

	Current Ii = ExtractIrradiatedCurrent("Diode_8_Anneal_80mins_3011.txt","Diode 8 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_8_1_0711.txt","Diode 8 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_8_1_0711.txt","Diode 8 Unirradiated I-V curve");	
	Ii.mean = Ii.mean - Inon;
	Ii.error = pow(Ii.error*Ii.error + Inonerror*Inonerror,0.5);
	Ii.fluence = 1.29543e14/c;
	Ii.fluence_error = pow(pow(8.070e10/c,2.)+pow((Ii.fluence*error_c)/(c*c),2.) + pow(Ii.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ii);

	Current Ij = ExtractIrradiatedCurrent("Diode_15_Anneal_80mins_3011.txt","Diode 15 I-V curve, 80 mins of Annealing"); // Irradiated Current
	Inon = ExtractNonIrradiatedCurrent_Inon("Diode_15_1_0911.txt","Diode 15 Unirradiated I-V curve"); //Non
	Inonerror = ExtractNonIrradiatedCurrent_Inonerror("Diode_15_1_0911.txt","Diode 15 Unirradiated I-V curve");	
	Ij.mean = Ij.mean - Inon;
	Ij.error = pow(Ij.error*Ij.error + Inonerror*Inonerror,0.5);
	Ij.fluence = 2.28207e13/c;
	Ij.fluence_error = pow(pow(8.142e10/c,2.)+pow((Ij.fluence*error_c)/(c*c),2.) + pow(Ij.fluence*sys_fluence_error,2.),0.5);
	Is.push_back(Ij);
	
	std::cout << "==============================================================================================="<<std::endl;
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
	std::cout << "==============================================================================================="<<std::endl;

	PlotDiode(Is);

//Pretty Graph

//Excludes High Points
	const Int_t n = 4;
	Double_t SetAx[n] = {If.fluence, Ih.fluence, Ii.fluence, Ij.fluence};
	Double_t SetAy[n] = {If.mean, Ih.mean, Ii.mean, Ij.mean};
	Double_t eSetAx[n] = {If.fluence_error, Ih.fluence_error, Ii.fluence_error, Ij.fluence_error};
	Double_t eSetAy[n] = {If.error, Ih.error, Ii.error, Ij.error};
	
	Double_t SetBx[n] = {Ia.fluence, Ib.fluence, Id.fluence, Ie.fluence};
	Double_t SetBy[n] = {Ia.mean, Ib.mean, Id.mean, Ie.mean};
	Double_t eSetBx[n] = {Ia.fluence_error, Ib.fluence_error, Id.fluence_error, Ie.fluence_error};
	Double_t eSetBy[n] = {Ia.error, Ib.error, Id.error, Ie.error};

//Includes High Points
	/*const Int_t n = 5;
	Double_t SetAx[n] = {If.fluence, Ig.fluence, Ih.fluence, Ii.fluence, Ij.fluence};
	Double_t SetAy[n] = {If.mean, Ig.mean, Ih.mean, Ii.mean, Ij.mean};
	Double_t eSetAx[n] = {If.fluence_error, Ig.fluence_error, Ih.fluence_error, Ii.fluence_error, Ij.fluence_error};
	Double_t eSetAy[n] = {If.error, Ig.error, Ih.error, Ii.error, Ij.error};
	
	Double_t SetBx[n] = {Ia.fluence, Ib.fluence, Ic.fluence, Id.fluence, Ie.fluence};
	Double_t SetBy[n] = {Ia.mean, Ib.mean, Ic.mean, Id.mean, Ie.mean};
	Double_t eSetBx[n] = {Ia.fluence_error, Ib.fluence_error, Ic.fluence_error, Id.fluence_error, Ie.fluence_error};
	Double_t eSetBy[n] = {Ia.error, Ib.error, Ic.error, Id.error, Ie.error};*/

	TCanvas *Better_Formatting = new TCanvas("Better Formatting","Better Formatting",600,700);
	TGraphErrors *SetA = new TGraphErrors(n, SetAx, SetAy, eSetAx, eSetAy);
	TGraphErrors *SetB = new TGraphErrors(n, SetBx, SetBy, eSetBx, eSetBy);
	TMultiGraph *combined = new TMultiGraph();
	Better_Formatting->SetRightMargin(1);
	
		//SetA->SetMarkerColor(kBlue);
		SetA->SetMarkerStyle(20);
		SetA->SetMarkerSize(1);
		SetA->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		SetA->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		SetA->GetYaxis()->SetTitleOffset(1.1);
		SetA->SetTitle("");

		//SetB->SetMarkerColor(kRed);
		SetB->SetMarkerStyle(24);
		SetB->SetMarkerSize(1);
		SetB->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
		SetB->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		SetB->GetYaxis()->SetTitleOffset(1.1);
		SetB->SetTitle("");

		combined->Add(SetA,"p");
		combined->Add(SetB,"p");		
		/*combined->GetXaxis()->SetTitle("Fluence (p/cm^2)");
		combined->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
		combined->GetYaxis()->SetTitleOffset(1.1);
		combined->SetTitle("");*/

	TF1* fitA = new TF1("fitA","[0]*x", 0,2e12);
	TF1* fitB = new TF1("fitB","[0]*x", 0,2e12);
	TF1* fitboth = new TF1("fitboth","[0]*x", 0,2e12);
		fitA->SetParameter(0,5e-11);
		fitB->SetParameter(0,5e-11);
		fitboth->SetParameter(0,5e-11);		

		//fitA->SetLineColor(kBlue);
		//fitB->SetLineColor(kRed);
		//fitboth->SetLineColor(kMagenta);
		fitA->SetLineColor(kBlack); fitB->SetLineColor(kBlack); fitboth->SetLineColor(kBlack);
		fitA->SetLineStyle(3);
		fitB->SetLineStyle(7);
		fitboth->SetLineStyle(1);
		
		SetA->Fit(fitA,"RN");
		SetB->Fit(fitB,"RN");
		combined->Fit(fitboth,"RN");
	
		
		SetA->Draw("AP");
		SetB->Draw("psame");
		//fitA->Draw("same");
		//fitB->Draw("same");
		fitboth->Draw("same");

	   TLegend *legend = new TLegend(0.2,0.75,0.4,0.85);
   		//legend->AddEntry(fitA,"Fit to Set A","l");
   		//legend->AddEntry(fitB,"Fit to Set B","l");
   		//legend->AddEntry(fitboth,"Fit to all Data","l");
		legend->AddEntry(SetA,"Set A","p");
		legend->AddEntry(SetB,"Set B","p");
   		legend->Draw();

	double l = 0.265; //p cm^2
	double w = 0.03; //cm
	double alphan = 3.99e-17; //A cm^-1
	double ealphan = 0.03e-17; //A cm^-1

	double thetaA = fitA->GetParameter(0); //nA cm^2 
	double alphaA = pow(10,-9)*thetaA/(l*l*w); //A cm^-1
	double ethetaA = fitA->GetParError(0);
	double ealphaA = pow(10,-9)*ethetaA/(l*l*w);
	double kA = alphaA/alphan;
	double ekA = pow(pow(ealphaA/alphan,2)+pow((alphaA*ealphan)/(alphan*alphan),2),0.5);

	double thetaB = fitB->GetParameter(0); //nA cm^2 
	double alphaB = pow(10,-9)*thetaB/(l*l*w); //A cm^-1
	double ethetaB = fitB->GetParError(0);
	double ealphaB = pow(10,-9)*ethetaB/(l*l*w);
	double kB = alphaB/alphan;
	double ekB = pow(pow(ealphaB/alphan,2)+pow((alphaB*ealphan)/(alphan*alphan),2),0.5);

	double theta = fitboth->GetParameter(0); //nA cm^2 
	double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1
	double etheta = fitboth->GetParError(0);
	double ealpha = pow(10,-9)*etheta/(l*l*w);
	double k = alpha/alphan;
	double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

	std::cout << "Set A alpha(protons) = " << alphaA << " +/- " << ealphaA << std::endl;
	std::cout << "Set B alpha(protons) = " << alphaB << " +/- " << ealphaB << std::endl;
	std::cout << "Combined alpha(protons) = " << alpha << " +/- " << ealpha << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Set A hardness factor = " << kA << " +/- " << ekA << std::endl;
	std::cout << "Set B hardness factor = " << kB << " +/- " << ekB << std::endl; 	
	std::cout << "Combined hardness factor = " << k << " +/- " << ek << std::endl; 	 			
		
}

void GraphLeakageFluence1902_combined_all_error()
{	

	rootlogonATLAS();
	EvaluateDiodes(); 

}
