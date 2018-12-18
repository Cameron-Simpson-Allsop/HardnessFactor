//Force 0 Fit Equation: y = (1.84769e-10 +/- 9.11651e-12)x
//Pol 1 Fit Equation: y = (1.86778e-10 +/- 9.11651e-12)x + (-1.72396 +/- 4.92234)
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "rootlogonATLAS.h"
//#include "RooRealVar.h"
//#include "RooDataSet.h"
//#include "RooGaussian.h"
//#include "RooLandau.h"
//#include "RooFFTConvPdf.h"
//#include "RooPlot.h"
//#include "RooCurve.h"
//#include "RooDataHist.h"
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
  std::vector<double> fluences;
  std::vector<double> currents;
  std::vector<double> efluences;
  std::vector<double> ecurrents;
  
  //read in MC40 results and calculate average fractional error for current and fluence
  
  if(!MC40.good()) 
    { std::cout << "Error opening file" << std::endl; }
  else
    while(!MC40.eof())
      {
	MC40 >> fluence >> current >> efluence >> ecurrent;
	std::cout << fluence << "\t" << efluence << "\t" << current << "\t" << ecurrent << std::endl;
	std::cout << "fractional fluence/current error = " << efluence/fluence << "\t" << ecurrent/current << std::endl;
	fluences.push_back(fluence);
	currents.push_back(current);
	efluences.push_back(efluence);
	ecurrents.push_back(ecurrent);
	error.fracFluenceErrors.push_back(efluence/fluence);
	error.fracCurrentErrors.push_back(ecurrent/current);
	sumFracFluenceError += efluence/fluence;
	sumFracCurrentError += ecurrent/current;
	++linecount;
      }


  TGraph *fracCurrent = new TGraph(currents.size(), &(currents[0]), &(error.fracCurrentErrors[0]));
  fracCurrent->GetXaxis()->SetTitle("#Delta I (nA)");
  fracCurrent->GetYaxis()->SetTitle("#frac{#sigma #Delta I}{#Delta I}");
  fracCurrent->SetTitle("");
  fracCurrent->SetMarkerStyle(20);
  TGraph *fracFluence = new TGraph(fluences.size(), &(fluences[0]), &(error.fracFluenceErrors[0]));
  fracFluence->GetXaxis()->SetTitle("#phi (p/cm^{2})");
  fracFluence->GetYaxis()->SetTitle("#frac{#sigma #phi}{#phi}");
  fracFluence->SetTitle("");
  fracFluence->SetMarkerStyle(20);
  TGraph *crossCurrent = new TGraph(fluences.size(), &(fluences[0]), &(error.fracCurrentErrors[0]));
  crossCurrent->GetXaxis()->SetTitle("#phi (p/cm^{2})");
  crossCurrent->GetYaxis()->SetTitle("#frac{#sigma #Delta I}{#Delta I}");
  crossCurrent->SetTitle("");
  crossCurrent->SetMarkerStyle(20);
  TGraph *crossFluence = new TGraph(currents.size(), &(currents[0]), &(error.fracFluenceErrors[0]));
  crossFluence->GetXaxis()->SetTitle("#Delta I (nA)");
  crossFluence->GetYaxis()->SetTitle("#frac{#sigma #phi}{#phi}");
  crossFluence->SetTitle("");
  crossFluence->SetMarkerStyle(20);    
  TCanvas *fracError = new TCanvas("fracError","fracError",600,600);
  fracError->Divide(2,2);
  fracError->cd(1);
  fracCurrent->Draw("AP");
  fracError->cd(2);
  fracFluence->Draw("AP");
  fracError->cd(3);
  crossCurrent->Draw("AP");
  fracError->cd(4);
  crossFluence->Draw("AP");
  fracError->SaveAs("Fractional_Current_Fluence_Error.png");

  TGraph *errorCurrent = new TGraph(currents.size(), &(currents[0]), &(ecurrents[0]));
  errorCurrent->GetXaxis()->SetTitle("#Delta I (nA)");
  errorCurrent->GetYaxis()->SetTitle("#sigma #Delta I (nA)");
  errorCurrent->SetTitle("");
  errorCurrent->SetMarkerStyle(20);
  TGraph *errorFluence = new TGraph(fluences.size(), &(fluences[0]), &(efluences[0]));
  errorFluence->GetXaxis()->SetTitle("#Delta I (nA)");
  errorFluence->GetYaxis()->SetTitle("#sigma #Delta I (nA)");
  errorFluence->SetTitle("");
  errorFluence->SetMarkerStyle(20);
  TCanvas *Error = new TCanvas("Error","Error",600,600);
  Error->Divide(1,2);
  Error->cd(1);
  errorCurrent->Fit("pol1");
  errorCurrent->Draw("AP");
  Error->cd(2);
  errorFluence->Fit("pol1");
  errorFluence->Draw("AP");
  Error->SaveAs("Current_Fluence_Error.png");
  
  
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
  
  TH1F *hForce0 = new TH1F("Fit Gradient (Force 0)",";Fit Gradient (nA/p/cm^{2});Counts",100,1.e-10,3.e-10);
  TH1F *hPol1 = new TH1F("Fit Gradient (Pol1)",";Fit Gradient (nA/p/cm^{2});Counts",100,0.5e-10,3.e-10);
  TH1F *hPol0 = new TH1F("Fit Intercept (Pol1)",";Fit Intercept (nA);Counts",100,-40,60);
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
      int N1{5};
      for(int i{0}; i < N1; ++i)
	{
	  double fluencemean = 1.e11 + i*2.e11;
	  //double fluencemean = 1.e10 + i*2.e10;
	  double fluencePoint = rndm2->Gaus(fluencemean, fluencemean*error.fracFluenceError);
	  double currentmeanforce0 = calcCurrent(fluencemean, "force0");
	  double currentPointforce0 = rndm2->Gaus(currentmeanforce0, currentmeanforce0*error.fracFluenceError);
	  double currentmeanpol1 = calcCurrent(fluencemean, "pol1");
	  double currentPointpol1 = rndm2->Gaus(currentmeanpol1, currentmeanpol1*error.fracFluenceError);
	  fluencePoints.push_back(fluencePoint);
	  currentPointsforce0.push_back(currentPointforce0);
	  currentPointspol1.push_back(currentPointpol1);
	  //std::cout << fluencePoints[i] << "\t" << currentPointsforce0[i] << std::endl;
	  //std::cout << fluencemean << std::endl;
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

      if(n == 0)
	{
	  TCanvas *tmpforce00 = new TCanvas("tmpforce00","tmpforce00",600,600);
	  gforce0->GetXaxis()->SetTitle("#phi (p/cm^{2})");
	  gforce0->GetYaxis()->SetTitle("#Delta I (-nA)");
	  gforce0->GetYaxis()->SetTitleOffset(1.25);
	  gforce0->SetTitle("");
	  gforce0->SetMarkerStyle(20);
	  gforce0->Draw("AP");
	  fitForce0->Draw("same");
	  
	  TCanvas *tmppol10 = new TCanvas("tmppol10","temppol10",600,600);	  
	  gpol1->GetXaxis()->SetTitle("#phi (p/cm^{2})");
	  gpol1->GetYaxis()->SetTitle("#Delta I (-nA)");
	  gpol1->GetYaxis()->SetTitleOffset(1.25);
	  gpol1->SetTitle("");
	  gpol1->SetMarkerStyle(20);
	  gpol1->Draw("AP");
	  fitPol1->Draw("same");

	  tmpforce00->SaveAs("DeltaI_vs_Phi_Force0_n0.png");
	  tmppol10->SaveAs("DeltaI_vs_Phi__Pol1_n0.png");
	  tmpforce00->Close();
	  tmppol10->Close();
	}
      
      else if(n == 500000)
	{
	  TCanvas *tmpforce01 = new TCanvas("tmpforce01","tmpforce01",600,600);
	  gforce0->GetXaxis()->SetTitle("#phi (p/cm^{2})");
	  gforce0->GetYaxis()->SetTitle("#Delta I (-nA)");
	  gforce0->GetYaxis()->SetTitleOffset(1.25);
	  gforce0->SetTitle("");
	  gforce0->SetMarkerStyle(20);
	  gforce0->Draw("AP");
	  fitForce0->Draw("same");
	  
	  TCanvas *tmppol11 = new TCanvas("tmppol11","temppol11",600,600);	  
	  gpol1->GetXaxis()->SetTitle("#phi (p/cm^{2})");
	  gpol1->GetYaxis()->SetTitle("#Delta I (-nA)");
	  gpol1->GetYaxis()->SetTitleOffset(1.25);
	  gpol1->SetTitle("");
	  gpol1->SetMarkerStyle(20);
	  gpol1->Draw("AP");
	  fitPol1->Draw("same");

	  tmpforce01->SaveAs("DeltaI_vs_Phi_Force0_n1.png");
	  tmppol11->SaveAs("DeltaI_vs_Phi__Pol1_n1.png");
	  tmpforce01->Close();
	  tmppol11->Close();
	}
      else if(n == 999999)
	{
	  TCanvas *tmpforce02 = new TCanvas("tmpforce02","tmpforce02",600,600);
	  gforce0->GetXaxis()->SetTitle("#phi (p/cm^{2})");
	  gforce0->GetYaxis()->SetTitle("#Delta I (-nA)");
	  gforce0->GetYaxis()->SetTitleOffset(1.25);
	  gforce0->SetTitle("");
	  gforce0->SetMarkerStyle(20);
	  gforce0->Draw("AP");
	  fitForce0->Draw("same");
	  
	  TCanvas *tmppol12 = new TCanvas("tmppol12","temppol12",600,600);	  
	  gpol1->GetXaxis()->SetTitle("#phi (p/cm^{2})");
	  gpol1->GetYaxis()->SetTitle("#Delta I (-nA)");
	  gpol1->GetYaxis()->SetTitleOffset(1.25);
	  gpol1->SetTitle("");
	  gpol1->SetMarkerStyle(20);
	  gpol1->Draw("AP");
	  fitPol1->Draw("same");

	  tmpforce02->SaveAs("DeltaI_vs_Phi_Force0_n2.png");
	  tmppol12->SaveAs("DeltaI_vs_Phi__Pol1_n2.png");
	  tmpforce02->Close();
	  tmppol12->Close();
	}
    }
  TGaxis::SetMaxDigits(3);
  std::cout << "Average fractional fluence error = " << error.fracFluenceError << " +/- " << error.efracFluenceError << "\n" << "Average fractional current error = " << error.fracCurrentError << " +/- " << error.efracCurrentError << std::endl;							  

  double force0Frac{(hForce0->GetStdDev())/(hForce0->GetMean())};
  double pol1Frac{(hPol1->GetStdDev())/(hPol1->GetMean())};
  std::cout << "Force 0 slope fractional error = " << force0Frac << "\n" << "Pol 1 fractional error = " << pol1Frac << std::endl;

  //Draw and fit histograms

  /*RooRealVar grad("grad","gradient", 1.5e-10, 2.e-10);
  RooRealVar mean("mean","gausmean", 1.8e-10, 1.5e-10, 2.e-10);
  RooRealVar width("width","gauswidth", 7.e-12, 6.e-12, 8.e-12);

  RooGaussian gradvalue("gradvalue","gradient PDF",grad,mean,width);
  //RooDataSet *data = gradvalue.generate(grad,1000);
  //gradvalue.fitTo(*data);*/

  //TF1 *landgaus = new TF1("landgaus","gaus(0)+landau(3)",1.2e-10,2.6e-10);
  
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->Divide(1,3);
  c1->cd(1);
  //hForce0->Fit("landgaus","R");
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
