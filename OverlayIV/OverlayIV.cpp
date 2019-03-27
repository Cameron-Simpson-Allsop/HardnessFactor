#include <iostream>
#include "rootlogonATLAS.h"

void GraphSettings(TMultiGraph *g)
{
  g->SetTitle("");
  g->GetXaxis()->SetTitle("V [V]");
  g->GetYaxis()->SetTitle("I [nA]");
}

void OverlayIV()
{
  TGraphErrors *unirrad = new TGraphErrors("Diode46_IV_2802.txt");
  unirrad->SetMarkerStyle(20);

  TGraphErrors *irrad = new TGraphErrors("Diode46_IV_irradiated_0603.txt");
  irrad->SetMarkerStyle(21);
  
  TMultiGraph *mg = new TMultiGraph();
  GraphSettings(mg);
  mg->Add(unirrad,"p");
  mg->Add(irrad,"p");

  TLegend *leg = new TLegend(0.55,0.15,0.65,0.3);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);

  double maxdep = -103.478;
  double minfit = maxdep-30.;
  double maxfit = maxdep+30.;
  double minfitirr = maxdep-15.;
  double maxfitirr = maxdep+15.;

  TF1 *fit = new TF1("fit","pol1",minfit,maxfit);
  fit->SetLineColor(kRed);

  TF1 *fitirr = new TF1("fitirr","pol1",minfitirr,maxfitirr);
  fitirr->SetLineColor(kRed);

  TCanvas *can = new TCanvas("OverlayIV","OverlayIV",600,600);
  unirrad->Fit(fit,"RN");
  irrad->Fit(fitirr,"RN");
  leg->AddEntry(unirrad,"Unirradiated","lp");
  leg->AddEntry(irrad,"Irradiated 4.33x10^{11} p/cm^{2}","lp");
  mg->Draw("AP");
  fit->Draw("same");
  fitirr->Draw("same");
  leg->Draw("same");
  can->SetLeftMargin(0.15);
  can->SaveAs("Diode46_Overlay_IV.pdf");
}
