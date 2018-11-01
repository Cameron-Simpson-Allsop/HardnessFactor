#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "cmath"
#include "fstream"

double MaxDep{0};
double eMaxDep_squared{0};

int n1{0};

void Extract_Max_Depletion_Voltage(TString txtName="", double min1 = 0., double max1 = 0., double min2 = 0., double max2 = 0.)
{
  ifstream file;
  file.open(txtName);

  std::vector<double> v, c;
  int n = 0;
  while(!file.eof())
    {
      double voltage, capacitance;
      file >> voltage >> capacitance;

      v.push_back(voltage);
      c.push_back(1/pow(capacitance,2));

      n = n+1;
      //std::cout << voltage << " " << capacitance << "\n" << n << "\n";

    }
  
  TGraph *g = new TGraph(n, &v[0], &c[0]);
	g->GetXaxis()->SetTitle("Voltage(-V)");
	g->GetYaxis()->SetTitle("1/Capacitance^{2} (1/F^{2})");
	g->SetTitle("");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetMarkerStyle(20);
	g->SetMarkerSize(1.2);
	
	TF1* fit1 = new TF1("fit1","pol1", min1, max1);
	TF1* fit2 = new TF1("fit2","pol1", min2, max2);
	
	fit1->SetLineColor(kRed);
	fit2->SetLineColor(kRed);
	g->Fit(fit1,"RN");
	g->Fit(fit2,"RN");

	TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
	g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
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
	
	std::cout << txtName << std::endl;
	std::cout << "Max Depletion Voltage = " << Intersect << " +/- " << eIntersect << " V" << std::endl;

	MaxDep += Intersect;
	eMaxDep_squared += pow(eIntersect,2);
	n1 += 1;
	
}

void Isidre_CV()
{
	std::cout << "Non-Irradiated" << std::endl;
	std::cout << "=====================================================================" << std::endl;

	Extract_Max_Depletion_Voltage("W332-C4_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-F2_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-F8_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M10_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M12_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M4_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M6_nonirr_CV.txt",50., 250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M7_nonirr_CV.txt",50., 250., 300., 350.);

	int n_1 = n1;
	double MaxDepUnirr = MaxDep/n1;
	
	std::cout << "Pre-Annealing" << std::endl;
	std::cout << "=====================================================================" << std::endl;

	Extract_Max_Depletion_Voltage("W332-C4_preanneal_CV.txt",50. ,200., 250., 300.);
       	Extract_Max_Depletion_Voltage("W332-F2_preanneal_CV.txt",20. ,35., 100., 250.);
	Extract_Max_Depletion_Voltage("W332-F8_preanneal_CV.txt",100. ,150., 150., 300.);
	Extract_Max_Depletion_Voltage("W332-M10_preanneal_CV.txt",50. ,250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M12_preanneal_CV.txt",20. ,35., 75., 300.);
	Extract_Max_Depletion_Voltage("W332-M4_preanneal_CV.txt",50. ,250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M6_preanneal_CV.txt",100. ,160., 200., 300.);
	Extract_Max_Depletion_Voltage("W332-M7_preanneal_CV.txt",50. ,200., 250., 340.);

	int n_2 = n1 - n_1;
	double MaxDepPre = (MaxDep - MaxDepUnirr*n_1)/n1;

	std::cout << "Post-Annealing" << std::endl;
	std::cout << "=====================================================================" << std::endl;
	
	Extract_Max_Depletion_Voltage("W332-C4_postanneal_CV.txt",50. ,240., 260., 350.);
	Extract_Max_Depletion_Voltage("W332-F2_postanneal_CV.txt",40. ,75., 100., 300.);
	Extract_Max_Depletion_Voltage("W332-F8_postanneal_CV.txt",150. ,170., 200., 350.);
	Extract_Max_Depletion_Voltage("W332-M10_postanneal_CV.txt",50. ,240., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M12_postanneal_CV.txt",40. ,70., 100., 200.);
	Extract_Max_Depletion_Voltage("W332-M4_postanneal_CV.txt",50. ,250., 300., 350.);
	Extract_Max_Depletion_Voltage("W332-M6_postanneal_CV.txt",150. ,190., 250., 350.);
	Extract_Max_Depletion_Voltage("W332-M7_postanneal_CV.txt",50. ,225., 260., 350.);

	double MaxDepPost = (MaxDep - MaxDepPre*n_2)/n1;

	//std::cout << "\nAverage unirradiated maximum depletion voltage = " << MaxDepUnirr << " V\nAverage pre-annealing maximum depletion voltage = " << MaxDepPre << " V\nAverage post- annealing maximum depletion voltage = " << MaxDepPost << " V\n";

}	
