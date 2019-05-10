#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "rootlogonATLAS.h"

struct Data
{
  std::vector<double> Voltages; //(V)
  std::vector<double> Capacitances; //(F)
  std::vector<double> OneOverC2; //(F^-2)
  std::vector<double> eVoltages; //(V)
  std::vector<double> eCapacitances; //(F)
  std::vector<double> eOneOverC2; //(F^-2)
  std::vector<double> logVoltages;
  std::vector<double> logCapacitances;
  std::vector<double> elogVoltages;
  std::vector<double> elogCapacitances;
  double Fluence; //(p/cm^2)
  double eFluence; //(p/cm^2)
};

double StdDev(double c1, double c2, double c3, double c4, double c5, double mean)
{
  double sumSquares = pow(c1-mean,2) + pow(c2-mean,2) + pow(c3-mean,2) + pow(c4-mean,2) + pow(c5-mean,2);
  return pow(sumSquares/4.,0.5); 
}

Data ReadFile(std::string filePath, std::string fileHeaderStart)
{
  ifstream inFile;
  inFile.open(filePath);
  Data data;
  std::vector<double> Voltage;
  std::vector<double> Capacitance;
  double capacitanceMean{0};

  if(!inFile.good())
    {
      std::cout << "Error Opening Input File" << std::endl;
    }
  else if(inFile.good())
    {
      std::string line{""};
      std::string timeStamp{""};
      double voltage{}, current{}, resistance{}, capacitance{}, fluence{}, efluence{};
      int linecount{1};
      while(!inFile.eof())
	{
	  getline(inFile,line);
	  if(line.find(fileHeaderStart) == 0)
	    {
	      //std::cout << line << std::endl;
	    }
	  else if(linecount == 5)
	    {
	      //std::cout << line << std::endl;
	      stringstream ssfluence(line);
	      ssfluence >> fluence >> efluence;
	      std::cout << fluence << " +/- " << efluence << std::endl;
	      data.Fluence = fluence;
	      data.eFluence = efluence;
	    }
	  else if(linecount > 28)
	    {
	      //std::cout << line << std::endl;
	      stringstream ssdata(line);
	      ssdata >> timeStamp >> voltage >> current >> resistance >> capacitance;
	      //std ::cout << timeStamp << "\t" << voltage << "\t" << current << "\t" << resistance << "\t" << capacitance << std::endl;
	      Voltage.push_back(voltage);
	      Capacitance.push_back(capacitance);
	    }  
	  ++linecount;
	}
    }
  
  int n{0};
  for(int i{0}; i<=Voltage.size(); ++i)
    {
      if(n != 5){++n;}
      else if(n == 5)
	{
	  n = 1;
	  double voltageav{(Voltage[i-1] + Voltage[i-2] + Voltage[i-3] + Voltage[i-4] +Voltage[i-5])/5.};
	  data.Voltages.push_back(voltageav);
	  data.eVoltages.push_back(0.05);
	  capacitanceMean = (Capacitance[i-1] + Capacitance[i-2] + Capacitance[i-3] + Capacitance[i-4] +Capacitance[i-5])/5.;
	  data.Capacitances.push_back(capacitanceMean);
	  double ecapacitanceMean{StdDev(Capacitance[i-1],Capacitance[i-2],Capacitance[i-3],Capacitance[i-4],Capacitance[i-5],capacitanceMean)};
	  data.eCapacitances.push_back(ecapacitanceMean);
	  data.OneOverC2.push_back(1/pow(capacitanceMean,2));
	  data.eOneOverC2.push_back(2*ecapacitanceMean/pow(capacitanceMean,3));
	  if(voltageav != 0.)
	    {
	  data.logVoltages.push_back(log(abs(voltageav)));
	  data.elogVoltages.push_back(0.05/abs(voltageav));
	  data.logCapacitances.push_back(log(capacitanceMean));
	  data.elogCapacitances.push_back(ecapacitanceMean/capacitanceMean);
	    }
	}      
    }
 
  return data;
  inFile.close();
}

