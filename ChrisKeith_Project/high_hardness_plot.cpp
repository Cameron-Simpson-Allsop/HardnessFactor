#include <iostream>
#include <vector>
#include "rootlogonATLAS.h"

void high_hardness_plot()
{
  rootlogonATLAS();
  TFile *_file0 = TFile::Open("high_hardness_plot.root");
  TCanvas *canvas = (TCanvas*)_file0->Get("dICanvas");
  TGraphErrors *g=(TGraphErrors*)canvas->GetPrimitive("Graph");
  double xpoint,ypoint;
  std::vector<double> x,y,ex,ey;
  for(int i{0}; i<g->GetN(); ++i)
    {
      g->GetPoint(i,xpoint,ypoint);
      x.push_back(xpoint);
      y.push_back(ypoint);
      ex.push_back(g->GetErrorX(i));
      ey.push_back(g->GetErrorY(i));
    }
  TGraphErrors *fluence = new TGraphErrors(x.size(),&(x[0]),&(y[0]),&(ex[0]),&(ey[0]));
  fluence->SetTitle("");
  fluence->GetXaxis()->SetTitle("#phi [p/cm^{2}]");
  fluence->GetYaxis()->SetTitle("#Delta I [nA]");
  fluence->SetMarkerStyle(20);
  TGaxis::SetMaxDigits(2);
  TF1 *fit = new TF1("fit","pol1",0,1e16);
  fit->SetLineStyle(1);
  fit->SetLineWidth(2);
  fit->SetLineColor(kRed);
  fit->SetParameter(1,1e-20);
  TCanvas *can = new TCanvas("can","can",600,600);
  can->SetLogy();
  can->SetLogx();
  fluence->Fit(fit,"RN");
  fluence->Draw("AP");
  fit->Draw("same");
  can->SaveAs("high_fluence.root");
  can->SaveAs("high_fluence.pdf");
  can->SaveAs("high_fluence.png");
}
