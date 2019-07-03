#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "TGraphErrors.h"

struct Hardness
{
  double k;
  double ek;
  double a;
  double ea;
};

Hardness hardness(double fitparam, double efitparam)
{
  Hardness kappa;
  //Sensor parameters
  double l{0.5}; //p cm^2
  //double l{0.265}; //p cm^2
  double w{0.03}; //cm
  double alphan{3.99e-17}; //A cm^-1
  double ealphan{0.03e-17}; //A cm^-1

  double theta   = fitparam; //nA cm^2
  double etheta  = efitparam; //pol1 fit
  double alpha   = pow(10,-9)*theta/(l*l*w); //A cm^-1
  double ealpha  = pow(10,-9)*etheta/(l*l*w);
  double k   = alpha/alphan;
  double ek  = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);
  
  std::cout<<"hardness factor = "<<k<<" +/- "<<ek<<"\n";
  std::cout<<"relative error = "<<ek/k<<"\n\n";

  kappa.k=k;
  kappa.ek=ek;
  kappa.a=alpha;
  kappa.ea=ealpha;
  
  return kappa;
}

void Irradiated_Error_Analysis()
{
  ifstream MC40;
  std::string line{""};
  double x,y,ex,ey;
  std::vector<double> fluence,current,efluence,ecurrent;
  MC40.open("Isidre_results.txt");
  int i{0};
  if(MC40.good())
    {
      getline(MC40,line);
      while(true)
	{	  
	  MC40>>x>>y>>ex>>ey;
	  if(MC40.eof())break;
	  fluence.push_back(x);
	  current.push_back(y);
	  efluence.push_back(ex);
	  ecurrent.push_back(ey);
	  //std::cout<<fluence[i]<<"\t"<<current[i]<<std::endl;
	  ++i;
	}
    }
  else std::cout<<"Error opening file..."<<std::endl;
  MC40.close(); 

  double calibration = 112.67;
  double ec = pow(pow(0.55238,2) + pow(5.358,2),0.5);//4.8%

  //These change for other facilities
  //double ecalibration = ec/calibration;
  double ecalibration = 0.;
  //double enickel = 0.15;//15%
  double enickel = 0.04;

  TH1F*h_grad_stat=new TH1F("","",200, 0.,4.e-10);
  TH1F*h_grad_sys=new TH1F("","",200, 0.,4.e-10);
  TH1F*h_grad_sys_stat=new TH1F("","",200, 0.,4.e-10);
  //TF1* fit1 = new TF1("fit1","pol1",0,6e12);
  TF1* fit1 = new TF1("fit1","pol1",0,2e14);
  //TF1* fit1 = new TF1("fit1","pol1",0,8e13);
  fit1->SetParameters(0., 5e-11);
  fit1->FixParameter(0,0.);
  TRandom*rndm=new TRandom3(0);
  std::vector<double> fluenceIter;
  std::vector<double> currentIter;
  std::vector<double> dummy;
  int Ntrials = 300000;
  for(int i{0}; i<Ntrials; ++i)
    {
      double alphafluence = rndm->Gaus(1.,enickel);
      double alphacalibration = rndm->Gaus(1.,ecalibration);
      for(int n{0}; n<fluence.size(); ++n)
	{
	  fluenceIter.push_back(fluence[n]*alphafluence*alphacalibration);
	  currentIter.push_back(current[n]*rndm->Gaus(1.,ecurrent[n]));
	  dummy.push_back(0.);
	  //std::cout<<fluenceIter[n]<<"\t"<<currentIter[n]<<"\n";
	}
      TGraphErrors *g_stat = new TGraphErrors(fluence.size(),&(fluence[0]),&(current[0]),&(dummy[0]),&(ecurrent[0]));
      TGraphErrors *g_sys = new TGraphErrors(fluenceIter.size(),&(fluenceIter[0]),&(current[0]),&(dummy[0]),&(dummy[0]));
      TGraphErrors *g_sys_stat = new TGraphErrors(fluenceIter.size(),&(fluenceIter[0]),&(current[0]),&(dummy[0]),&(ecurrent[0]));
      g_stat->Fit(fit1,"SQRNE");
      h_grad_stat->Fill(fit1->GetParameter(1));
      g_sys->Fit(fit1,"SQRNE");
      h_grad_sys->Fill(fit1->GetParameter(1));
      g_sys_stat->Fit(fit1,"SQRNE");
      h_grad_sys_stat->Fill(fit1->GetParameter(1));
      //std::cout<<"fit "<<fit1->GetParameter(1)<<"\n";
      fluenceIter.clear();
      currentIter.clear();
      //dummy.clear();
    }
  h_grad_stat->GetXaxis()->SetTitle("Fit Gradient 24 MeV protons");
  h_grad_sys->GetXaxis()->SetTitle("Fit Gradient 24 MeV protons");
  h_grad_sys_stat->GetXaxis()->SetTitle("Fit Gradient 24 MeV protons");
  //TCanvas *canvas_stat = new TCanvas("fit_gradient_stat","fit_gradient_stat",600,600);
  //h_grad_stat->Draw();
  TCanvas *canvas_sys = new TCanvas("fit_gradient_sys","fit_gradient_sys",600,600);
  h_grad_sys->Draw();
  TCanvas *canvas_sys_stat = new TCanvas("fit_gradient_sys_stat","fit_gradient_sys_stat",600,600);
  h_grad_sys_stat->Draw();
  TCanvas *canvas_stat = new TCanvas("fit_gradient_stat","fit_gradient_stat",600,600);
  h_grad_stat->Draw();

  TGraphErrors *g_current = new TGraphErrors(fluence.size(),&(fluence[0]),&(current[0]),&(dummy[0]),&(ecurrent[0]));
  //TF1* fit = new TF1("fit","pol1",0,6e12);
  TF1* fit = new TF1("fit","pol1",0,2e14);
  fit->SetParameters(0.,5e-11);
  fit->FixParameter(0,0.);
  TCanvas *canvas = new TCanvas("stat","stat",600,600);
  g_current->Draw("AP");
  g_current->Fit(fit,"RN");
  fit->Draw("same");

  TGraphErrors *g_original = new TGraphErrors(fluence.size(),&(fluence[0]),&(current[0]),&(efluence[0]),&(ecurrent[0]));
  //TF1* fitoriginal = new TF1("fitoriginal","pol1",0,6e12);
  TF1* fitoriginal = new TF1("fitoriginal","pol1",0,2e14);
  //TF1* fitoriginal = new TF1("fitoriginal","pol1",0,8e13);
  fitoriginal->SetParameters(0.,5e-11);
  fitoriginal->FixParameter(0,0.);
  TCanvas *canvasoriginal = new TCanvas("original","original",600,600);
  g_original->Draw("AP");
  g_original->Fit(fitoriginal,"RN");
  fitoriginal->Draw("same");
  
  Hardness kappa1;
  Hardness kappa2;
  Hardness kappa3;
  Hardness kappa4;
  Hardness kappa5;
     
  std::cout<<"(original) fit equation:  Delta I = ("<<fitoriginal->GetParameter(1)<<" +/- "<<fitoriginal->GetParError(1)<<")*fluence"<<std::endl;
  std::cout<<"(original) relative error = "<<fitoriginal->GetParError(1)/fitoriginal->GetParameter(1)<<std::endl;
  
  double fitparam1 = fitoriginal->GetParameter(1);
  double efitparam1 = fitoriginal->GetParError(1);
  kappa1 = hardness(fitparam1,efitparam1);
  
  std::cout<<"(stat) fit equation:  Delta I = ("<<fit->GetParameter(1)<<" +/- "<<fit->GetParError(1)<<")*fluence"<<std::endl;
  std::cout<<"(stat) relative error = "<<fit->GetParError(1)/fit->GetParameter(1)<<std::endl;

  double fitparam2 = fit->GetParameter(1);
  double efitparam2 = fit->GetParError(1);
  kappa2 = hardness(fitparam2,efitparam2);
  
  std::cout<<"(sys) fit equation:  Delta I = ("<<h_grad_sys->GetMean()<<" +/- "<<h_grad_sys->GetStdDev()<<")*fluence"<<std::endl;
  std::cout<<"(sys) relative error = "<<h_grad_sys->GetStdDev()/h_grad_sys->GetMean()<<std::endl;

  double fitparam3 = h_grad_sys->GetMean();
  double efitparam3 = h_grad_sys->GetStdDev();
  kappa3 = hardness(fitparam3,efitparam3);

  std::cout<<"(sys + stat) fit equation:  Delta I = ("<<h_grad_sys_stat->GetMean()<<" +/- "<<h_grad_sys_stat->GetStdDev()<<")*fluence"<<std::endl;
  std::cout<<"(sys + stat) relative error = "<<h_grad_sys_stat->GetStdDev()/h_grad_sys_stat->GetMean()<<std::endl;

  double fitparam4 = h_grad_sys_stat->GetMean();
  double efitparam4 = h_grad_sys_stat->GetStdDev();
  kappa4 = hardness(fitparam4,efitparam4);

  std::cout<<"(statIter) fit equation:  Delta I = ("<<h_grad_stat->GetMean()<<" +/- "<<h_grad_stat->GetStdDev()<<")*fluence"<<std::endl;
  std::cout<<"(statIter) relative error = "<<h_grad_stat->GetStdDev()/h_grad_stat->GetMean()<<std::endl;

  double fitparam5 = h_grad_stat->GetMean();
  double efitparam5 = h_grad_stat->GetStdDev();
  kappa5 = hardness(fitparam5,efitparam5);

  std::cout<<"Overall: alpha = "<<kappa1.a<<" +/ - "<<kappa2.ea*kappa1.a/kappa2.a<<" +/- "<<kappa3.ea*kappa1.a/kappa3.a<<std::endl;
  std::cout<<"Combined errors: alpha = "<<kappa1.a<<" +/ - "<<kappa2.ea*kappa1.a/kappa2.a+kappa3.ea*kappa1.a/kappa3.a<<std::endl;
  
  std::cout<<"Overall: k = "<<kappa1.k<<" +/ - "<<kappa2.ek*kappa1.k/kappa2.k<<" +/- "<<kappa3.ek*kappa1.k/kappa3.k<<std::endl;
  std::cout<<"Combined errors: k = "<<kappa1.k<<" +/ - "<<kappa2.ek*kappa1.k/kappa2.k+kappa3.ek*kappa1.k/kappa3.k<<std::endl;
}
