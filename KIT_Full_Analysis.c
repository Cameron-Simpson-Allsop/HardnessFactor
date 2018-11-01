#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"

//Define 'Current' structure
struct Current{
  double Mean_current{0.};
  double eMean_current{0.};
  double Fluence{0.};
  double eFluence{0.};
};

Current Extract_Current(TString txtName, double voltage, double minFit, double maxFit, double fluence, double efluence)
{
  //Plots raw data
  TGraphErrors *g = new TGraphErrors(txtName);
  g->GetXaxis()->SetTitle("Voltage(-V)");
  g->GetYaxis()->SetTitle("Leakage Current (-nA)");
  g->GetYaxis()->SetTitleOffset(1.45);
  g->SetTitle("");

  //Fits raw data
  TF1* fit = new TF1("fit","pol1", minFit, maxFit);
  fit->SetLineColor(kRed);
  g->Fit(fit,"RN");

  //Draws raw data with fit
  TCanvas* canvas = new TCanvas(txtName,txtName);
    g->Draw("AP");
    fit->Draw("same");

  //Extracts leakage current and fluence measurements
  double p0g = fit->GetParameter(0);
  double p0ge = fit->GetParError(0);
  double p1g = fit->GetParameter(1);
  double p1ge = fit->GetParError(1);
  Current I;
  I.Mean_current = abs(p1g*voltage+p0g);
  I.eMean_current = pow(voltage*voltage*p1ge*p1ge + p0ge*p0ge + p1g*p1g*0.05*0.05,0.5);
  I.Fluence = fluence;
  I.eFluence = efluence;

  return I;
}

void Extract_Hardness_Factor(std::vector<Current> Data)
{
  //Put data from vector into a plottable format
  std::vector<double> x,y,ex,ey;
  for(unsigned int i{0}; i<Data.size(); i++)
    {
      x.push_back(Data[i].Fluence);
      y.push_back(Data[i].Mean_current);
      ex.push_back(Data[i].eFluence);
      ey.push_back(Data[i].eMean_current);
    }
  
  //Plots data
  TGraphErrors *g = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(3);
  g->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
  g->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
  g->GetXaxis()->SetRangeUser(-0.02e15,0.6e15);
  g->GetYaxis()->SetRangeUser(-2e3,70e3);
  g->SetTitle("");

  //Fits data
  TF1* fit = new TF1("fit","pol1",0,5.5e14);
  fit->SetParameter(1,1e-12);
  fit->SetParameter(0,0);
  fit->SetLineColor(kBlack);
  fit->SetLineStyle(9);
  
  TF1* fit1 = new TF1("fit1","[0]*x",0,5.5e14);
  fit1->SetParameter(0,1e-12);
  fit1->SetLineColor(kBlue);
  
  g->Fit(fit,"RN");
  //g->Fit(fit1,"RN");

  TLegend* leg = new TLegend(0.2, 0.75, 0.4, 0.85);
  leg->AddEntry(fit,"pol1 fit","l");
  leg->AddEntry(fit1,"[0]*x fit","l");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  
  //Draws plot and fit
  TCanvas *Fluence = new TCanvas("KIT Current v Fluence","KIT Current v Fluence",600,700);
  Fluence->SetRightMargin(1);
  Fluence->SetTopMargin(1);
  TGaxis::SetMaxDigits(3);
  g->Draw("AP");
  fit->Draw("same");
  //fit1->Draw("same");
  //leg->Draw();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.DrawLatex(0.49,0.2,"#kappa = 1.97 #pm 0.21");
  //latex.DrawLatex(0.49,0.25,"#kappa_{[0]*x fit} = 2.859 #pm 0.286");
  gPad->RedrawAxis();

  //Sensor parameters
  double l{0.265}; //p cm^2
  double w{0.03}; //cm
  double alphan{3.99e-17}; //A cm^-1
  double ealphan{0.03e-17}; //A cm^-1

  //Calculates hardness factor from fit
  double theta = fit->GetParameter(1); //nA cm^2
  double etheta = fit->GetParError(1); //pol1 fit
  double theta1 = fit1->GetParameter(0); //nA cm^2
  double etheta1 = fit1->GetParError(0); //force 0 fit
  double alpha = pow(10,-9)*theta/(l*l*w); //A cm^-1
  double ealpha = pow(10,-9)*etheta/(l*l*w);
  double alpha1 = pow(10,-9)*theta1/(l*l*w); //A cm^-1
  double ealpha1 = pow(10,-9)*etheta1/(l*l*w);
  double k = alpha/alphan;
  double ek = pow(pow(ealpha/alphan,2)+pow((alpha*ealphan)/(alphan*alphan),2),0.5);
  double k1 = alpha1/alphan;
  double ek1 = pow(pow(ealpha1/alphan,2)+pow((alpha1*ealphan)/(alphan*alphan),2),0.5);

  std::cout << "KIT Alpha (pol1) = " << alpha << " +/- " << ealpha << std::endl;
  std::cout << "KIT Hardness Factor (pol1) = " << k << " +/- " << ek << std::endl;

 //std::cout << "KIT Alpha (force 0) = " << alpha1 << " +/- " << ealpha1 << std::endl;
 //std::cout << "KIT Hardness Factor (force 0) = " << k1 << " +/- " << ek1 << std::endl;

}

void Evaluate_KIT()
{
  double KIT_sys_fluence_error = 27./170.; //15.9%
  std::vector<Current> I_KIT;

  //Irradiated variables
  std::vector<TString> filenamesIrr = {"KIT_1_s_Anneal_80mins_1902.txt","KIT_2_s_Anneal_80mins_1902.txt","KIT_3_Anneal_80mins_1902.txt","KIT_4_s_Anneal_80mins_1902.txt"};
  std::vector<double> fluencesIrr = {5.0e12, 5.0e13, 1.5e14, 5.0e14};//p cm^-2
  std::vector<double> efluencesIrr = {fluencesIrr[0]*KIT_sys_fluence_error,fluencesIrr[1]*KIT_sys_fluence_error,fluencesIrr[2]*KIT_sys_fluence_error,fluencesIrr[3]*KIT_sys_fluence_error};
  double minFitIrr = -100.;
  double maxFitIrr = -75.;

  double voltage = -91.;//V

  //Extract leakage current and fluence measurements and put data into a vector
  for(unsigned int i{0}; i<filenamesIrr.size(); i++)
    {

      Current I_1 = Extract_Current(filenamesIrr[i],voltage,minFitIrr,maxFitIrr,fluencesIrr[i],efluencesIrr[i]);
      
      I_KIT.push_back(I_1);
  
      std::cout << "Current = " << I_1.Mean_current << " +/- " << I_1.eMean_current << " nA \n" << "Fluence = " << I_1.Fluence << " +/- " << I_1.eFluence << " p/cm^2 \n";
    }

  //Extract current related damage rate and  hardness factor value
  Extract_Hardness_Factor(I_KIT);
}

void KIT_Full_Analysis()
{
  rootlogonATLAS();
  Evaluate_KIT();
}

