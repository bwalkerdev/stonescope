#include <string>
#include <vector>

#ifndef TOUCHSTONE_FILE_H
#define TOUCHSTONE_FILE_H

class TouchstoneFile {
 public:
  enum class FrequencyUnit {
    HZ,
    KHZ,
    MHZ,
    GHZ,
  };
  enum class Parameter {
    S,
    Y,
    Z,
    H,
    G,
  };
  enum class Format { DB, MA, RI };
  struct DataPoint {
    double frequency;
    std::array<double, 2> s11, s21, s12, s22;
  };
  TouchstoneFile(const std::string& FILEPATH);
  ~TouchstoneFile();

 private:
  TouchstoneFile::FrequencyUnit _frequencyUnit;
  TouchstoneFile::Parameter _parameter;
  TouchstoneFile::Format _format;
  std::vector<DataPoint> _data;
  double _refResistance;
  void parseOptionLine(const std::string& optionLine);
  void readFile(const std::ifstream& FILE)
};

#endif  // TOUCHSTONE_FILE_H