double MaxDep(Data data, TString graphTitle, int DiodeNumber, std::string irradstate)
{
  rootlogonATLAS();
  
  double minFitLeft, minFitRight, maxFitLeft, maxFitRight, p0l, p1l, p0r, p1r, logdep;
  
  switch(DiodeNumber)
    {
    case 25: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.7; maxFitRight=5.3; break;
    case 26: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.6; maxFitRight=5.3; break;
    case 27: minFitLeft=2.5; maxFitLeft=4.3; minFitRight=4.5; maxFitRight=5.3; break;
    case 28: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.6; maxFitRight=5.3; break;
    case 29: minFitLeft=2.5; maxFitLeft=4.4; minFitRight=4.5; maxFitRight=5.2; break;
    case 30: minFitLeft=2.5; maxFitLeft=4.4; minFitRight=4.5; maxFitRight=5.3; break;
    case 31: minFitLeft=2.5; maxFitLeft=4.1; minFitRight=4.6; maxFitRight=5.3; break;
    case 32: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.6; maxFitRight=5.3; break;
    case 33: minFitLeft=2.5; maxFitLeft=4.1; minFitRight=4.5; maxFitRight=5.2; break;
    case 34: minFitLeft=2.5; maxFitLeft=4.3; minFitRight=4.5; maxFitRight=5.2; break;
    case 35: minFitLeft=2.5; maxFitLeft=4.4; minFitRight=4.6; maxFitRight=5.2; break;
    case 36: minFitLeft=2.5; maxFitLeft=4.3; minFitRight=4.5; maxFitRight=5.3; break;
    case 37: minFitLeft=2.5; maxFitLeft=3.6; minFitRight=4.; maxFitRight=4.75; break;
    case 38: minFitLeft=2.5; maxFitLeft=3.7; minFitRight=4.1; maxFitRight=5.3; break;
    case 39: minFitLeft=2.5; maxFitLeft=4.3; minFitRight=4.5; maxFitRight=5.3; break;
    case 40: minFitLeft=2.5; maxFitLeft=4.4; minFitRight=4.5; maxFitRight=5.3; break;
    case 41: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.8; maxFitRight=5.3; break;
    case 42: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.8; maxFitRight=5.3; break;
    case 43: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.75; maxFitRight=5.3; break;
    case 44: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.75; maxFitRight=5.3; break;  
    case 45: minFitLeft=2.5; maxFitLeft=4.4; minFitRight=4.8; maxFitRight=5.3; break;
    case 46: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.8; maxFitRight=5.3; break;
    case 47: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.9; maxFitRight=5.3; break;
    case 48: minFitLeft=2.5; maxFitLeft=4.5; minFitRight=4.75; maxFitRight=5.3; break;      
    }

  TF1 *fitLeft = new TF1("fitLeft", "pol1", minFitLeft, maxFitLeft);
  TF1 *fitRight = new TF1("fitRight", "pol1", minFitRight, maxFitRight);
  fitLeft->SetParameter(1,-0.5);
  fitLeft->SetLineColor(kRed);
  fitRight->SetLineColor(kRed);

  TGaxis::SetMaxDigits(3);
  //TGraphErrors *g = new TGraphErrors(data.Voltages.size(), &(data.Voltages[0]), &(data.OneOverC2[0]), &(data.eVoltages[0]), &(data.eOneOverC2[0]));
  TGraphErrors *g = new TGraphErrors(data.logVoltages.size(), &(data.logVoltages[0]), &(data.logCapacitances[0]), &(data.elogVoltages[0]), &(data.elogCapacitances[0]));
  //g->GetXaxis()->SetTitle("Bias Voltage [V]");
  //g->GetYaxis()->SetTitle("#frac{1}{C^{2}} [F^{-2}]");
  g->GetXaxis()->SetTitle("Ln(V) [Ln(V)]");
  g->GetYaxis()->SetTitle("Ln(C) [Ln(F)]");
  g->SetMarkerStyle(20);
  g->GetYaxis()->SetTitleOffset(1.8);

  if(DiodeNumber == 31)
    {
      g->SetTitle("Diode 31 (Resoldered)");
    }
  else
    {
      g->SetTitle(graphTitle);
    }

  g->Fit(fitLeft,"RN");
  g->Fit(fitRight,"RN");

  TCanvas *can = new TCanvas(graphTitle,graphTitle,600,600);
  can->SetLeftMargin(0.2);
  can->SetTopMargin(0.2);
  g->Draw("AP");
  fitLeft->Draw("same");
  fitRight->Draw("same");
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.DrawLatex(0.6,0.5,"(1)");
  latex.DrawLatex(0.6,0.5,"(2)");
  gPad->RedrawAxis();
  
  TString PlotFile = "Diode" + std::to_string(DiodeNumber) + "_CV_" + irradstate + ".png";
  //can->SaveAs(PlotFile);

  p0l = fitLeft->GetParameter(0);
  p1l = fitLeft->GetParameter(1);
  p0r = fitRight->GetParameter(0);
  p1r = fitRight->GetParameter(1);
  logdep = (p0r - p0l)/(p1l - p1r);

  return -exp(logdep);
  
}

void MC40_CV()
{
  rootlogonATLAS();
  ofstream maxdeps;
  maxdeps.open("MaxDep_vs_Fluence.txt");
  std::string irradstate{"PostAnneal"};
  std::string fileHeaderStart{"Time/Date"};
  std::vector<double> maxdep;
  std::vector<double> fluence;
  if(!maxdeps.good())
    {
      std::cout << "Error opening output file..." << std::endl;
    }
  else if(maxdeps.good())
    {
      maxdeps << "Diode Number" << "\t" << "Fluence (p/cm^2)" << "\t" << "eFluence (p/cm^2)" << "\t"  << "Max Depletion Voltage (V)" << std::endl;
      for(int i{25}; i<=48; ++i)
	{  
	  std::string filePath = "Diode" + std::to_string(i) + "_CV_" + irradstate + ".txt";
	  std::cout << filePath << std::endl;
	  Data data = ReadFile(filePath, fileHeaderStart);
	  TString graphTitle = "Diode " + std::to_string(i);
	  double depvolt = MaxDep(data, graphTitle, i, irradstate);
	  maxdeps << i << "\t" << data.Fluence << "\t" << data.eFluence << "\t" << depvolt << std::endl;
	  maxdep.push_back(depvolt);
	  fluence.push_back(data.Fluence);
	}
      TGraph *g = new TGraph(maxdep.size(), &(fluence[0]), &(maxdep[0]));
      g->GetYaxis()->SetTitle("Max Depletion Voltage (V)");
      g->GetXaxis()->SetTitle("Fluence (p/cm^{2})");
      g->SetTitle("");
      g->GetYaxis()->SetTitleOffset(1.5);
      g->SetMarkerStyle(20);

      TCanvas *canvas = new TCanvas("MaxDep_vs_Fluence","MaxDep_vs_Fluence",600,600);
      canvas->SetLeftMargin(0.16);
      canvas->SetRightMargin(0.13);
      canvas->SetTopMargin(0.2);
      g->Draw("AP");
      //canvas->SaveAs("MaxDep_vs_Fluence.pdf");
    }
  maxdeps.close();
}
  
  
