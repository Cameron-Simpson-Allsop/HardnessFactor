#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"

void IRRAD_Isidre_Combined()
{
  rootlogonATLAS();
  TGraphErrors *Isidre = new TGraphErrors("Isidre_Hardness_Factor_Data.txt");
  Isidre->SetMarkerStyle(20);
  Isidre->SetMarkerSize(2);
  TGraphErrors *IRRAD = new TGraphErrors("IRRAD_Hardness_Factor_Data.txt");
  IRRAD->SetMarkerStyle(21);
  Isidre->SetMarkerSize(2);
  
  TF1* fit = new TF1("fit","pol1",0,10.e13);
  fit->SetParameter(1,1.e-12);
  fit->SetParameter(0,0);
  fit->SetLineColor(kBlue);
  
  TF1* fit1 = new TF1("fit1","[0]*x",0,5e13);
  fit1->SetParameter(0,1e-12);
  fit1->SetLineColor(kRed);

  IRRAD->Fit(fit,"RN");
  IRRAD->Fit(fit1,"RN");
  Isidre->Fit(fit,"RN");
  Isidre->Fit(fit1,"RN");
   
  TGaxis::SetMaxDigits(2);
 
  //TCanvas *combined = new TCanvas("combined","combined",600,600);
  //fit->Draw("same");
  //fit1->Draw("same");
  
  //Isidre Sensor parameters
  double li{0.5}; //p cm^2
  double wi{0.03}; //cm
  //IRRAD Sensor parameters
  double l{0.265}; //p cm^2
  double w{0.03}; //cm
  
  double alphan{3.99e-17}; //A cm^-1
  double ealphan{0.03e-17}; //A cm^-1
  double theta = fit->GetParameter(1); //nA cm^2
  double etheta = fit->GetParError(1); //pol1 fit
  double theta1 = fit1->GetParameter(0); //nA cm^2
  double etheta1 = fit1->GetParError(0); //force 0 fit
  
  //Calculates hardness factor from fit (IRRAD)  
  double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1
  double ealpha = pow(10,-9)*etheta/(l*l*w);
  double alpha1 = pow(10,-9)*theta1/(l*l*w); //A cm^-1
  double ealpha1 = pow(10,-9)*etheta1/(l*l*w);
  double k = alpha/alphan;
  double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);
  double k1 = alpha1/alphan;
  double ek1 = pow(pow(ealpha1/alphan,2)+pow((alpha1*ealphan)/(alphan*alphan),2),0.5);

  //Calculates hardness factor from fit (Isidre)  
  double alphai = pow(10,-9)*theta/(li*li*wi); //A cm^-1
  double ealphai = pow(10,-9)*etheta/(li*li*wi);
  double alpha1i = pow(10,-9)*theta1/(li*li*wi); //A cm^-1
  double ealpha1i = pow(10,-9)*etheta1/(li*li*wi);
  double ki = alpha/alphan;
  double eki = pow(pow(ealphai/alphan,2)+pow((alphai*ealphan)/(alphan*alphan),2),0.5);
  double k1i = alpha1i/alphan;
  double ek1i = pow(pow(ealpha1i/alphan,2)+pow((alpha1i*ealphan)/(alphan*alphan),2),0.5);
  
  std::cout << "IRRAD Alpha (pol1) = " << alpha << " +/- " << ealpha << std::endl;
  std::cout << "IRRAD Hardness Factor (pol1) = " << k << " +/- " << ek << std::endl;

  std::cout << "IRRAD Alpha (force 0) = " << alpha1 << " +/- " << ealpha1 << std::endl;
  std::cout << "IRRAD Hardness Factor (force 0) = " << k1 << " +/- " << ek1 << std::endl;

  std::cout << "Isidre Alpha (pol1) = " << alphai << " +/- " << ealphai << std::endl;
  std::cout << "Isidre Hardness Factor (pol1) = " << ki << " +/- " << eki << std::endl;

  std::cout << "Isidre Alpha (force 0) = " << alpha1i << " +/- " << ealpha1i << std::endl;
  std::cout << "Isidre Hardness Factor (force 0) = " << k1i << " +/- " << ek1i << std::endl;


}
