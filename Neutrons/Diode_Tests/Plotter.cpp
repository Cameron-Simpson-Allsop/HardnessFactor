#include <iostream>
#include <fstream>
#include <vector>

void Plotter()
{
  std::vector<string> filePath = {"IV_BPW_first_wait_5_sec","IV_BPW_sec_wait_5_sec","IV_BPW_third_wait_5_sec","IV_BPW_fourth_wait_1_sec"};
  ifstream inFile;
  double voltage,current,temp,guardCurrent;
  std::string date,timeStamp;
  std::vector<double> V,I;
  std::string line{""};
  int linecount{0};
  TMultiGraph *mg = new TMultiGraph();
  mg->GetXaxis()->SetTitle("V [V]");
  mg->GetYaxis()->SetTitle("I [A]");
  for(int i{0}; i<filePath.size(); ++i)
    {
      inFile.open(filePath[i]);
      if(!inFile.good()){std::cout<<"Error reading file '"<<filePath[i]<<"'...\n";}
      while(true)
	{
	  ++linecount;
	  getline(inFile,line);
	  // std::cout<<line<<"\n";
	  if(inFile.eof())break;
	  if(linecount >= 37)// && linecount <= 437)
	    {
	      stringstream ss(line);
	      ss>>date>>timeStamp>>voltage>>temp>>current>>guardCurrent;
	      V.push_back(voltage);
	      I.push_back(current);
	    }
	}
      TGraph *g = new TGraph(V.size(),&(V[0]),&(I[0]));
      g->SetTitle("");
      g->SetMarkerStyle(20);
      g->SetMarkerSize(0.5);
      g->SetMarkerColor(i+1);
      mg->Add(g,"p");
      V.clear();
      I.clear();
      inFile.close();
    }
  TCanvas *can = new TCanvas("can","can",600,600);
  can->SetLeftMargin(0.12);
  mg->Draw("AP");
}
