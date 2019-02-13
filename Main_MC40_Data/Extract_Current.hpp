#include <vector>

class Data
{
public:
  int diodeNumber;
  double fluence;
  double depletion;
  std::vector<double> current;
  std::vector<double> voltage;
  std::vector<double> ecurrent;
  std::vector<double> evoltage;
};
