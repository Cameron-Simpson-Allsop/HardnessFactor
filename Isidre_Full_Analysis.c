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

double Extract_Max_Depletion_Voltage(TString txtName="", double min1 = 0, double max1 = 0, double min2 = 0, double max2 = 0)
{
  //Reads in file and assign variables to each column. Then manipulate variables and put into a vector
  ifstream file;
  file.open(txtName);
  std::vector<double> v, c;
  int n = 0;
  while(!file.eof())
    {
      double voltage, capacitance;
      file >> voltage >> capacitance;

      v.push_back(voltage);
      c.push_back(1/pow(capacitance,2));

      n = n+1;
      //std::cout << voltage << " " << capacitance << "\n" << n << "\n";

    }

  //Plot vector
  TGraph *g = new TGraph(n, &v[0], &c[0]);
  g->GetXaxis()->SetTitle("Voltage(-V)");
  g->GetYaxis()->SetTitle("1/Capacitance^{2} (1/F^{2})");
  g->SetTitle("");
  g->SetMarkerStyle(20);
  g->SetMarkerSize(1.2);

  //Fit each region on plot
  TF1* fit1 = new TF1("fit1","pol1", min1, max1);
  TF1* fit2 = new TF1("fit2","pol1", min2, max2);
	
  fit1->SetLineColor(kRed);
  fit2->SetLineColor(kRed);
  g->Fit(fit1,"RN");
  g->Fit(fit2,"RN");

  //Draw plot with fits
  TCanvas* canvas = new TCanvas(txtName,txtName); //Defines a canvas.
    g->Draw("AP"); //Draw graph with defined axes (A) and points (P).
    fit1->Draw("same");
    fit2->Draw("same");

  //Calculate intersect of the fits
  double c1 = fit1->GetParameter(0);
  double m1 = fit1->GetParameter(1);
  double c2 = fit2->GetParameter(0);
  double m2 = fit2->GetParameter(1);	
  double ec1 = fit1->GetParError(0);
  double em1 = fit1->GetParError(1);
  double ec2 = fit2->GetParError(0);
  double em2 = fit2->GetParError(1);
  /*double Intersect = (c2-c1)/(m1-m2); 
    double e1 = ec2/(m1-m2);
    double e2 = ec1/(m1-m2);
    double e3 = em1*(c2-c1)/(pow(m1-m2,2));
    double e4 = em2*(c2-c1)/(pow(m1-m2,2));
    double eIntersect = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);*/

  double cdiff = c2-c1;
  double mdiff = m1-m2;
  double Intersect = cdiff/mdiff; //Intersect of fit lines on x axis.
  double ec = pow(ec1*ec1 + ec2*ec2,0.5);
  double em = pow(em1*em1 + em2*em2,0.5);
  double eIntersect = pow(pow(ec/mdiff,2) + pow((cdiff*em)/pow(mdiff,2),2) - (2*cdiff)/pow(mdiff,3)*ec*em,0.5);
	
  std::cout << txtName << std::endl;
  std::cout << "Max Depletion Voltage = " << Intersect << " +/- " << eIntersect << " V" << std::endl;

  //Return max depletion voltage
  return Intersect;
}

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
  g->GetXaxis()->SetTitle("Fluence (pcm^{-2})");
  g->GetYaxis()->SetTitle("Change in Leakage Current (-nA)");
  g->SetTitle("");
  g->GetXaxis()->SetRangeUser(-5.e12, 100.e12);
  g->GetYaxis()->SetRangeUser(-0.5e3, 18.e3);

  //Fits data
  TF1* fit = new TF1("fit","pol1",0,10e13);
  fit->SetParameter(1,1e-12);
  fit->SetParameter(0,0);
  fit->SetLineColor(kBlue);
  
  TF1* fit1 = new TF1("fit1","[0]*x",0,5e13);
  fit1->SetParameter(0,1e-12);
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
  TCanvas *Fluence = new TCanvas("Isidre Current v Fluence","Isidre Current v Fluence",600,700);
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
  //latex.DrawLatex(0.49,0.2,"#kappa_{pol1 fit} = 0.601 #pm 0.020");
  latex.DrawLatex(0.49,0.25,"#kappa = 0.62 #pm 0.02");
  gPad->RedrawAxis();

  //Sensor parameters
  double l{0.5}; //p cm^2
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

  std::cout << "Isidre Alpha (pol1) = " << alpha << " +/- " << ealpha << std::endl;
  std::cout << "Isidre Hardness Factor (pol1) = " << k << " +/- " << ek << std::endl;

  std::cout << "Isidre Alpha (force 0) = " << alpha1 << " +/- " << ealpha1 << std::endl;
  std::cout << "Isidre Hardness Factor (force 0) = " << k1 << " +/- " << ek1 << std::endl;
  
}
    
