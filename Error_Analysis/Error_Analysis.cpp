#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooFFTConvPdf.h"
#include "RooPlot.h"
#include "RooCurve.h"
#include "RooDataHist.h" 
using namespace RooFit;

struct Data
{
  std::vector<double> fluence; //p/cm^2
  std::vector<double> current; //nA
  std::vector<double> efluence;
  std::vector<double> ecurrent;
  std::vector<double> kappa;
  std::vector<double> ekappa;
};

double StdDev(std::vector<double> v, double mean)
{
  double sqsum{0.};
  for(int i{0}; i<v.size(); ++i)
    {
      sqsum += pow(v[i]-mean,2);
    }
  return pow(sqsum/(v.size()-1.),0.5);
}

void Error_Analysis()
{
  Data data;
  ifstream inFile;
  inFile.open("MC40_results.txt");
  std::string line{""};
  double fluence,current,efluence,ecurrent;
  getline(inFile,line);
  while(true)
    {
      getline(inFile,line);
      if(inFile.eof()){break;}
      stringstream ss(line);
      ss>>fluence>>current>>efluence>>ecurrent;
      data.fluence.push_back(fluence);
      data.current.push_back(current);
      data.efluence.push_back(efluence);
      data.ecurrent.push_back(ecurrent);
    }

  TH1F *hardness = new TH1F("Hardness Factor",";Hardness Factor value;Counts",100,1.6,2.7);
  hardness->SetMarkerStyle(20);
  hardness->SetMarkerSize(0.5);
  
  int Ntrials = 50000;
  TRandom2 *rndm = new TRandom2();
  //Sensor parameters
  double l{0.265}; //p cm^2
  double w{0.03}; //cm
  double alphan{3.99e-17}; //A cm^-1
  double ealphan{0.03e-17}; //A cm^-1
  for(int i{0}; i<Ntrials; ++i)
    {
      std::vector<double> tmpfluence,tmpcurrent;
      for(int n{0}; n<data.fluence.size(); ++n)
	{
	  tmpfluence.push_back(rndm->Gaus(data.fluence[n],data.efluence[n]));
	  tmpcurrent.push_back(rndm->Gaus(data.current[n],data.ecurrent[n]));
	}
      TGraphErrors *gtmp = new TGraphErrors(tmpfluence.size(),&(tmpfluence[0]),&(tmpcurrent[0]),&(data.efluence[0]),&(data.ecurrent[0]));
      TF1 *tmpfit = new TF1("tmpfit","pol1",0,6e12);
      tmpfit->SetParameter(1,5e-11);
      tmpfit->SetParameter(0,0);
      gtmp->Fit(tmpfit,"QRN");

      //Calculates hardness factor from fit
      double theta = tmpfit->GetParameter(1); //nA cm^2
      double etheta = tmpfit->GetParError(1); //pol1 fit
      double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1
      double ealpha = pow(10,-9)*etheta/(l*l*w);
      double k = alpha/alphan;
      double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);

      data.kappa.push_back(k);
      data.ekappa.push_back(ek);
      hardness->Fill(k);
    }

  double kappaAv = std::accumulate(data.kappa.begin(),data.kappa.end(),0.)/data.kappa.size();
  double ekappaAv = StdDev(data.kappa,kappaAv);
  double Avekappa = std::accumulate(data.ekappa.begin(),data.ekappa.end(),0.)/data.kappa.size();
  double eAvekappa = StdDev(data.ekappa,Avekappa);
  
  std::cout<<"Average hardness factor value: "<<kappaAv<<" +/- "<<ekappaAv<<std::endl;
  std::cout<<"Average uncertainty: "<<Avekappa<<" +/- "<<eAvekappa<<std::endl<<std::endl;

  std::cout<<"Uncertainty on the hardness factor value is taken as the stdev of "<<Ntrials<<" hardness factor values, generated via monte carlo.\n\nThe average uncertainty is taken as the average of the fit uncertainties for each hardness factor value. The uncertainty on this value is the stdev of these uncertainties."<<std::endl;

  RooRealVar kappa("kappa","kappa",1.,4.);
  RooDataHist kappadata("kappadata","Hardness",kappa,hardness);
  RooRealVar gkappa("gkappa","gkappa",1.7,2.7);
  RooDataHist gkappadata("gkappadata","Hardness",gkappa,hardness);
  
  //Crystal ball fit
  RooRealVar mean("mean","mean",kappaAv,1.,4.);
  RooRealVar sigma("sigma","sigma",ekappaAv,0.,1.);
  RooRealVar alpha("alpha","alpha",6.,-10.,10.);
  RooRealVar n("n","n",30.,0.,60.);
  RooCBShape crystalball("crystalball","crystalball",kappa,mean,sigma,alpha,n);

  //Gaussian fit
  RooRealVar gmean("gmean","gmean",kappaAv,2.,2.3);
  RooRealVar gsigma("gsigma","gsigma",ekappaAv,0.,0.5);
  RooGaussian gausfit("gausfit","gausfit",gkappa,gmean,gsigma);

  kappa.setRange("kapparange",1.8,2.6);
  gkappa.setRange("gkapparange",2.,2.2);
  
  crystalball.fitTo(kappadata,RooFit::Range("kapparange"));
  RooPlot *CBhardnessplot = kappa.frame();
  CBhardnessplot->SetTitle("CB RooFit");
  kappadata.plotOn(CBhardnessplot);
  crystalball.plotOn(CBhardnessplot);

  gausfit.fitTo(kappadata,RooFit::Range("gkapparange"));
  RooPlot *ghardnessplot = gkappa.frame();
  ghardnessplot->SetTitle("Gaus RooFit");
  gkappadata.plotOn(ghardnessplot);
  gausfit.plotOn(ghardnessplot);

  //RooChi2Var CBchi2("CBchi2","chi2",crystalball, kappadata);
  
  TF1 *fitgaus = new TF1("fitgaus","gaus",1.9,2.5);
  hardness->Fit(fitgaus,"RN");
  TCanvas *can = new TCanvas("RooPlot","RooPlot",600,600);
  can->Divide(1,3);  
  can->cd(1);
  hardness->SetTitle("Gaus TF1 Fit");
  hardness->Draw();
  fitgaus->Draw("same");
  can->cd(2);
  CBhardnessplot->Draw();
  can->cd(3);
  ghardnessplot->Draw();
  can->SaveAs("Hardness_Error.root");
  
  //std::cout<<"CB chi^2 = "<<CBchi2.getVal()<<std::endl;
}
