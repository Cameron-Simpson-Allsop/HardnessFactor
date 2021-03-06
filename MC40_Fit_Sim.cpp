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
//include "RooCurve.h"
//include "RooDataHist.h"
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
  std::string line{""};
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
    getline(MC40,line);
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
  /*TCanvas *fracError = new TCanvas("fracError","fracError",600,600);
  fracError->Divide(2,2);
  fracError->cd(1);
  fracCurrent->Draw("AP");
  fracError->cd(2);
  fracFluence->Draw("AP");
  fracError->cd(3);
  crossCurrent->Draw("AP");
  fracError->cd(4);
  crossFluence->Draw("AP");
  fracError->SaveAs("Fractional_Current_Fluence_Error.png");*/

  TF1 *errorCurrentFit = new TF1("errorCurrentFit","pol1",0,3000);
  TF1 *errorFluenceFit = new TF1("errorCurrentFit","pol1",0,1.5e13);
  
  TGraph *errorCurrent = new TGraph(currents.size(), &(currents[0]), &(ecurrents[0]));
  errorCurrent->GetXaxis()->SetTitle("#Delta I (nA)");
  errorCurrent->GetYaxis()->SetTitle("#sigma #Delta I (nA)");
  errorCurrent->SetTitle("");
  errorCurrent->SetMarkerStyle(20);
  TGraph *errorFluence = new TGraph(fluences.size(), &(fluences[0]), &(efluences[0]));
  errorFluence->GetXaxis()->SetTitle("#phi (p/cm^{2})");
  errorFluence->GetYaxis()->SetTitle("#sigma #phi (p/cm^{2})");
  errorFluence->SetTitle("");
  errorFluence->SetMarkerStyle(20);
  errorCurrent->Fit(errorCurrentFit);
  errorFluence->Fit(errorFluenceFit);
  /*TCanvas *Error = new TCanvas("Error","Error",600,600);
  Error->Divide(1,2);
  Error->cd(1);  
  errorCurrent->Draw("AP");
  Error->cd(2);  
  errorFluence->Draw("AP");
  Error->SaveAs("Current_Fluence_Error.png");*/

  std::cout << "Current error fit: y = " << errorCurrentFit->GetParameter(1) << "x + " << errorCurrentFit->GetParameter(0) << std::endl;
  std::cout << "Fluence error fit: y = " << errorFluenceFit->GetParameter(1) << "x + " << errorFluenceFit->GetParameter(0) << std::endl;

  auto calcCurrentError = [&](double current)
  {
    return (errorCurrentFit->GetParameter(1))*current + (errorCurrentFit->GetParameter(0));
  };
  auto calcFluenceError = [&](double fluence)
  {
    return (errorFluenceFit->GetParameter(1))*fluence + (errorFluenceFit->GetParameter(0));
  };
  
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
      /*for(int i{0}; i < N1; ++i)
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
	  }*/

      for(int i{0}; i < N1; ++i)
	{
	  //double fluencemean = 1.e11 + i*2.e11;
	  double fluencemean = 1.e10 + i*2.e10;
	  double fluencePoint = rndm2->Gaus(fluencemean, calcFluenceError(fluencemean));
	  double currentmeanforce0 = calcCurrent(fluencemean, "force0");
	  double currentPointforce0 = rndm2->Gaus(currentmeanforce0, calcCurrentError(currentmeanforce0));
	  double currentmeanpol1 = calcCurrent(fluencemean, "pol1");
	  double currentPointpol1 = rndm2->Gaus(currentmeanpol1, calcCurrentError(currentmeanpol1));
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

  /*//Construct observables  
  RooRealVar grad("grad","gradient", 5.e-12, 3.e-10);
  RooRealVar inter("Intercept","Intercept",0., -10, 10);
  RooDataHist Force0data("Force0data","result Force 0", grad, hForce0);
  RooDataHist Pol1data("Pol1data","result pol 1", grad, hPol1);
  RooDataHist Pol0data("Pol0data","result pol 0", inter, hPol0);
  
  //Construct Gauss
  RooRealVar meangaus("meangaus","gausmean", 2.e-10, 0., 3.e-10);
  RooRealVar widthgaus("widthgaus","gauswidth", 2.e-11, 0., 4.e-11);
  RooGaussian gradgaus("gradgaus","gradgaussian",grad,meangaus,widthgaus);
  //RooRealVar a("a","a",1,0,100);
  //RooRealVar nn("nn","nn",1,0,100);
  //RooCBShape gradgaus("crystal","crystal",grad,meangaus,widthgaus,a,nn);
  
  RooRealVar meangausInt("meangausInt","gausintmean",0., -10, 10);
  RooRealVar widthgausInt("widthgausInt","gausintwidth",4., -10, 10);
  RooGaussian intgaus("intgaus","intgaussian",inter,meangausInt,widthgausInt);
  
  //Construct Landau
  RooRealVar meanland("meanland","landmean", 2.e-10, 0., 3.e-10);
  RooRealVar widthland("widthland","landwidth", 2.e-11, 0., 4.e-11);
  RooLandau gradland("gradland","gradlandau",grad,meangaus,widthgaus);

   //Set #bins for FFT sampling
  grad.setBins(10000,"cache");

  //Construct convolution of landau & gauss
  RooFFTConvPdf lxg("lxg","landau (X) gauss", grad, gradland, gradgaus);

  grad.setRange("Force0Range",1.4e-10,2.4e-10);
  lxg.fitTo(Force0data,RooFit::Range("Force0Range"));
  RooPlot *frameForce0 = grad.frame();
  frameForce0->SetTitle("");
  Force0data.plotOn(frameForce0);
  lxg.plotOn(frameForce0);

  grad.setRange("Pol1Range",1.1e-10,2.4e-10);
  lxg.fitTo(Pol1data,RooFit::Range("Pol1Range"));
  RooPlot *framePol1 = grad.frame();
  framePol1->SetTitle("");
  Pol1data.plotOn(framePol1);
  lxg.plotOn(framePol1);
  
  intgaus.fitTo(Pol0data);
  RooPlot *framePol0 = inter.frame();
  framePol0->SetTitle("");
  Pol0data.plotOn(framePol0);
  intgaus.plotOn(framePol0);
  
  TCanvas *RooPlots = new TCanvas("RooPlots","RooPlots",600,600);
  RooPlots->Divide(1,3);
  RooPlots->cd(1);
  frameForce0->Draw();
  RooPlots->cd(2);
  framePol1->Draw();
  RooPlots->cd(3);
  framePol0->Draw();*/

    TF1 *gaussian1 = new TF1("gaussian1","gaus", 1.4e-10, 2.1e-10);
    TF1 *gaussian2 = new TF1("gaussian2","gaus", 1.05e-10, 2.05e-10);
    
    TCanvas *c1 = new TCanvas("c1","c1",600,600);
    c1->Divide(1,3);
    c1->cd(1);
    hForce0->Fit(gaussian1,"R");
    hForce0->Draw();
    c1->cd(2);
    hPol1->Draw();
    hPol1->Fit(gaussian2,"R");
    c1->cd(3);
    hPol0->Draw();
    hPol0->Fit("gaus");
    c1->SaveAs("MC40_Fit_Simulation_10_11.pdf");

}
