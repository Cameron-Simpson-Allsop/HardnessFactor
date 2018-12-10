//Force 0 Fit Equation: y = (1.84769e-10 +/- 9.11651e-12)x
//Pol 1 Fit Equation: y = (1.86778e-10 +/- 9.11651e-12)x + (-1.72396 +/- 4.92234)
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "rootlogonATLAS.h"

#include <iostream>
#include <vector>
#include <cmath>

double calcCurrent(double fluence, std::string fitType)
{
  if(fitType == "force0")
    {
  double fitSlope{1.84769e-10};
  return fitSlope*fluence;
    }
  else if (fitType == "pol1")
    {
      double fitSlope{1.86778e-10};
      double fitIntercept{-1.72396};
      return fitSlope*fluence + fitIntercept;
    }
  else
    std::cout << "Invalid input for calcCurrent function" << std::endl;
  return 0.;
}

struct errors
{
  double fracFluenceError;
  std::vector<double> fracFluenceErrors = {};
  double fracCurrentError;
  std::vector<double> fracCurrentErrors = {};
  double efracFluenceError;
  double efracCurrentError;
};

void MC40_Fit_Sim()
{
  //rootlogonATLAS();
  double fluence, efluence, current, ecurrent;
  double sumFracFluenceError{0};
  double sumFracCurrentError{0};
  double accumFluenceVar{0};
  double accumCurrentVar{0};
  errors error;
  int linecount{0};
  ifstream MC40;
  MC40.open("MC40_results.txt");

  //read in MC40 results and calculate average fractional error for current and fluence
  
  if(!MC40.good()) 
    { std::cout << "Error opening file" << std::endl; }
  else
    while(!MC40.eof())
      {
	MC40 >> fluence >> current >> efluence >> ecurrent;
	//std::cout << fluence << "\t" << efluence << "\t" << current << "\t" << ecurrent << std::endl;
	std::cout << "fractional fluence/current error = " << efluence/fluence << "\t" << ecurrent/current << std::endl;
	error.fracFluenceErrors.push_back(efluence/fluence);
	error.fracCurrentErrors.push_back(ecurrent/current);
	sumFracFluenceError += efluence/fluence;
	sumFracCurrentError += ecurrent/current;
	++linecount;
      }
  std::cout << "===================================================================" << std::endl;

  error.fracFluenceError = sumFracFluenceError/(linecount*1.);
  error.fracCurrentError = sumFracCurrentError/(linecount*1.);

  //calculate standard deviation on average fractional error for current and fluence
  
  for(int vec{0}; vec < error.fracFluenceErrors.size(); ++vec)
    {   
      accumFluenceVar += pow(error.fracFluenceErrors[vec] - error.fracFluenceError,2);
      accumCurrentVar += pow(error.fracCurrentErrors[vec] - error.fracCurrentError,2);
    }
  error.efracFluenceError = pow(accumFluenceVar/(error.fracFluenceErrors.size()-1),0.5);
  error.efracCurrentError = pow(accumCurrentVar/(error.fracCurrentErrors.size()-1),0.5);

  //fit and histogram definitions
  
  TH1F *hForce0 = new TH1F("Fit Gradient (Force 0)",";Fit Gradient (nA/p/cm^{2});Counts",100,1.2e-10,2.4e-10);
  TH1F *hPol1 = new TH1F("Fit Gradient (Pol1)",";Fit Gradient (nA/p/cm^{2});Counts",100,0.8e-10,2.4e-10);
  TH1F *hPol0 = new TH1F("Fit Intercept (Pol1)",";Fit Intercept (nA);Counts",100,-20,40);
  TF1 *fitForce0 = new TF1("fitForce0","[0]*x",0.,1.e13);
  TF1 *fitPol1 = new TF1("fitPol1","pol1",0.,1.e13);

  //using the fit equation from the MC40 data, obtain currents for various fluences between 10^11 and 10^12 p/cm^2. Where each data point is taken from a gaussian with a standard deviation equal to the error on that value. Then, fit the resulting data set, and add the fit parameters to a histogram. 
  
  int N{1000000};
  TRandom2 *rndm2 = new TRandom2(0);
  for(int n{0}; n < N; n++)
    {  
      std::vector<double> fluencePoints = {};
      std::vector<double> currentPointsforce0 = {};
      std::vector<double> currentPointspol1 = {};
      int N1{20};
      for(int i{1}; i <= N1; ++i)
	{
	  double fluencemean = i*0.5e11;
	  double fluencePoint = rndm2->Gaus(fluencemean, fluencemean*error.fracFluenceError);
	  double currentmeanforce0 = calcCurrent(fluencemean, "force0");
	  double currentPointforce0 = rndm2->Gaus(currentmeanforce0, currentmeanforce0*error.fracFluenceError);
	  double currentmeanpol1 = calcCurrent(fluencemean, "pol1");
	  double currentPointpol1 = rndm2->Gaus(currentmeanpol1, currentmeanpol1*error.fracFluenceError);
	  fluencePoints.push_back(fluencePoint);
	  currentPointsforce0.push_back(currentPointforce0);
	  currentPointspol1.push_back(currentPointpol1);
	  //std::cout << fluencePoints[i-1] << "\t" << currentPointsforce0[i-1] << currentPointspol1[i-1] << std::endl;      
	}
  
      TGraph *gforce0 = new TGraph(fluencePoints.size(), &(fluencePoints[0]), &(currentPointsforce0[0]));
      TGraph *gpol1 = new TGraph(fluencePoints.size(), &(fluencePoints[0]), &(currentPointspol1[0]));
      gforce0->Fit(fitForce0,"RNq");
      gpol1->Fit(fitPol1,"RNq");
      //std::cout<<fitForce0->GetParameter(0)<<std::endl;
      //std::cout<<fitPol1->GetParameter(1)<<std::endl;
      //std::cout<<fitPol1->GetParameter(0)<<std::endl;
      hForce0->Fill(fitForce0->GetParameter(0));
      hPol1->Fill(fitPol1->GetParameter(1));
      hPol0->Fill(fitPol1->GetParameter(0));
    }
  TGaxis::SetMaxDigits(3);
  std::cout << "Average fractional fluence error = " << error.fracFluenceError << " +/- " << error.efracFluenceError << "\n" << "Average fractional current error = " << error.fracCurrentError << " +/- " << error.efracCurrentError << std::endl;							  

  double force0Frac{(hForce0->GetStdDev())/(hForce0->GetMean())};
  double pol1Frac{(hPol1->GetStdDev())/(hPol1->GetMean())};
  std::cout << "Force 0 slope fractional error = " << force0Frac << "\n" << "Pol 1 fractional error = " << pol1Frac << std::endl;

  //Draw and fit histograms
  
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->Divide(1,3);
  c1->cd(1);
  hForce0->Fit("gaus");
  hForce0->Draw();
  c1->cd(2);
  hPol1->Draw();
  hPol1->Fit("gaus");
  c1->cd(3);
  hPol0->Draw();
  hPol0->Fit("gaus");
  c1->SaveAs("MC40_Fit_Simulation.pdf");

}
