#include <iostream>
#include <string>
#include <algorithm>
#include "generateData.hpp"

double xIntercept(double m1, double m2, double c1, double c2)
{
  return (c2-c1)/(m1-m2);
}

void Hardness(std::vector<double> dI, std::vector<double> phi, std::vector<double> edI, std::vector<double> ephi)
{
  
  TGraphErrors *DeltaIphi = new TGraphErrors(phi.size(),&(phi[0]),&(dI[0]),&(ephi[0]),&(edI[0]));
  DeltaIphi->SetTitle("");
  DeltaIphi->GetXaxis()->SetTitle("#phi [p/cm^{2}]");
  DeltaIphi->GetYaxis()->SetTitle("#Delta I [nA]");
  DeltaIphi->SetMarkerStyle(20);
  DeltaIphi->SetMarkerSize(0.5);
  TF1 *fit = new TF1("fit","pol1",0.,2.e15);
  fit->FixParameter(0,0.);
  fit->SetParameter(1,1.e20);
  DeltaIphi->Fit(fit,"RN");
  TCanvas *canvas = new TCanvas("DeltaI_vs_Phi","DeltaI_vs_Phi",600,600);
  DeltaIphi->Draw("AP");
  fit->Draw("same");

  std::string hardnessDatafile = "hardness_results.txt";
  ofstream hardnessData;
  hardnessData.open(hardnessDatafile);
  if(!hardnessData.good())
    {
      std::cout<<"Error opening file '"+hardnessDatafile+"'..."<<std::endl;
    }
  else if(hardnessData.good())
    {
      hardnessData << "Fluence [p/cm^2]\tDelta I [nA]\teFluence [p/cm^2]\teDelta I [nA]"<< std::endl;
      for(int i{0}; i<phi.size(); ++i)
  	{
  	  hardnessData << phi[i] << "\t" << dI[i] << "\t" << ephi[i] << "\t" << edI[i] << std::endl;
  	}
    }
  hardnessData.close();

}

