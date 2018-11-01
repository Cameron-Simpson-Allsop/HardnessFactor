#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"

void CV_updated_error()
{
	rootlogonATLAS();
	TGraphErrors *gr1 = new TGraphErrors("CV_Diode_2_1711.txt");
		gr1->GetXaxis()->SetTitle("Ln(-V) (Ln(V))");
		gr1->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
		gr1->SetTitle("");
		gr1->SetLineColor(kBlack);
		gr1->SetMarkerStyle(20);
		gr1->SetMarkerSize(1);
		

	TF1* fit1 = new TF1("fit1","pol1",2,4.2);
	TF1* fit2 = new TF1("fit2","pol1",4.6,5.4);	
	fit1->SetParameter(1,-1);
	fit1->SetLineColor(kRed);
	fit2->SetLineColor(kRed);	
	
	TCanvas *c1a = new TCanvas("c1","c1",600,700);
		gr1->Draw("AP");
		gr1->Fit(fit1,"RN");
		gr1->Fit(fit2,"RN");
		fit1->Draw("same");
		fit2->Draw("same");
		c1a->SetRightMargin(1);		

	double c1 = fit1->GetParameter(0);
	double m1 = fit1->GetParameter(1);
	double c2 = fit2->GetParameter(0);
	double m2 = fit2->GetParameter(1);
	
	double ec1 = fit1->GetParError(0);
	double em1 = fit1->GetParError(1);
	double ec2 = fit2->GetParError(0);
	double em2 = fit2->GetParError(1);

	TF1* fit3 = new TF1("fit3","[1]*x+[0]",4.19,4.7); //Extrapolates fit lines (Cosmetic).
	TF1* fit4 = new TF1("fit4","[1]*x+[0]",4.3,4.61);
	fit3->SetParameter(0,c1);
	fit3->SetParameter(1,m1);
	fit4->SetParameter(0,c2);
	fit4->SetParameter(1,m2);
	fit3->SetLineColor(kBlack);
	fit4->SetLineColor(kBlack);
	fit3->SetLineWidth(1);
	fit4->SetLineWidth(1);
	
		//fit3->Draw("same");
		//fit4->Draw("same");		

	double c = c2-c1;
	double m = m1-m2;
	double Intersect = (c)/(m); //Intersect of fit lines on x axis.
	double ec = pow(ec1*ec1 + ec2*ec2,0.5);
	double em = pow(em1*em1 + em2*em2,0.5);
	double eIntersect = pow(pow(ec/m,2) + pow((c*em)/pow(m,2),2) + (2*c)/pow(m,3)*ec*em,0.5);
	
	std::cout << "x Intersect = " << Intersect << " +/- " << eIntersect << std::endl;
	std::cout << "Max Depletion Voltage = " << -exp(Intersect) << " +/- " << exp(Intersect)*eIntersect <<std::endl; //Log scale so take exponents.
	std::cout << "Percentage Error = " << 100*exp(Intersect)*eIntersect/exp(Intersect) << "%" << std::endl;	
}
