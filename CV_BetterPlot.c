#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "fstream"
#include "rootlogonATLAS.h"

void CV_BetterPlot()
{
  rootlogonATLAS();

  ifstream inFile;
  ofstream outFile;
  inFile.open("CV_Diode_2_1711.txt");
  outFile.open("CV_Diode_2_1711_nonlog.txt");

  while(!inFile.eof())
    {
      double logvoltage, logcapacitance, elogvoltage, elogcapacitance;
      inFile >> logvoltage >> logcapacitance >> elogvoltage >> elogcapacitance;
      outFile << exp(logvoltage) << "\t" << exp(logcapacitance) << "\t" << exp(logvoltage)*elogvoltage << "\t" << exp(logcapacitance)*elogcapacitance << std::endl;

      std::cout << logvoltage << " " << logcapacitance << " " << elogvoltage << " " << elogcapacitance << " | " << exp(logvoltage) << " " << exp(logcapacitance) << " "  << exp(logvoltage)*elogvoltage << " " << exp(logcapacitance)*elogcapacitance << std::endl;
      
    }

  inFile.close();
  outFile.close();
  
  TGraphErrors *gr1 = new TGraphErrors("CV_Diode_2_1711_nonlog.txt");
  gr1->GetXaxis()->SetTitle("V (V)");
  gr1->GetYaxis()->SetTitle("C (pF)");
  gr1->SetTitle("");
  gr1->SetLineColor(kBlack);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1);
		

  TF1* fit1 = new TF1("fit1","pol1",2,4.2);
  TF1* fit2 = new TF1("fit2","pol1",4.6,5.4);	
  fit1->SetParameter(1,-1);
  fit1->SetLineColor(kRed);
  fit2->SetLineColor(kRed);	
	
  TCanvas *c1a = new TCanvas("c1","c1",600,700);
  gr1->Draw("AP");
  gr1->Fit(fit1,"RN");
  gr1->Fit(fit2,"RN");
  fit1->Draw("same");
  fit2->Draw("same");
  c1a->SetRightMargin(1);		


     
}
