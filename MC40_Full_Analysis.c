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

//Calibration ratio and systematic fluence error
double c = 112.67;
double error_c = pow(pow(0.55238,2) + pow(5.358,2),0.5); //propagated error from MAESTRO + range of values/2  UPDATE THIS
double sys_fluence_error = 27./170.; //15.9%


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
  /*TCanvas* canvas = new TCanvas(txtName,txtName);
  g->Draw("AP");
  fit->Draw("same");*/

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
  g->GetYaxis()->SetRangeUser(0,1e3);
  g->GetXaxis()->SetRangeUser(0,6e12);
  g->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
  g->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
  g->SetTitle("");
  TGaxis::SetMaxDigits(3);

  //Fits data with pol1 (cuts out highest fluence)
  TF1* fit = new TF1("fit","pol1",0,6e12);
  fit->SetParameter(1,5e-11);
  fit->SetParameter(0,0);
  fit->SetLineColor(kBlue);
  
  //Fits data with [0]*x (cuts out highest fluence)
  TF1* fit1 = new TF1("fit1","[0]*x",0,6e12);
  fit1->SetParameter(0,5e-11);
  fit1->SetLineColor(kBlack);
  fit1->SetLineStyle(9);

  g->Fit(fit,"RN");
  g->Fit(fit1,"RN");
   
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
  TCanvas *Fluence = new TCanvas("MC40 Current v Fluence","MC40 Current v Fluence",600,700);
  Fluence->SetRightMargin(1);
  Fluence->SetTopMargin(1);
  TGaxis::SetMaxDigits(3);
  g->Draw("AP");
  //fit->Draw("same");
  fit1->Draw("same");
  //leg->Draw();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  //latex.DrawLatex(0.49,0.2,"#kappa_{pol1 fit} = 2.222 #pm 0.110");
  latex.DrawLatex(0.49,0.25,"#kappa = 2.20 #pm 0.08");
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

  std::cout << "MC40 Alpha (pol1) = " << alpha << " +/- " << ealpha << std::endl;
  std::cout << "MC40 Hardness Factor (pol1) = " << k << " +/- " << ek << std::endl;

  std::cout << "MC40 Alpha (force 0) = " << alpha1 << " +/- " << ealpha1 << std::endl;
  std::cout << "MC40 Hardness Factor (force 0) = " << k1 << " +/- " << ek1 << std::endl;

  std::cout << "pol1 fit equation: y = (" << theta << " +/- " << etheta << ")x + (" << fit->GetParameter(0) << " +/- " << fit->GetParError(0) << ")" << std::endl;
  std::cout << "force 0 fit equation: y = (" << theta1 << " +/- " << etheta1 << ")x" << std::endl;
  
}

//Function to calculate error on scaled fluence
double calc(double fluence, double efluence)
{
  return pow(pow(efluence/c,2.)+pow((fluence*error_c)/(c*c),2.) + pow(fluence*sys_fluence_error,2.),0.5);
}

