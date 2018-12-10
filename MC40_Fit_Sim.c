//Force 0 Fit Equation: y = 1.84769e-10*x
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "rootlogonATLAS.h"

#include <iostream>
#include <vector>
#include <cmath>

double calcCurrent(double fluence)
{
  double fitSlope{1.84769e-10};
  return fitSlope*fluence; 
}

struct errors
{
  double fracFluenceError;
  double fracCurrentError;
};

void MC40_Fit_Sim()
{
  
  double fluence, efluence, current, ecurrent;
  double sumFracFluenceError{0};
  double sumFracCurrentError{0};
  errors error;
  int linecount{0};
  ifstream MC40;
  MC40.open("MC40_results.txt");
  if(!MC40.good())
    { std::cout << "Error opening file" << std::endl; }
  else
    while(!MC40.eof())
      {
	MC40 >> fluence >> current >> efluence >> ecurrent;
	//std::cout << fluence << "\t" << efluence << "\t" << current << "\t" << ecurrent << std::endl;
	//std::cout << "fractional fluence/current error = " << efluence/fluence << "\t" << ecurrent/current << std::endl;

	sumFracFluenceError += (efluence/fluence);
	sumFracCurrentError += (ecurrent/current);
	++linecount;	  
      }
      error.fracFluenceError = sumFracFluenceError/(linecount*1.);
      error.fracCurrentError = sumFracCurrentError/(linecount*1.);

  TH1F *h = new TH1F("Fit Slope",";Slope;Counts",100,1.e-10,3.e-10);
  TF1 *fit = new TF1("fit","[0]*x",0.,1.e13);
  int N{10000};
  TRandom2 *rndm2 = new TRandom2(0);
  
  for(int n{0}; n < N; n++)
    {  
  std::vector<double> fluencePoints = {};
  std::vector<double> currentPoints = {};
  int N{20};
  for(int i{1}; i <= N; ++i)
    {
      double fluencemean = i*0.5e11;
      double fluencePoint = rndm2->Gaus(fluencemean, fluencemean*error.fracFluenceError);
      double currentmean = calcCurrent(fluencemean);
      double currentPoint = rndm2->Gaus(currentmean, currentmean*error.fracFluenceError);
      fluencePoints.push_back(fluencePoint);
      currentPoints.push_back(currentPoint);
      std::cout << fluencePoints[i-1] << "\t" << currentPoints[i-1] << std::endl;      
    }
  TGraph *g = new TGraph(fluencePoints.size(), &(fluencePoints[0]), &(currentPoints[0]));
  g->Fit(fit,"RN");
  std::cout<<fit->GetParameter(0)<<std::endl;
  h->Fill(fit->GetParameter(0));
    }

  std::cout << "Fractional fluence error = " << error.fracFluenceError << "\n" << "Fractional current error = " << error.fracCurrentError << std::endl;
  TCanvas *canvas = new TCanvas("canvas","canvas",600,600);
  h->Draw("AP");
  h->Fit("gaus");
}
