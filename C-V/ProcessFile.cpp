#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct Data
{
  std::vector<double> Voltages; //(V)
  std::vector<double> Currents; //(A)
  std::vector<double> eVoltages; //(V)
  std::vector<double> eCurrents; //(A)
};

double StdDev(double c1, double c2, double c3, double c4, double c5, double mean)
{
  double sumSquares = pow(c1-mean,2) + pow(c2-mean,2) + pow(c3-mean,2) + pow(c4-mean,2) + pow(c5-mean,2);
  return pow(sumSquares/4.,0.5); 
}

Data ReadFile(std::string filePath, std::string fileHeaderStart)
{
  ifstream inFile;
  ofstream outFile;
  inFile.open(filePath);
  outFile.open("testOutputFile.txt");
  Data data;
  std::vector<double> Voltage;
  std::vector<double> Current;
  double currentMean{0};

  if(!outFile.good())
    {
      std::cout << "Error Creating Output File" << std::endl;
    }
  
  if(!inFile.good())
    {
      std::cout << "Error Opening Input File" << std::endl;
    }
  else if (inFile.good())
    {
      std::string line{""};
      std::string timeStamp{""};
      double voltage{}, current{};
      int linecount{1};
      while(!inFile.eof())
	{
	  getline(inFile,line);
	  if(line.find(fileHeaderStart) == 0)
	    {
	      //std::cout << line << std::endl;
	    }
	  else if(linecount > 18)
	    {
	      stringstream ss(line);
	      ss >> timeStamp >> voltage >> current;
	      //std ::cout << timeStamp << "\t" << voltage << "\t" << current << std::endl;
	      Voltage.push_back(voltage);
	      Current.push_back(current);
	    }  
	  ++linecount;
	}
    }

  int n{0};
  for(int i{0}; i<=Voltage.size(); ++i)
    {
      if(n != 5){++n;}
      else if(n == 5)
	{
	  n = 1;
	  data.Voltages.push_back((Voltage[i-1] + Voltage[i-2] + Voltage[i-3] + Voltage[i-4] +Voltage[i-5])/5.);
	  data.eVoltages.push_back(0.05);
	  currentMean = (Current[i-1] + Current[i-2] + Current[i-3] + Current[i-4] +Current[i-5])/5.;
	  data.Currents.push_back(currentMean);
	  data.eCurrents.push_back(StdDev(Current[i-1],Current[i-2],Current[i-3],Current[i-4],Current[i-5],currentMean));
	}      
    }
  for(int i{0}; i<data.Voltages.size(); ++i)
    {
      std::cout << data.Voltages[i] << " +/- " << data.eVoltages[i] << "\t\t" << data.Currents[i] << " +/- " << data.eCurrents[i] << std::endl;

      outFile << data.Voltages[i] << "\t" << data.Currents[i] << "\t" << data.eVoltages[i] << "\t" << data.eCurrents[i] << std::endl;
    }
  return data;
}

void ProcessFile()
{
  std::string filePath = "../../ALiBaVa/ATLAS17minis_GammaIrrad/I-V/Post_Anneal/ATLAS17_10Mrad_PostAnneal_IV_16-11-2018.txt";
  std::string fileHeaderStart{"Time/Date"};

  Data data = ReadFile(filePath, fileHeaderStart);  
}