void Evaluate_MC40()
{
  //Defines vector and states MC40 cylcotron's systematic fluence error multiplier
  std::vector<Current> I_MC40_warm;
  std::vector<Current> I_MC40_cold;
  std::vector<Current> I_MC40_combined;
  
  //Warm Irradiated filenames and fluences
  std::vector<TString> filenamesIrr_warm = {"Diode26_IV_irradiated_0603.txt","Diode28_IV_irradiated_0603.txt","Diode30_IV_irradiated_0603.txt","Diode32_IV_irradiated_0603.txt","Diode34_IV_irradiated_0603.txt","Diode36_IV_irradiated_0603.txt","Diode25_IV_irradiated_0603.txt","Diode27_IV_irradiated_0603.txt","Diode29_IV_irradiated_0603.txt","Diode31_IV_irradiated_0603.txt","Diode33_IV_irradiated_0603.txt","Diode35_IV_irradiated_0603.txt"};
  std::vector<double> fluencesIrr_warm = {6.52E+13/c, 1.87E+14/c, 2.92e14/c, 3.61e14/c, 5.34e14/c, 3.82e14/c, 6.52E+13/c, 1.87E+14/c, 2.92e14/c, 3.61e14/c, 5.34e14/c, 3.82e14/c};//p cm^-2
  std::vector<double> efluencesIrr_warm = {calc(fluencesIrr_warm[0],4.30E+12),calc(fluencesIrr_warm[1],5.00E+12),calc(fluencesIrr_warm[2],0.09e14),calc(fluencesIrr_warm[3],0.11e14),calc(fluencesIrr_warm[4],0.12e14),calc(fluencesIrr_warm[5],0.13e14),calc(fluencesIrr_warm[6],4.30E+12),calc(fluencesIrr_warm[7],5.00E+12),calc(fluencesIrr_warm[8],0.09e14),calc(fluencesIrr_warm[9],0.11e14),calc(fluencesIrr_warm[10],0.12e14),calc(fluencesIrr_warm[11],0.13e14)}; //numbers are the error on the uncalibrated fluence
  
  //Cold Irradiated filenames and fluences
  std::vector<TString> filenamesIrr_cold = {"Diode38_IV_irradiated_0603.txt","Diode40_IV_irradiated_0603.txt","Diode42_IV_irradiated_0603.txt","Diode44_IV_irradiated_0603.txt","Diode46_IV_irradiated_0603.txt","Diode48_IV_irradiated_0603.txt","Diode37_IV_irradiated_0603.txt","Diode39_IV_irradiated_0603.txt","Diode41_IV_irradiated_0603.txt","Diode43_IV_irradiated_0603.txt","Diode45_IV_irradiated_0603.txt","Diode47_IV_irradiated_0603.txt"};
  std::vector<double> fluencesIrr_cold = {1.58e15/c, 2.81E+14/c, 7.51e13/c, 1.13e14/c, 4.88e13/c, 1.76e13/c, 1.58e15/c, 2.81E+14/c, 7.51e13/c, 1.13e14/c, 4.88e13/c, 1.76e13/c};//p cm^-2
  std::vector<double> efluencesIrr_cold = {calc(fluencesIrr_cold[0],0.02e15),calc(fluencesIrr_cold[1],0.08E+14),calc(fluencesIrr_cold[2],0.41e13),calc(fluencesIrr_cold[3],0.04e14),calc(fluencesIrr_cold[4],0.36e13),calc(fluencesIrr_cold[5],0.27e13),calc(fluencesIrr_cold[6],0.02e15),calc(fluencesIrr_cold[7],0.08E+14),calc(fluencesIrr_cold[8],0.41e13),calc(fluencesIrr_cold[9],0.04e14),calc(fluencesIrr_cold[10],0.36e13),calc(fluencesIrr_cold[11],0.27e13)};//numbers are the error on the uncalibrated fluence
  
  //Combined Irradiated filenames and fluences
  std::vector<TString> filenamesIrr_combined = {"Diode26_IV_irradiated_0603.txt","Diode28_IV_irradiated_0603.txt","Diode30_IV_irradiated_0603.txt","Diode32_IV_irradiated_0603.txt","Diode34_IV_irradiated_0603.txt","Diode36_IV_irradiated_0603.txt","Diode25_IV_irradiated_0603.txt","Diode27_IV_irradiated_0603.txt","Diode29_IV_irradiated_0603.txt","Diode31_IV_irradiated_0603.txt","Diode33_IV_irradiated_0603.txt","Diode35_IV_irradiated_0603.txt","Diode38_IV_irradiated_0603.txt","Diode40_IV_irradiated_0603.txt","Diode42_IV_irradiated_0603.txt","Diode44_IV_irradiated_0603.txt","Diode46_IV_irradiated_0603.txt","Diode48_IV_irradiated_0603.txt","Diode37_IV_irradiated_0603.txt","Diode39_IV_irradiated_0603.txt","Diode41_IV_irradiated_0603.txt","Diode43_IV_irradiated_0603.txt","Diode45_IV_irradiated_0603.txt","Diode47_IV_irradiated_0603.txt"};
  std::vector<double> fluencesIrr_combined = {6.52E+13/c, 1.87E+14/c, 2.92e14/c, 3.61e14/c, 5.34e14/c, 3.82e14/c, 6.52E+13/c, 1.87E+14/c, 2.92e14/c, 3.61e14/c, 5.34e14/c, 3.82e14/c, 1.58e15/c, 2.81E+14/c, 7.51e13/c, 1.13e14/c, 4.88e13/c, 1.76e13/c, 1.58e15/c, 2.81E+14/c, 7.51e13/c, 1.13e14/c, 4.88e13/c, 1.76e13/c};//p cm^-2
  std::vector<double> efluencesIrr_combined = {calc(fluencesIrr_warm[0],4.30E+12),calc(fluencesIrr_warm[1],5.00E+12),calc(fluencesIrr_warm[2],0.09e14),calc(fluencesIrr_warm[3],0.11e14),calc(fluencesIrr_warm[4],0.12e14),calc(fluencesIrr_warm[5],0.13e14),calc(fluencesIrr_warm[6],4.30E+12),calc(fluencesIrr_warm[7],5.00E+12),calc(fluencesIrr_warm[8],0.09e14),calc(fluencesIrr_warm[9],0.11e14),calc(fluencesIrr_warm[10],0.12e14),calc(fluencesIrr_warm[11],0.13e14),calc(fluencesIrr_cold[0],0.02e15),calc(fluencesIrr_cold[1],0.08E+14),calc(fluencesIrr_cold[2],0.41e13),calc(fluencesIrr_cold[3],0.04e14),calc(fluencesIrr_cold[4],0.36e13),calc(fluencesIrr_cold[5],0.27e13),calc(fluencesIrr_cold[6],0.02e15),calc(fluencesIrr_cold[7],0.08E+14),calc(fluencesIrr_cold[8],0.41e13),calc(fluencesIrr_cold[9],0.04e14),calc(fluencesIrr_cold[10],0.36e13),calc(fluencesIrr_cold[11],0.27e13)};
  
  //Warm Unirradiated filenames
  std::vector<TString> filenames_warm = {"Diode26_IV_2602.txt","Diode28_IV_2602.txt","Diode30_IV_2602.txt","Diode32_IV_2602.txt","Diode34_IV_2602.txt","Diode36_IV_2602.txt","Diode25_IV_2602.txt","Diode27_IV_2602.txt","Diode29_IV_2602.txt","Diode31_IV_2602.txt","Diode33_IV_2602.txt","Diode35_IV_2602.txt"};
  //Cold Unirradiated filenames
  std::vector<TString> filenames_cold = {"Diode38_IV_2602.txt","Diode40_IV_2802.txt","Diode42_IV_2802.txt","Diode44_IV_2802.txt","Diode46_IV_2802.txt","Diode48_IV_2802.txt","Diode37_IV_2602.txt","Diode39_IV_2602.txt","Diode41_IV_2802.txt","Diode43_IV_2802.txt","Diode45_IV_2802.txt","Diode47_IV_2802.txt"};
  //Combined Unirradiated filenames
  std::vector<TString> filenames_combined = {"Diode26_IV_2602.txt","Diode28_IV_2602.txt","Diode30_IV_2602.txt","Diode32_IV_2602.txt","Diode34_IV_2602.txt","Diode36_IV_2602.txt","Diode25_IV_2602.txt","Diode27_IV_2602.txt","Diode29_IV_2602.txt","Diode31_IV_2602.txt","Diode33_IV_2602.txt","Diode35_IV_2602.txt","Diode38_IV_2602.txt","Diode40_IV_2802.txt","Diode42_IV_2802.txt","Diode44_IV_2802.txt","Diode46_IV_2802.txt","Diode48_IV_2802.txt","Diode37_IV_2602.txt","Diode39_IV_2602.txt","Diode41_IV_2802.txt","Diode43_IV_2802.txt","Diode45_IV_2802.txt","Diode47_IV_2802.txt"};

  //Irradiated variables
  double minFitIrr = -100.;
  double maxFitIrr = -75.;
  
  //Unirradiated variables
  double fluences = 0.;//p cm^-2
  double efluences = 0.;
  double minFit = -110.;
  double maxFit = -40.;

  double voltage = -91.;//V
  
  //Extract leakage current and fluence measurements and calculate change in leakage current for each warm sensor. Then put data into a vector
  for(unsigned int i{0}; i<filenamesIrr_warm.size(); i++)
    {

      Current I_1w = Extract_Current(filenamesIrr_warm[i],voltage,minFitIrr,maxFitIrr,fluencesIrr_warm[i],efluencesIrr_warm[i]);
      Current I_2w = Extract_Current(filenames_warm[i],voltage,minFit,maxFit,fluences,efluences);
  
      Current I_3w;
      I_3w.Mean_current = I_1w.Mean_current - I_2w.Mean_current;
      I_3w.eMean_current = pow(pow(I_1w.eMean_current,2) + pow(I_2w.eMean_current,2),0.5);
      I_3w.Fluence = I_1w.Fluence;
      I_3w.eFluence = I_1w.eFluence;  
      I_MC40_warm.push_back(I_3w);
  
      std::cout << "Current = " << I_3w.Mean_current << " +/- " << I_3w.eMean_current << " nA \n" << "Fluence = " << I_3w.Fluence << " +/- " << I_3w.eFluence << " p/cm^2 \n";
    }
  
  //Extract leakage current and fluence measurements and calculate change in leakage current for each cold sensor. Then put data into a vector
  for(unsigned int i{0}; i<filenames_cold.size(); i++)
    {

      Current I_1c = Extract_Current(filenamesIrr_cold[i],voltage,minFitIrr,maxFitIrr,fluencesIrr_cold[i],efluencesIrr_cold[i]);
      Current I_2c = Extract_Current(filenames_cold[i],voltage,minFit,maxFit,fluences,efluences);
  
      Current I_3c;
      I_3c.Mean_current = I_1c.Mean_current - I_2c.Mean_current;
      I_3c.eMean_current = pow(pow(I_1c.eMean_current,2) + pow(I_2c.eMean_current,2),0.5);
      I_3c.Fluence = I_1c.Fluence;
      I_3c.eFluence = I_1c.eFluence;  
      I_MC40_cold.push_back(I_3c);
  
      std::cout << "Current = " << I_3c.Mean_current << " +/- " << I_3c.eMean_current << " nA \n" << "Fluence = " << I_3c.Fluence << " +/- " << I_3c.eFluence << " p/cm^2 \n";
    }

  //Extract leakage current and fluence measurements and calculate change in leakage current for all sensors. Then put data into a vector
  for(unsigned int i{0}; i<filenames_combined.size(); i++)
    {

      Current I_1 = Extract_Current(filenamesIrr_combined[i],voltage,minFitIrr,maxFitIrr,fluencesIrr_combined[i],efluencesIrr_combined[i]);
      Current I_2 = Extract_Current(filenames_combined[i],voltage,minFit,maxFit,fluences,efluences);
  
      Current I_3;
      I_3.Mean_current = I_1.Mean_current - I_2.Mean_current;
      I_3.eMean_current = pow(pow(I_1.eMean_current,2) + pow(I_2.eMean_current,2),0.5);
      I_3.Fluence = I_1.Fluence;
      I_3.eFluence = I_1.eFluence;  
      I_MC40_combined.push_back(I_3);
  
      std::cout << "Current = " << I_3.Mean_current << " +/- " << I_3.eMean_current << " nA \n" << "Fluence = " << I_3.Fluence << " +/- " << I_3.eFluence << " p/cm^2 \n";
    }
  
  //Extract current related damage rate and  hardness factor value for each data set. Uncomment desired set
  //Extract_Hardness_Factor(I_MC40_warm);
  //Extract_Hardness_Factor(I_MC40_cold);
  Extract_Hardness_Factor(I_MC40_combined);

}

void MC40_Full_Analysis()
{
  rootlogonATLAS();
  Evaluate_MC40();
}
