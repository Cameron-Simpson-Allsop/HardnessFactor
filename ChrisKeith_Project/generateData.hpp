#include <iostream>
#include <fstream>
#include <algorithm>
#include "FluenceData.hpp"

FluenceData generateData()
{
  FluenceData data;
  ifstream fluencelist;
  std::string line{""};

  fluencelist.open("Info.txt");

  if(fluencelist.good())
    {   
      int linecount{0};
      while(!fluencelist.eof())
	{
	  ++linecount;
	  std::string diode, irradIVfile, irradCVfile, unirradIVfile, unirradCVfile;
	  double tmp1, tmp2, fluence, efluence, unirradTemp, irradTemp;
	  getline(fluencelist,line);
	  if(linecount>2 && linecount<45)
	    {
	      stringstream ss(line);
	      ss >> diode >> tmp1 >> tmp2 >> fluence >> efluence >> unirradTemp >> irradTemp;
	      irradIVfile = "Irrad_Diode_"+diode+"_IV.txt";
	      irradCVfile = "Irrad_Diode_"+diode+"_CV.txt";
	      unirradIVfile = "Diode_"+diode+"_IV.txt";
	      unirradCVfile = "Diode_"+diode+"_CV.txt";
	      
	      data.irradIVFiles.push_back(irradIVfile);
	      data.irradCVFiles.push_back(irradCVfile);
	      data.unirradIVFiles.push_back(unirradIVfile);
	      data.unirradCVFiles.push_back(unirradCVfile);
	      data.irradIVTemp.push_back(irradTemp);
	      data.unirradIVTemp.push_back(unirradTemp);
	      data.fluences.push_back(fluence);
	      data.efluences.push_back(efluence);
	    }
	}
    }
  else
    {
      std::cout<<"Error opening file lists"<<std::endl;
    }
  fluencelist.close();

  // for(int i{0}; i<data.irradIVFiles.size(); ++i)
  //   {
  //     std::cout << data.irradIVFiles[i] << "\n" << data.irradCVFiles[i] << "\n" << data.unirradIVFiles[i] << "\n" << data.unirradCVFiles[i] << "\n" << data.irradIVTemp[i] << "\n" << data.unirradIVTemp[i] << "\n" << data.fluences[i] << "\n" << data.efluences[i] << "\n" << std::endl;
  //   }
  return data;
}
