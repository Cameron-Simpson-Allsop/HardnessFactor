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
  std::vector<double> fracFluenceErrors = {};
  double fracCurrentError;
  std::vector<double> fracCurrentErrors = {};
};

void MC40_Fit_Sim()
{
  //rootlogonATLAS();
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
	error.fracFluenceErrors.push_back(efluence/fluence);
	error.fracCurrentErrors.push_back(ecurrent/current);
	sumFracFluenceError += (efluence/fluence);
	sumFracCurrentError += (ecurrent/current);
	++linecount;	  
      }
      error.fracFluenceError = sumFracFluenceError/(linecount*1.);
      error.fracCurrentError = sumFracCurrentError/(linecount*1.);
      /*accumulator_set<double,stats<tag::variance>> accfluence;
      accumulator_set<double,stats<tag::variance>> acccurrent;
      for_each(error.fracFluenceErrors.begin(), error.fracFluenceErrors.end(), bind<void>(ref(accfluence), _1));
      for_each(error.fracFluenceErrors.begin(), error.fracFluenceErrors.end(), bind<void>(ref(acccurrent), _1));*/

      TH1F *hForce0 = new TH1F("Fit Gradient (Force 0)",";Fit Gradient (nA/p/cm^{2});Counts",100,1.e-10,3.e-10);
  TH1F *hPol1 = new TH1F("Fit Gradient (Pol1)",";Fit Gradient (nA/p/cm^{2});Counts",100,1.e-10,3.e-10);
  TF1 *fitForce0 = new TF1("fitForce0","[0]*x",0.,1.e13);
  TF1 *fitPol1 = new TF1("fitPol1","pol1",0.,1.e13);
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
      //std::cout << fluencePoints[i-1] << "\t" << currentPoints[i-1] << std::endl;      
    }
  
  TGraph *g = new TGraph(fluencePoints.size(), &(fluencePoints[0]), &(currentPoints[0]));
  g->Fit(fitForce0,"RNq");
  g->Fit(fitPol1,"RNq");  
  //std::cout<<fitForce0->GetParameter(0)<<std::endl;
  //std::cout<<fitPol1->GetParameter(1)<<std::endl;
  hForce0->Fill(fitForce0->GetParameter(0));
  hPol1->Fill(fitPol1->GetParameter(1));
    }
  TGaxis::SetMaxDigits(3);
  hForce0->Fit("gaus");
  hPol1->Fit("gaus");
  std::cout << "Fractional fluence error = " << error.fracFluenceError << "\n" << "Fractional current error = " << error.fracCurrentError << std::endl;							  

  double force0Frac{(hForce0->GetStdDev())/(hForce0->GetMean())};
  double pol1Frac{(hPol1->GetStdDev())/(hPol1->GetMean())};
  std::cout << "Force 0 slope fractional error = " << force0Frac << "\n" << "Pol 1 fractional error = " << pol1Frac << std::endl;
  
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->Divide(1,2);
  c1->cd(1);
  hForce0->SetMarkerStyle(20);
  hForce0->Draw();  
  c1->cd(2);
  hPol1->SetMarkerStyle(20);
  hPol1->Draw();  
  c1->SaveAs("MC40_Fit_Simulation.pdf");

}
