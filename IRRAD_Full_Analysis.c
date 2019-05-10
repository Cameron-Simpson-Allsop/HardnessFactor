#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"
#include "fstream"

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
  ofstream outFile;
  outFile.open("IRRAD_Hardness_Factor_Data.txt");
  //Put data from vector into a plottable format
  std::vector<double> x,y,ex,ey;
  for(unsigned int i{0}; i<Data.size(); i++)
    {
      x.push_back(Data[i].Fluence);
      y.push_back(Data[i].Mean_current);
      ex.push_back(Data[i].eFluence);
      ey.push_back(Data[i].eMean_current);
      outFile << Data[i].Fluence << "\t" << Data[i].Mean_current << "\t" << Data[i].eFluence << "\t" << Data[i].eMean_current << std::endl;
    }
  outFile.close();
  
  //Plots data
  TGraphErrors *g = new TGraphErrors(x.size(), &(x[0]), &(y[0]), &(ex[0]), &(ey[0]));
  g->SetMarkerColor(kBlack);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(2);
  g->GetXaxis()->SetTitle("#phi [pcm^{-2}]");
  g->GetYaxis()->SetTitle("|#Delta I| [nA]");
  g->GetXaxis()->SetRangeUser(-1.e12,120.e12);
  g->GetYaxis()->SetRangeUser(-0.1e3,7e3);
  g->SetTitle("");

  //Fits data
  TF1* fit = new TF1("fit","pol1",0,10.e13);
  fit->SetParameter(1,1.e-12);
  fit->SetParameter(0,0);
  fit->SetLineColor(kBlue);
  
  TF1* fit1 = new TF1("fit1","[0]*x",0,20.e13);
  fit1->SetParameter(0,1.e-12);
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
  TCanvas *Fluence = new TCanvas("IRRAD Current v Fluence","IRRAD Current v Fluence",600,700);
  Fluence->SetRightMargin(1);
  Fluence->SetRightMargin(0.12);
  Fluence->SetTopMargin(1);
  g->GetYaxis()->SetTitleOffset(1.3);
  TGaxis::SetMaxDigits(3);
  g->Draw("AP");
  //fit->Draw("same");
  fit1->Draw("same");
  //leg->Draw();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  // latex.DrawLatex(0.49,0.2,"#kappa_{pol1 fit} = 0.649 #pm 0.024");
  latex.DrawLatex(0.55,0.3,"#kappa = 0.62 #pm 0.04");
  gPad->RedrawAxis();

  Fluence->SaveAs("IRRAD_results.root");

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

  std::cout << "IRRAD Alpha (pol1) = " << alpha << " +/- " << ealpha << std::endl;
  std::cout << "IRRAD Hardness Factor (pol1) = " << k << " +/- " << ek << std::endl;

  std::cout << "IRRAD Alpha (force 0) = " << alpha1 << " +/- " << ealpha1 << std::endl;
  std::cout << "IRRAD Hardness Factor (force 0) = " << k1 << " +/- " << ek1 << std::endl;

  /* std::string hardnessDatafile = "IRRAD_results.txt"; */
  /* ofstream hardnessData; */
  /* hardnessData.open(hardnessDatafile); */
  /* if(!hardnessData.good()) */
  /*   { */
  /*     std::cout<<"Error opening file '"+hardnessDatafile+"'..."<<std::endl; */
  /*   } */
  /* else if(hardnessData.good()) */
  /*   { */
  /*     hardnessData << "Fluence [p/cm^2]\tDelta I [nA]\teFluence [p/cm^2]\teDelta I [nA]"<< std::endl; */
  /*     for(int i{0}; i<x.size(); ++i) */
  /* 	{ */
  /* 	  hardnessData << x[i] << "\t" << y[i] << "\t" << ex[i] << "\t" << ey[i] << std::endl; */
  /* 	} */
  /*   } */
  /* hardnessData.close(); */
  
}

void Evaluate_IRRAD()
{
  
  //Defines vector and states IRRAD's systematic fluence error multiplier
  std::vector<Current> I_IRRAD;
  double IRRAD_sys_fluence_error = 0.07;//7%
  
  //Irradiated variables
  std::vector<TString> filenamesIrr = {"Diode1_Irradiated_1607.txt","Diode11_Irradiated_1607.txt","Diode12_Irradiated_1607.txt","Diode13_Irradiated_1607.txt","Diode16_Irradiated_1607.txt","Diode17_Irradiated_1607.txt","Diode19_Irradiated_1607.txt","Diode20_Irradiated_1607.txt"};
  std::vector<double> fluencesIrr = {1.09e12, 1.09e12, 7.44e12, 7.44e12, 2.41e13, 2.41e13, 9.66e13, 9.66e13};//p cm^-2
  std::vector<double> efluencesIrr = {fluencesIrr[0]*IRRAD_sys_fluence_error,fluencesIrr[1]*IRRAD_sys_fluence_error,fluencesIrr[2]*IRRAD_sys_fluence_error,fluencesIrr[3]*IRRAD_sys_fluence_error,fluencesIrr[4]*IRRAD_sys_fluence_error,fluencesIrr[5]*IRRAD_sys_fluence_error,fluencesIrr[6]*IRRAD_sys_fluence_error,fluencesIrr[7]*IRRAD_sys_fluence_error};
  double minFitIrr = -100.;
  double maxFitIrr = -75.;
  
  //Unirradiated variables
  std::vector<TString> filenames = {"Diode_1_3_0911.txt","Diode_11_3_0911.txt","Diode_12_3_0911.txt","Diode_13_3_0911.txt","Diode_16_3_0911.txt","Diode_17_3_1611.txt","Diode_19_3_1611.txt","Diode_20_2_1611.txt"};
  std::vector<double> fluences = {0., 0., 0., 0., 0., 0., 0., 0.};//p cm^-2
  std::vector<double> efluences = {0., 0., 0., 0., 0., 0., 0., 0.};
  double minFit = -110.;
  double maxFit = -40.;

  double voltage = -91.;//V

  //Extract leakage current and fluence measurements and calculate change in leakage current for each sensor. Then put data into a vector
  for(unsigned int i{0}; i<filenames.size(); i++)
    {

      Current I_1 = Extract_Current(filenamesIrr[i],voltage,minFitIrr,maxFitIrr,fluencesIrr[i],efluencesIrr[i]);
      Current I_2 = Extract_Current(filenames[i],voltage,minFit,maxFit,fluences[i],efluences[i]);
  
      Current I_3;
      I_3.Mean_current = I_1.Mean_current - I_2.Mean_current;
      I_3.eMean_current = pow(pow(I_1.eMean_current,2) + pow(I_2.eMean_current,2),0.5);
      I_3.Fluence = I_1.Fluence;
      I_3.eFluence = I_1.eFluence;  
      I_IRRAD.push_back(I_3);
  
      std::cout << "Current = " << I_3.Mean_current << " +/- " << I_3.eMean_current << " nA \n" << "Fluence = " << I_3.Fluence << " +/- " << I_3.eFluence << " p/cm^2 \n";
    }
  
  //Extract current related damage rate and  hardness factor value
  Extract_Hardness_Factor(I_IRRAD);
  
}

void IRRAD_Full_Analysis()
{	
  rootlogonATLAS();
  Evaluate_IRRAD(); 
}
