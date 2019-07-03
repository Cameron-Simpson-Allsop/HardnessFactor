#include<iostream>
#include<fstream>
#include<vector>

void Efficiency_calibration()
{
  ifstream inFile;
  inFile.open("Efficiency_calibration_data_edit.txt");
  std::string line{""};
  std::vector<double> VEn,VEf,VeEn,VeEf;
  getline(inFile,line);
  while(!inFile.eof())
    {
      double En,Ef,eEn,eEf;
      inFile>>En>>Ef>>eEn>>eEf;
      VEn.push_back(En);//keV
      VEf.push_back(Ef);
      VeEn.push_back(eEn);
      VeEf.push_back(eEf);      
    }
  inFile.close();
  TF1 *power = new TF1("power","[0]*x^[1]",200,1400);
  TGraphErrors *g = new TGraphErrors(VEn.size(),&(VEn[0]),&(VEf[0]),&(VeEn[0]),&(VeEf[0]));
  g->GetXaxis()->SetTitle("Energy [keV]");
  g->GetYaxis()->SetTitle("Detector Efficiency");
  g->SetTitle("");
  g->SetMarkerStyle(20);
  g->Fit(power,"RN");
  TCanvas *canvas = new TCanvas("canvas","canvas",600,600);
  canvas->SetLeftMargin(0.15);
  g->Draw("AP");
  power->Draw("same");
  canvas->SaveAs("Efficiency_calibration_surface.png");

  double keV = 1377.;
  double DP_eff = 0.0001993;
  double Ni_eff = power->GetParameter(0)*pow(keV,power->GetParameter(1));
  double eNi_eff = pow(pow(pow(keV,power->GetParameter(1))*power->GetParError(0),2) + pow(pow(keV,power->GetParameter(1))*log(keV)*power->GetParError(1),2),0.5);
  std::cout << "Efficiency at "<<keV<<"keV = "<<Ni_eff<<" +/- "<<eNi_eff<<std::endl;
  std::cout << "Calibration Factor (Efficiency/Efficiency at Calibrated Position) = "<<Ni_eff/DP_eff<<" +/- "<<eNi_eff/DP_eff<<std::endl;
  
}
