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
double error_c = pow(pow(0.55238,2) + pow(5.358,2),0.5); //propagated error from MAESTRO + range of values/2
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
  latex.DrawLatex(0.55,0.25,"#kappa = 2.21 #pm 0.08");
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
  std::vector<Current> I_MC40_combined;
 
  //Combined Irradiated filenames and fluences
  std::vector<double> fluencesIrr_combined = {5.78681e+11,5.78681e+11,1.65971e+12,1.65971e+12,2.59164e+12,2.59164e+12,3.20405e+12,3.20405e+12,4.7395e+12,4.7395e+12,3.39043e+12,3.39043e+12,1.40233e+13,1.40233e+13,2.49401e+12,2.49401e+12,6.66548e+11,6.66548e+11,1.00293e+12,1.00293e+12,4.33123e+11,4.33123e+11,1.56208e+11,1.56208e+11};
  
  std::vector<TString> filenamesIrr_combined = {"Diode25_IV_irradiated_0603.txt","Diode26_IV_irradiated_0603.txt","Diode27_IV_irradiated_0603.txt","Diode28_IV_irradiated_0603.txt","Diode29_IV_irradiated_0603.txt","Diode30_IV_irradiated_0603.txt","Diode31_IV_irradiated_0603.txt","Diode32_IV_irradiated_0603.txt","Diode33_IV_irradiated_0603.txt","Diode34_IV_irradiated_0603.txt","Diode35_IV_irradiated_0603.txt","Diode36_IV_irradiated_0603.txt","Diode37_IV_irradiated_0603.txt","Diode38_IV_irradiated_0603.txt","Diode39_IV_irradiated_0603.txt","Diode40_IV_irradiated_0603.txt","Diode41_IV_irradiated_0603.txt","Diode42_IV_irradiated_0603.txt","Diode43_IV_irradiated_0603.txt","Diode44_IV_irradiated_0603.txt","Diode45_IV_irradiated_0603.txt","Diode46_IV_irradiated_0603.txt","Diode47_IV_irradiated_0603.txt","Diode48_IV_irradiated_0603.txt"};  

  std::vector<double> efluencesIrr_combined = {9.95174e+10,9.95174e+10,2.67312e+11,2.67312e+11,4.19294e+11,4.19294e+11,5.18161e+11,5.18161e+11,7.60245e+11,7.60245e+11,5.50705e+11,5.50705e+11,2.23429e+12,2.23429e+12,4.02422e+11,4.02422e+11,1.11944e+11,1.11944e+11,1.63198e+11,1.63198e+11,7.58488e+10,7.58488e+10,3.44932e+10,3.44932e+10};
  
  std::vector<TString> filenames_combined = {"Diode25_IV_2602.txt","Diode26_IV_2602.txt","Diode27_IV_2602.txt","Diode28_IV_2602.txt","Diode29_IV_2602.txt","Diode30_IV_2602.txt","Diode31_IV_2602.txt","Diode32_IV_2602.txt","Diode33_IV_2602.txt","Diode34_IV_2602.txt","Diode35_IV_2602.txt","Diode36_IV_2602.txt","Diode37_IV_2602.txt","Diode38_IV_2602.txt","Diode39_IV_2602.txt","Diode40_IV_2802.txt","Diode41_IV_2802.txt","Diode42_IV_2802.txt","Diode43_IV_2802.txt","Diode44_IV_2802.txt","Diode45_IV_2802.txt","Diode46_IV_2802.txt","Diode47_IV_2802.txt","Diode48_IV_2802.txt"};

  //Irradiated variables
  double minFitIrr = -115.;
  double maxFitIrr = -65.;
  
  //Unirradiated variables
  double fluences = 0.;//p cm^-2
  double efluences = 0.;
  double minFit = -115.;
  double maxFit = -40.;

  ifstream maxdeps;
  maxdeps.open("C-V/MaxDep_vs_Fluence.txt");
  if(!maxdeps.good())
    {
      std::cout << "'MaxDep_vs_Fluence.txt' not found" << std::endl;
    }
  std::vector<double> voltage;
  std::string line{""};
  double DiodeNumber, tmpFluence, MaxDepVolt;
  getline(maxdeps,line);
  while(!maxdeps.eof())
    {
      getline(maxdeps,line);
      stringstream ss(line);
      ss >> DiodeNumber >> tmpFluence >> MaxDepVolt;
      std::cout << DiodeNumber << "\t" << tmpFluence << "\t" << MaxDepVolt << std::endl;
      voltage.push_back(MaxDepVolt);

    }

  //Extract leakage current and fluence measurements and calculate change in leakage current for all sensors. Then put data into a vector
  std::cout << "file" << "\t\t" << "fluence" << "\t\t" << "maxdep" << std::endl;
  for(unsigned int i{0}; i<filenames_combined.size(); i++)
    {
      minFitIrr = voltage[i] - 15.;
      maxFitIrr = voltage[i] + 15.;
      minFit = voltage[i] - 30.;
      maxFit = voltage[i] + 30.;

      Current I_1 = Extract_Current(filenamesIrr_combined[i],voltage[i],minFitIrr,maxFitIrr,fluencesIrr_combined[i],efluencesIrr_combined[i]);
      Current I_2 = Extract_Current(filenames_combined[i],voltage[i],minFit,maxFit,fluences,efluences);
  
      Current I_3;
      I_3.Mean_current = I_1.Mean_current - I_2.Mean_current;
      I_3.eMean_current = pow(pow(I_1.eMean_current,2) + pow(I_2.eMean_current,2),0.5);
      I_3.Fluence = I_1.Fluence;
      I_3.eFluence = I_1.eFluence;  
      I_MC40_combined.push_back(I_3);
  
      std::cout << filenamesIrr_combined[i] << "\t" << fluencesIrr_combined[i] << "\t" << voltage[i] << std::endl;
    }
  
  Extract_Hardness_Factor(I_MC40_combined);
  maxdeps.close();

}

void MC40_Full_Analysis_CV()
{
  rootlogonATLAS();
  Evaluate_MC40();
}
