#include <iostream>
#include <fstream>
#include <vector>

void Plotter()
{
  std::vector<string> files = {"1st_data_set_wait_5","2nd_data_set_wait_5_hyst","3rd_data_set_wait_5_hyst_no_people","4th_data_set_wait_5_hyst_no_people_no_banana"};
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("");
  mg->GetXaxis()->SetTitle("Bias [V]");
  mg->GetYaxis()->SetTitle("Current [pA]");
  TLegend *leg = new TLegend(0.4,0.2,0.6,0.4);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  for(int i{0}; i<files.size(); ++i)
    {      
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
      if(i != 2)
	{	  
	  IV->SetMarkerColor(i+1);
	  IV->SetLineColor(i+1);
	}
      else if(i==2)
	{
	  IV->SetMarkerColor(6);
	  IV->SetLineColor(6);	  
	}
      mg->Add(IV,"lp");
      leg->AddEntry(IV,fileName,"lp");
    }
  TCanvas *canvas = new TCanvas("canvas","canvas",600,600);
  TGaxis::SetMaxDigits(3);
  mg->Draw("AP");
  leg->Draw();
  canvas->SaveAs("BPW34F_setup2.root");
  canvas->SaveAs("BPW34F_setup2.pdf");
  canvas->SaveAs("BPW34F_setup2.png");
}
