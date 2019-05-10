#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

struct Data
{
  std::vector<double> fluences;
  std::vector<double> currents;
  std::vector<double> efluences;
  std::vector<double> ecurrents;
};

void MC40_Errors()
{
  Data measured;
  ifstream MC40;
  std::string line{""};
  double x,y,ex,ey;
  std::vector<double> dummy, fluenceIter, currentIter;
  MC40.open("MC40_results.txt");
  int i{0};
  if(MC40.good())
    {
      getline(MC40,line);
      while(true)
	{	  
	  MC40>>x>>y>>ex>>ey;
	  if(MC40.eof())break;
	  measured.fluences.push_back(x);
	  measured.currents.push_back(y);
	  measured.efluences.push_back(ex);
	  measured.ecurrents.push_back(ey);
	  dummy.push_back(0.);
	  ++i;
	}
    }
  else std::cout<<"Error opening file..."<<std::endl;
  MC40.close();

  TF1* fit1 = new TF1("fit1","pol1",0,6e12);
  fit1->SetParameters(0., 5e-11);
  fit1->FixParameter(0,0.);
  TRandom*rndm=new TRandom3(0);
  TH1F*hres=new TH1F("hres","",200, 0.,4);
  
  for(int iIter=0;iIter<50000;iIter++)
    {
      // correlated fluence uncertainties
      // uncorrelated current uncertainties
      double alphaFluence = rndm->Gaus(1.,0.17);
      for(unsigned int k=0;k<measured.fluences.size();k++)
	{
	  fluenceIter.push_back(measured.fluences[k]*alphaFluence);
	  currentIter.push_back(measured.currents[k]*rndm->Gaus(1.,measured.ecurrents[k]/measured.currents[k]));
	}

      TGraphErrors *g = new TGraphErrors(fluenceIter.size(),
					 &(fluenceIter[0]), 
					 &(currentIter[0]), 
					 &(dummy[0]),
					 &(dummy[0]));

      TFitResultPtr result=g->Fit(fit1,"SQRNE");
      //std::cout<< fit1->GetParameter(1)<<std::endl;
      hres->Fill(fit1->GetParameter(1)*1.e10);
      //result->Print();
      delete g;
      fluenceIter.clear();
      currentIter.clear();
    }
  TCanvas*c=new TCanvas("c","Fit_Gradient",600,600);
  hres->GetXaxis()->SetTitle("Fit Gradient 25 MeV protons");
  hres->Draw();
  std::cout<<"Fit equation: y = ("<<hres->GetMean()<<" +/- "<<hres->GetStdDev()<<")e-10*x"<<std::endl;
  double relerror = hres->GetStdDev()/hres->GetMean();
  std::cout<<"Relative fit error due to correlation = "<<relerror<<std::endl;

  //Sensor parameters
  double l{0.265}; //p cm^2
  double w{0.03}; //cm
  double alphan{3.99e-17}; //A cm^-1
  double ealphan{0.03e-17}; //A cm^-1

  TGraphErrors *graph = new TGraphErrors(measured.fluences.size(),&(measured.fluences[0]),&(measured.currents[0]),&(measured.efluences[0]),&(measured.ecurrents[0]));
  graph->Fit(fit1,"RN");

  TH1F*kappa=new TH1F("hardness","",100, 1.,3.9);
  for(int i{0}; i<100000; ++i)
    {
      double theta,alpha,k,ek;
      theta = fit1->GetParameter(1)*rndm->Gaus(1.,relerror);//nA cm^2
      alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1
      k = alpha/alphan;
      kappa->Fill(k);
    }
  TCanvas *can = new TCanvas("hardness","hardness factor",600,600);
  kappa->GetXaxis()->SetTitle("Hardness Factor (MC40 25MeV)");
  kappa->Draw();
}