void Evaluate_Isidre()
{

  //Defines vector and states Isidre's systematic fluence error multiplier
  std::vector<Current> I_Isidre;
  double Isidre_sys_fluence_error = 0.07;//7%

  //Determine max depletion voltage for each irradiated sensor and assign to variable. Format: "filename", min1, max1, min2, max2
  double C4_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-C4_postanneal_CV.txt",50., 240., 260., 350.);
  double F2_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-F2_postanneal_CV.txt",40., 75., 100., 300.);
  double F8_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-F8_postanneal_CV.txt",100., 170., 200., 350.);
  double M10_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-M10_postanneal_CV.txt",50., 250., 300., 350.);
  double M12_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-M12_postanneal_CV.txt",30., 70., 100., 200.);
  double M4_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-M4_postanneal_CV.txt",50., 270., 300., 350.);
  double M6_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-M6_postanneal_CV.txt",150., 200., 225., 350.);
  double M7_V = Extract_Max_Depletion_Voltage("Isidre_data/W332-M7_postanneal_CV.txt",50., 240., 270., 350.);
  
  //Irradiated variables
  std::vector<TString> filenamesIrr = {"Isidre_data/W332-C4_irr_pad.txt","Isidre_data/W332-F2_irr_pad.txt","Isidre_data/W332-F8_irr_pad.txt","Isidre_data/W332-M10_irr_pad.txt","Isidre_data/W332-M12_irr_pad.txt","Isidre_data/W332-M4_irr_pad.txt","Isidre_data/W332-M6_irr_pad.txt","Isidre_data/W332-M7_irr_pad.txt"};
  //std::vector<double> voltagesIrr = {249., 82., 186., 288., 81., 285., 207., 253.}; //Isidre's results
  std::vector<double> voltagesIrr = {C4_V, F2_V, F8_V, M10_V, M12_V, M4_V, M6_V, M7_V}; //My results
  std::vector<double> minFitIrr = {200., 50., 170., 250., 60., 250., 180., 225.};
  std::vector<double> maxFitIrr = {260., 100., 250., 300., 100., 350., 220.,  275.};
  std::vector<double> fluencesIrr = {7.44e12, 9.66e13, 2.41e13, 1.09e12, 9.66e13, 1.09e12, 2.41e13, 7.44e12};//p cm^-2
  std::vector<double> efluencesIrr = {fluencesIrr[0]*Isidre_sys_fluence_error,fluencesIrr[1]*Isidre_sys_fluence_error,fluencesIrr[2]*Isidre_sys_fluence_error,fluencesIrr[3]*Isidre_sys_fluence_error,fluencesIrr[4]*Isidre_sys_fluence_error,fluencesIrr[5]*Isidre_sys_fluence_error,fluencesIrr[6]*Isidre_sys_fluence_error,fluencesIrr[7]*Isidre_sys_fluence_error};

  //Unirradiated variables
  std::vector<TString> filenames = {"Isidre_data/W332-C4_nonirr_pad.txt","Isidre_data/W332-F2_nonirr_pad.txt","Isidre_data/W332-F8_nonirr_pad.txt","Isidre_data/W332-M10_nonirr_pad.txt","Isidre_data/W332-M12_nonirr_pad.txt","Isidre_data/W332-M4_nonirr_pad.txt","Isidre_data/W332-M6_nonirr_pad.txt","Isidre_data/W332-M7_nonirr_pad.txt"};
  //std::vector<double> voltages = {249., 82., 186., 288., 81., 285., 207., 253.}; //Isidre's results
  std::vector<double> voltages = {C4_V, F2_V, F8_V, M10_V, M12_V, M4_V, M6_V, M7_V}; //My results
  std::vector<double> minFit = {100., 100., 100., 100., 100., 100., 100., 100.};
  std::vector<double> maxFit = {300., 300., 300., 300., 300., 300., 300., 300.};
  std::vector<double> fluences = {0., 0., 0., 0., 0., 0., 0., 0.};//p cm^-2
  std::vector<double> efluences = {0., 0., 0., 0., 0., 0., 0., 0.};
 

  //Extract leakage current and fluence measurements and calculate change in leakage current for each sensor. Then put data into a vector
  for(unsigned int i{0}; i<filenames.size(); i++)
    {

      //Uncomment next two lines to use Isidre's CV data
      Current I_1 = Extract_Current(filenamesIrr[i],voltagesIrr[i],minFitIrr[i],maxFitIrr[i],fluencesIrr[i],efluencesIrr[i]);
      Current I_2 = Extract_Current(filenames[i],voltages[i],minFit[i],maxFit[i],fluences[i],efluences[i]);

      //Uncomment next two lines to use constant voltage/fit range
      // Current I_1 = Extract_Current(filenamesIrr[i], 91., 80., 100.,fluencesIrr[i],efluencesIrr[i]);
      // Current I_2 = Extract_Current(filenames[i],91. ,0. ,300. ,fluences[i],efluences[i]);
  
      Current I_3;
      I_3.Mean_current = I_1.Mean_current - I_2.Mean_current;
      I_3.eMean_current = pow(pow(I_1.eMean_current,2) + pow(I_2.eMean_current,2),0.5);
      I_3.Fluence = I_1.Fluence;
      I_3.eFluence = I_1.eFluence;  
      I_Isidre.push_back(I_3);
  
      std::cout << "Current = " << I_3.Mean_current << " +/- " << I_3.eMean_current << " nA \n" << "Fluence = " << I_3.Fluence << " +/- " << I_3.eFluence << " p/cm^2 \n";
    }

  //Extract current related damage rate and  hardness factor value
  Extract_Hardness_Factor(I_Isidre);  

}

void Isidre_Full_Analysis()
{
  rootlogonATLAS();
  Evaluate_Isidre();
}
