#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"
#include "fstream"
#include <algorithm>

struct DiodeFluence
{
  std::vector<int> DiodeNumber;
  std::vector<double> DiodeFluence;
  std::vector<double> eDiodeFluence;
};

struct Data
{
  int DiodeNumber;
  std::vector<double> voltage;
  std::vector<double> current;
  std::vector<double> evoltage;
  std::vector<double> ecurrent;
  std::vector<double> currentupper;
  std::vector<double> currentlower;
  double temperature;
  double etemperature;  
};

DiodeFluence GetFluences()
{
  DiodeFluence diode;
  std::string filepath{"MaxDep_vs_Fluence.txt"};
  ifstream inFile;
  inFile.open(filepath);
  if(!inFile.good())
    {
      std::cout << "Error opening file: '" + filepath + "'..." << std::endl;
    }
  std::string line{""};
  getline(inFile,line);
  while(!inFile.eof())
    {
      int DiodeNumber;
      double Fluence, eFluence, MaxDep;
      inFile >> DiodeNumber >> Fluence >> eFluence >> MaxDep;
      //std::cout << "\t" << DiodeNumber << "\t" << Fluence << "\t" << eFluence << "\t" << MaxDep << std::endl;
      diode.DiodeNumber.push_back(DiodeNumber);
      diode.DiodeFluence.push_back(Fluence);
      diode.eDiodeFluence.push_back(eFluence);
    }
  inFile.close();
  return diode;
}

double StdDev(double c1, double c2, double c3, double c4, double c5, double mean)
{
  double sumSquares = pow(c1-mean,2) + pow(c2-mean,2) + pow(c3-mean,2) + pow(c4-mean,2) + pow(c5-mean,2);
  return pow(sumSquares/4.,0.5); 
}

double TempScale(double current, double T)
{
  double Ea = 1.21; //eV
  double kb = 8.6173e-1; //eVK^-1
  double Tr = 273+21; //K
  double exponent = -(Ea/(2*kb))*((1/Tr)-(1/T));
  return current*pow((Tr/T),2)*exp(exponent);
}

Data GetFile(int DiodeNumber, std::string irradstate)
{
  ifstream inFile;
  std::string filePath = "Diode" + std::to_string(DiodeNumber) + "_IV_" + irradstate + ".txt";
  inFile.open(filePath);
  Data data;
  std::vector<double> Voltage;
  std::vector<double> Current;
  data.DiodeNumber = DiodeNumber;

  if(!inFile.good())
    {
      std::cout << "Error Opening Input File..." << std::endl;
    }
  else if(inFile.good())
    {
      std::string line{""};
      std::string timeStamp{""};
      double voltage{}, current{}, temperature{};
      int linecount{1};
      while(!inFile.eof())
	{
	  getline(inFile,line);
	  if(linecount == 4)
	    {
	      line.erase(std::remove(line.begin(), line.end(), 'C'), line.end());
	      line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	      std::string tmp = line.substr(line.length() - 5);
	      data.temperature = std::stod(tmp);
	      data.etemperature = 0.1;	      
	    }
	  else if(linecount >= 18)
	    {
	      //std::cout << line << std::endl;
	      stringstream ssdata(line);
	      ssdata >> timeStamp >> voltage >> current;
	      //std ::cout << timeStamp << "\t" << voltage << "\t" << current << std::endl;
	      Voltage.push_back(voltage);
	      Current.push_back(current);
	    }  
	  ++linecount;
	}
    }
  inFile.close();
  int n{0};
  for(int i{0}; i<=Voltage.size(); ++i)
    {
      if(n != 5){++n;}
      else if(n == 5)
	{
	  n = 1;
	  double voltageav{(Voltage[i-1] + Voltage[i-2] + Voltage[i-3] + Voltage[i-4] +Voltage[i-5])/5.};
	  data.voltage.push_back(voltageav);
	  data.evoltage.push_back(0.05);
	  
	  double currentMean = (Current[i-1] + Current[i-2] + Current[i-3] + Current[i-4] +Current[i-5])/5.;
	  data.current.push_back(TempScale(currentMean,data.temperature));
	  double ecurrentMean{StdDev(Current[i-1],Current[i-2],Current[i-3],Current[i-4],Current[i-5],currentMean)};
	  data.ecurrent.push_back((TempScale(currentMean,data.temperature)/currentMean)*ecurrentMean);

	  data.currentupper.push_back(TempScale(currentMean,data.temperature)+(TempScale(currentMean,data.temperature)/currentMean)*ecurrentMean);
	  data.currentlower.push_back(TempScale(currentMean,data.temperature)-(TempScale(currentMean,data.temperature)/currentMean)*ecurrentMean);
	}
      
    }      
  
  return data;
}
void MgSettings(TMultiGraph *g)
{ 
  g->GetXaxis()->SetTitle("Voltage (V)");
  g->GetYaxis()->SetTitle("Current (A)");
}
void GraphSettings(TGraph *g, std::string color)
{
  g->GetXaxis()->SetTitle("Voltage (V)");
  g->GetYaxis()->SetTitle("Current (A)");
  g->SetMarkerStyle(1);

  if(color == "red")
    {
      g->SetMarkerColor(kRed);
      g->SetLineColor(kRed);
    }
  else if(color == "blue")
    {
      g->SetMarkerColor(kBlue);
      g->SetLineColor(kBlue);
    }
  else
    {
      std::cout << "Error specifying graph colors..." << std::endl;
    }
}

void LeakageFluctuation()
{
  rootlogonATLAS();
  DiodeFluence Fluences = GetFluences();

  for(int i{25}; i<=48; ++i)
    {
      Data IrradData = GetFile(i,"Irrad");
      Data UnirradData = GetFile(i, "Unirrad");

      TString cantitle = "Diode " + std::to_string(i);
      
      TGraph *irradupper = new TGraph(IrradData.voltage.size(), &(IrradData.voltage[0]), &(IrradData.currentupper[0]));
      TGraph *irradlower = new TGraph(IrradData.voltage.size(), &(IrradData.voltage[0]), &(IrradData.currentlower[0]));
      TGraph *unirradupper = new TGraph(UnirradData.voltage.size(), &(UnirradData.voltage[0]), &(UnirradData.currentupper[0]));
      TGraph *unirradlower = new TGraph(UnirradData.voltage.size(), &(UnirradData.voltage[0]), &(UnirradData.currentlower[0]));

      GraphSettings(irradupper,"blue"); GraphSettings(irradlower,"red"); GraphSettings(unirradupper,"blue"); GraphSettings(unirradlower,"red");

      TMultiGraph *mgirrad = new TMultiGraph();
      MgSettings(mgirrad);
      mgirrad->Add(irradupper,"lp");
      mgirrad->Add(irradlower,"lp");

      TMultiGraph *mgunirrad = new TMultiGraph();
      MgSettings(mgunirrad);
      mgunirrad->Add(unirradupper,"lp");
      mgunirrad->Add(unirradlower,"lp");

      if(i==38||i==48)
	{
	  TCanvas *canvas = new TCanvas(cantitle, cantitle, 600, 600);
	  canvas->Divide(1,2);
	  canvas->cd(1);
	  mgirrad->Draw("AP");
	  canvas->cd(2);
	  mgunirrad->Draw("AP");
	}
    }
}
