#include <iostream>
#include <fstream>
#include <vector>

void Plotter()
{
  std::vector<string> files = {"Run1_5s_settling_75_steps","Run2_5s_settling_75_steps","Run3_5s_settling_75_steps","Run4_5s_settling_75_steps","Run5_5s_settling_75_steps","Run1_10s_settling_75_steps","Run2_10s_settling_75_steps_people","Run3_10s_settling_75_steps_people","Run4_10s_settling_75_steps_EC_chamber","Run5_10s_settling_75_steps_people","Run6_10s_settling_75_steps_people","Run1_10s_settling_75_steps_meter_connect_zero_correction","Run1_5s_settling_75_steps_meter_connect_zero_correction","Run2_10s_settling_75_steps_meter_connect_zero_correction","Run2_5s_settling_75_steps_meter_connect_zero_correction","Run3_5s_settling_75_steps_meter_connect_zero_correction","Run3_10s_settling_75_steps_meter_connect_zero_correction"};
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("");
  mg->GetXaxis()->SetTitle("Bias [V]");
  mg->GetYaxis()->SetTitle("Current [pA]");
  TLegend *leg = new TLegend(0.3,0.2,0.5,0.5);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.02);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  int color{1};
  for(int i{0}; i<files.size(); ++i)
    {
      ++color;
      if(color == 5 || color == 10 || color == 16 || color == 17 || color == 18 || color == 19 || color == 20)
	{
	  ++color;
	}
      ifstream inFile;
      std::string line{""};
      inFile.open(files[i]);
      TString fileName = files[i];
      if(!inFile.good()){std::cout<<"Error reading file '"<<files[i]<<"'..."<<std::endl;}
      int linecount{0};
      std::string date,timestamp;
      double voltage,temperature,current,guardcurrent;
      std::vector<double> Voltage,Current;
      while(!inFile.eof())
	{
	  ++linecount;
	  //remainder(linecount,2);
	  getline(inFile,line);
	    if(linecount>36 && line != "END" && linecount%2 != 0)
	      {
		stringstream ss(line);
		ss >> date >> timestamp >> voltage >> temperature >> current >> guardcurrent;
		Voltage.push_back(voltage);
		Current.push_back(current*1.e12);
	      }
	}
      TGraph *IV = new TGraph(Voltage.size(),&(Voltage[0]),&(Current[0]));
      IV->SetMarkerStyle(20);
      IV->SetMarkerSize(0.7);
      IV->SetMarkerColor(color);
      IV->SetLineColor(color);
      mg->Add(IV,"lp");
      leg->AddEntry(IV,fileName,"lp");
    }
  TCanvas *canvas = new TCanvas("canvas","canvas",600,600);
  TGaxis::SetMaxDigits(3);
  mg->Draw("AP");
  leg->Draw();
  canvas->SaveAs("BPW34F_setup3.root");
  canvas->SaveAs("BPW34F_setup3.pdf");
  canvas->SaveAs("BPW34F_setup3.png");
}
