#include <iostream>

double Scale(double current, double tempfluc)
{
  double Ea = 1.21;//eV
  double kb = 8.617e-5;//eVK^-1
  double Tr = 273.+20.;
  double T = Tr-tempfluc;
  double exponent = -(Ea/(2*kb))*((1/Tr)-(1/T));
  
  return current*pow(Tr/T,2)*exp(exponent);
}

void TempScalingTest()
{
  TMultiGraph *mg = new TMultiGraph();
  TLegend *leg = new TLegend(0.15,0.4,0.35,0.7);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.02);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  int color{0};
  for(int n{1}; n<=10; ++n)
    {
      ++color;
      if(color == 5 || color == 10)
	{
	  ++color;
	}
      std::vector<double> T;
      std::vector<double> I;
      double current = n*10.;
      for(int i{0}; i<100; ++i)
	{
	  double tempfluc = i*5.e-3;
	  I.push_back(Scale(current,tempfluc)-current);
	  T.push_back(tempfluc);
	}
      TGraph *g = new TGraph(T.size(),&(T[0]),&(I[0]));
      g->SetTitle("");
      g->GetXaxis()->SetTitle("Temperature Fluctuation[C]");
      g->GetYaxis()->SetTitle("Current Fluctuation [pA]");
      g->SetMarkerStyle(20);
      g->SetMarkerSize(0.5);
      g->SetMarkerColor(color);
      g->SetLineColor(color);
      mg->Add(g,"p");
      std::string legEntry = std::to_string(current) + "pA";
      TString TlegEntry = legEntry;
      leg->AddEntry(g,TlegEntry,"lp");      
    }
  TCanvas *canvas = new TCanvas("canvas","canvas",600,600);
  mg->GetXaxis()->SetTitle("Temperature Fluctuation[C]");
  mg->GetYaxis()->SetTitle("Current Fluctuation [pA]");
  mg->Draw("AP");
  leg->Draw("same");
  canvas->SaveAs("Current_vs_Temperature_sim.root");
  canvas->SaveAs("Current_vs_Temperature_sim.pdf");
  canvas->SaveAs("Current_vs_Temperature_sim.png");
}
