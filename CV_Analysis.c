#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

double sumvoltage = 0.;
double esumvoltage_squared = 0.;
double voltage = 0.;
double evoltage = 0.;
int nv = 0;

void ExtractVoltage(TString txtName="", TString graphTitle="")
{
	TGraphErrors *g = new TGraphErrors(txtName); 		
	g->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
	g->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);
		

	TF1* fit1 = new TF1("fit1","pol1",2.8,4.55);
	TF1* fit2 = new TF1("fit2","pol1",4.6,5.3);	
	fit1->SetParameter(1,-1);

	TCanvas *canvas = new TCanvas(txtName,txtName);
		g->Draw("ALP");
		g->Fit(fit1,"RN");
		g->Fit(fit2,"RN");
		fit1->Draw("same");
		fit2->Draw("same");		

	double c1 = fit1->GetParameter(0);
	double m1 = fit1->GetParameter(1);
	double c2 = fit2->GetParameter(0);
	double m2 = fit2->GetParameter(1);
	
	double ec1 = fit1->GetParError(0);
	double em1 = fit1->GetParError(1);
	double ec2 = fit2->GetParError(0);
	double em2 = fit2->GetParError(1);
    double Intersect = (c2-c1)/(m1-m2); 
	double e1 = ec2/(m1-m2);
	double e2 = ec1/(m1-m2);
	double e3 = em1*(c2-c1)/(pow(m1-m2,2));
	double e4 = em2*(c2-c1)/(pow(m1-m2,2));
    double eIntersect = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);

	sumvoltage += -exp(Intersect);
	esumvoltage_squared += exp(Intersect)*eIntersect;
	nv += 1;

	std::cout << "Unirradiated voltage = " << sumvoltage/nv << " +/- " << pow(esumvoltage_squared,0.5)/nv << " V\n";
	std::cout << "Unirradiated voltage sum = " << sumvoltage << " +/- " << pow(esumvoltage_squared,0.5) << " V\n";
}

void CV_Analysis()
{
	ExtractVoltage("Diode24_CV_2301_5kHz.txt","Diode 24 Non-Irradiated C-V 23/01 5kHz");
	ExtractVoltage("Diode24_CV_2301_10kHz.txt","Diode 24 Non-Irradiated C-V 23/01 10kHz");
 	ExtractVoltage("Diode24_CV_2301_30kHz.txt","Diode 24 Non-Irradiated C-V 23/01 30kHz");
    	ExtractVoltage("Diode24_CV_2301_60kHz.txt","Diode 24 Non-Irradiated C-V 23/01 60kHz");
    	ExtractVoltage("Diode24_CV_2301_100kHz.txt","Diode 24 Non-Irradiated C-V 23/01 100kHz");

	voltage = sumvoltage/nv;
	evoltage = pow(esumvoltage_squared,0.5)/nv;
	
	std::cout << "\n";
	std::cout << "Average unirradiated max depletion voltage = " << voltage << " +/- " << evoltage << " V\n";
	std::cout << "\n";
}
