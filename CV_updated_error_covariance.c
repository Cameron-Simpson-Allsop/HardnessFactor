#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"

void CV_updated_error_covariance()
{
  rootlogonATLAS();
  TGraphErrors *gr1 = new TGraphErrors("CV_Diode_2_1711.txt");
  gr1->GetXaxis()->SetTitle("Ln(-V) (Ln(V))");
  gr1->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
  gr1->SetTitle("");
  gr1->SetLineColor(kBlack);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1);
		

  TF1* fit1 = new TF1("fit1","pol1",2,4.2);
  TF1* fit2 = new TF1("fit2","pol1",4.6,5.4);	
  fit1->SetParameter(1,-1);
  fit1->SetLineColor(kRed);
  fit2->SetLineColor(kRed);
  gr1->Fit(fit1,"RN");
  gr1->Fit(fit2,"RN");

  double c1 = fit1->GetParameter(0);
  double m1 = fit1->GetParameter(1);
  double c2 = fit2->GetParameter(0);
  double m2 = fit2->GetParameter(1);
	
  double ec1 = fit1->GetParError(0);
  double em1 = fit1->GetParError(1);
  double ec2 = fit2->GetParError(0);
  double em2 = fit2->GetParError(1);

  double c = c2-c1;
  double m = m1-m2;
  double ec = pow(ec1*ec1 + ec2*ec2,0.5);
  double em = pow(em1*em1 + em2*em2,0.5);
  
  TH1F*hmult = new TH1F("Multiple",";Multiple;Number of Counts",100,0.3,0.345);
  TH1F*hm = new TH1F("x",";x;Number of Counts",100,0.255,0.28);
  TH1F*hc = new TH1F("y",";y;Number of Counts",100,1.151,1.26);
  
  TRandom2 *rndm2=new TRandom2(1);
  const int Ntrials = 10000;	
  for(int i = 0; i < Ntrials; i++){

    double c = abs(rndm2->Gaus(c2,ec2) - rndm2->Gaus(c1,ec1));
    double m = abs(rndm2->Gaus(m1,em1) - rndm2->Gaus(m2,em2));
    double mult = c*m;

    std::cout << c << " " << m << " " << mult <<std::endl;
    
    hmult->Fill(mult);
    hm->Fill(m);
    hc->Fill(c);
  }

  TGaxis::SetMaxDigits(2);
 
  TCanvas *h_mult = new TCanvas("h_mult","h_mult",600,600);
  hmult->Draw();
  hmult->Fit("gaus");
   
  TCanvas *h_m = new TCanvas("h_m","h_m",600,600);
  hm->Draw();
  hm->Fit("gaus");

  TCanvas *h_c = new TCanvas("h_c","h_c",600,600);
  hc->Draw();
  hc->Fit("gaus");

  TCanvas *c1a = new TCanvas("c1","c1",600,700);
  gr1->Draw("AP");
  //fit1->Draw("same");
  //fit2->Draw("same");
  c1a->SetRightMargin(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.DrawLatex(0.6,0.5,"V_{dep} = -91 #pm 5 V");
  gPad->RedrawAxis();
  
  double cov = hmult->GetMean() - (hm->GetMean()*hc->GetMean());
  double Rho = cov/(ec*em);
  double ecov = pow(pow(hmult->GetMeanError(),2) + pow(hm->GetMean()*hc->GetMeanError(),2)*pow(hc->GetMean()*hm->GetMeanError(),2),0.5);
  double Intersect = (c)/(m); //Intersect of fit lines on x axis.
  double eIntersect = pow(pow(ec/m,2) + pow((c*em)/pow(m,2),2) + (2*Rho*c)/pow(m,3)*ec*em,0.5);   
  
  std::cout << "Correlation = "<< Rho << std::endl;
  std::cout << "x Intersect = " << Intersect << " +/- " << eIntersect << std::endl;
  std::cout << "Max Depletion Voltage = " << -exp(Intersect) << " +/- " << exp(Intersect)*eIntersect <<std::endl; //Log scale so take exponents.
  std::cout << "Percentage Error = " << 100*exp(Intersect)*eIntersect/exp(Intersect) << "%" << std::endl;
}