void Analysis()
{
  FluenceData data;
  data = generateData();
  std::string line{""};
  std::string fileName;
  ifstream inFile;
  std::vector<double> DeltaI,Fluence,eDeltaI,eFluence;
  for(int i{0}; i<data.irradCVFiles.size(); ++i)
    {
      double maxdep, irrI, unirrI, deltaI, eirrI, eunirrI, edeltaI;
      fileName = "Data/"+data.irradCVFiles[i];
      inFile.open(fileName);
      if(inFile.good())
	{
	  double lnvoltage, lncapacitance, elnvoltage, elncapacitance;
	  std::vector<double> lnVoltage, lnCapacitance, elnVoltage, elnCapacitance;
	  while(true)
	    {
	      if(inFile.eof()){break;}
	      getline(inFile,line);
	      stringstream ss(line);
	      ss >> lnvoltage >> lncapacitance >> elncapacitance;
	      lnVoltage.push_back(lnvoltage);
	      lnCapacitance.push_back(lncapacitance);
	      elnVoltage.push_back(0.);
	      elnCapacitance.push_back(elncapacitance);
	    }
	  inFile.close();
	  TGraphErrors *CV = new TGraphErrors(lnVoltage.size(),&(lnVoltage[0]),&(lnCapacitance[0]),&(elnVoltage[0]),&(elnCapacitance[0]));
	  //fileName.erase(fileName.end()-4,4);
	  std::string fileshort = fileName.substr(5,fileName.length()-9);
	  TString filename = fileshort;
	  CV->SetTitle(filename);
	  CV->GetXaxis()->SetTitle("V [V]");
	  CV->GetYaxis()->SetTitle("I [nA]");
	  double minfitlower,maxfitlower,minfitupper,maxfitupper;
	  switch(i)
	    {
	    case 0: minfitlower = 3.0; maxfitlower = 3.6; minfitupper = 4.0; maxfitupper = 5.0; break; //A30
	    case 1: minfitlower = 3.3; maxfitlower = 3.8; minfitupper = 4.0; maxfitupper = 5.2; break; //B13
	    case 2: minfitlower = 2.5; maxfitlower = 4.2; minfitupper = 4.3; maxfitupper = 5.1; break; //A23
	    case 3: minfitlower = 2.5; maxfitlower = 4.1; minfitupper = 4.5; maxfitupper = 5.2; break; //A34
	    case 4: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.6; maxfitupper = 5.3; break; //B10
	    case 5: minfitlower = 2.5; maxfitlower = 4.3; minfitupper = 4.5; maxfitupper = 5.3; break; //A13
	    case 6: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.7; maxfitupper = 5.4; break; //A21
	    case 7: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.7; maxfitupper = 5.4; break; //A28
	    case 8: minfitlower = 2.5; maxfitlower = 4.4; minfitupper = 4.7; maxfitupper = 5.4; break; //A22
	    case 9: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.75; maxfitupper = 5.4; break; //B7
	    case 10: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 5.0; maxfitupper = 5.5; break; //A26
	    case 11: minfitlower = 2.5; maxfitlower = 4.6; minfitupper = 4.8; maxfitupper = 5.4; break; //A19
	    case 12: minfitlower = 3.5; maxfitlower = 4.1; minfitupper = 4.5; maxfitupper = 5.2; break; //A20
	    case 13: minfitlower = 3.5; maxfitlower = 4.1; minfitupper = 4.5; maxfitupper = 5.5; break; //A25
	    case 14: minfitlower = 3.1; maxfitlower = 3.7; minfitupper = 4.0; maxfitupper = 5.1; break; //B6
	    case 15: minfitlower = 3.4; maxfitlower = 4.0; minfitupper = 4.4; maxfitupper = 5.1; break; //B8
	    case 16: minfitlower = 2.5; maxfitlower = 4.4; minfitupper = 4.5; maxfitupper = 5.0; break; //B14
	    case 17: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.6; maxfitupper = 5.2; break; //A27
	    case 18: minfitlower = 2.5; maxfitlower = 4.2; minfitupper = 4.5; maxfitupper = 5.4; break; //A17
	    case 19: minfitlower = 2.5; maxfitlower = 4.2; minfitupper = 4.5; maxfitupper = 5.1; break; //B5
	    case 20: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.6; maxfitupper = 5.4; break; //B11
	    case 21: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.7; maxfitupper = 5.4; break; //A33
	    case 22: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.9; maxfitupper = 5.4; break; //B4
	    case 23: minfitlower = 2.5; maxfitlower = 4.5; minfitupper = 4.75; maxfitupper = 5.4; break; //A35
	    }
	  TF1 *fitlower = new TF1("fitlower","pol1",minfitlower,maxfitlower);
	  TF1 *fitupper = new TF1("fitupper","pol1",minfitupper,maxfitupper);
	  fitlower->SetLineColor(kRed);
	  fitlower->SetLineColor(kBlue);
	  CV->Fit(fitlower,"QRN");
	  CV->Fit(fitupper,"QRN");
	  double xintercept = xIntercept(fitlower->GetParameter(1),fitupper->GetParameter(1),fitlower->GetParameter(0),fitupper->GetParameter(0));
	  maxdep = -exp(xintercept);
	  TCanvas *canvasCV = new TCanvas(filename,filename,600,600);
	  CV->Draw("AP");
	  fitlower->Draw("same");
	  fitupper->Draw("same");
	  canvasCV->SaveAs(filename+".root");
	  canvasCV->Close();
	  Fluence.push_back(data.fluences[i]);
	  eFluence.push_back(data.efluences[i]);
	}      
      
      fileName = "Data/"+data.irradIVFiles[i];
      inFile.open(fileName);
      if(inFile.good())
	{
	  double voltage, current, evoltage, ecurrent;
	  std::vector<double> Voltage, Current, eVoltage, eCurrent;
	  while(true)
	    {
	      if(inFile.eof()){break;}
	      getline(inFile,line);
	      stringstream ss(line);
	      ss >> voltage >> current >> ecurrent;
	      Voltage.push_back(voltage);
	      Current.push_back(current);
	      eVoltage.push_back(0.05);
	      eCurrent.push_back(ecurrent);	  
	    }
	  inFile.close();
	  TGraphErrors *IV = new TGraphErrors(Voltage.size(),&(Voltage[0]),&(Current[0]),&(eVoltage[0]),&(eCurrent[0]));
	  std::string fileshort = fileName.substr(5,fileName.length()-9);
	  TString filename = fileshort;
	  IV->SetTitle(filename);
	  IV->GetXaxis()->SetTitle("V [V]");
	  IV->GetYaxis()->SetTitle("I [nA]");
	  TF1 *fitIV = new TF1("fitIV","pol1",maxdep-20,maxdep+20);
	  fitIV->SetParameter(1,1.e-6);
	  IV->Fit(fitIV,"QRN");
	  TCanvas *canvasIV = new TCanvas(filename,filename,600,600);
	  IV->Draw("AP");
	  fitIV->Draw("same");
	  canvasIV->SaveAs(filename+".root");
	  canvasIV->Close();
	  irrI = fitIV->GetParameter(1)*maxdep + fitIV->GetParameter(0);
	  eirrI = pow(pow(fitIV->GetParError(1)*maxdep,2)+pow(fitIV->GetParError(0),2),0.5);
	}
      
      fileName = "Data/"+data.unirradIVFiles[i];
      inFile.open(fileName);
      if(inFile.good())
	{
	  double voltage, current, evoltage, ecurrent;
	  std::vector<double> Voltage, Current, eVoltage, eCurrent;
	  while(true)
	    {
	      if(inFile.eof()){break;}
	      getline(inFile,line);
	      stringstream ss(line);
	      ss >> voltage >> current >> ecurrent;
	      Voltage.push_back(voltage);
	      Current.push_back(current);
	      eVoltage.push_back(0.05);
	      eCurrent.push_back(ecurrent);	  
	    }
	  inFile.close();
	  TGraphErrors *IV = new TGraphErrors(Voltage.size(),&(Voltage[0]),&(Current[0]),&(eVoltage[0]),&(eCurrent[0]));
	  std::string fileshort = fileName.substr(5,fileName.length()-9);
	  TString filename = fileshort;
	  IV->SetTitle(filename);
	  IV->GetXaxis()->SetTitle("V [V]");
	  IV->GetYaxis()->SetTitle("I [nA]");
	  TF1 *fitIV = new TF1("fitIV","pol1",maxdep-50,maxdep+50);
	  fitIV->SetParameter(1,1.e-6);
	  IV->Fit(fitIV,"QRN");
	  TCanvas *canvasIV = new TCanvas(filename,filename,600,600);
	  IV->Draw("AP");
	  fitIV->Draw("same");
	  canvasIV->SaveAs(filename+".root");
	  canvasIV->Close();
	  unirrI = fitIV->GetParameter(1)*maxdep + fitIV->GetParameter(0);
	  eunirrI = pow(pow(fitIV->GetParError(1)*maxdep,2)+pow(fitIV->GetParError(0),2),0.5);
	  
	  deltaI = abs(irrI-unirrI);
	  edeltaI = pow(pow(eirrI,2)+pow(eunirrI,2),0.5);
	  DeltaI.push_back(deltaI);
	  eDeltaI.push_back(edeltaI);
	}
    }
  Hardness(DeltaI,Fluence,eDeltaI,eFluence);
}
