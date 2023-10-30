
#include "TouchstoneFile.H"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

TouchstoneFile::TouchstoneFile(const std::string& FILEPATH) {
  // Setup defaults
  _frequencyUnit = FrequencyUnit::GHZ;
  _parameter = Parameter::S;
  _format = Format::MA;
  _refResistance = 50;
  // TODO: Handle non-two port files

  // Read in config from file
  std::ifstream file(FILEPATH);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return;  // FIXME Gracefully handle this
  }
  std::string currentLine;
  while (std::getline(file, currentLine)) {
    if (currentLine.empty() || currentLine.at(0) == '!') continue;
    if (currentLine.at(0) == '#') {
      parseOptionLine(currentLine);
      break;
    };
  }

  // Read the rest of the data in
  readFile();

  // TODO Handle baseline data or whatever they call it
}

TouchstoneFile::parseOptionLine(const std::string& optionLine) {
  std::istringstream iss(optionLine);
  std::string token;

  while (iss >> token) {
    toupper(token);
    if (token == "HZ")
      _frequencyUnit = FrequencyUnit::HZ;
    else if (token == "KHZ")
      _frequencyUnit = FrequencyUnit::KHZ;
    else if (token == "MHZ")
      _frequencyUnit = FrequencyUnit::MHZ;
    else if (token == "GHZ")
      _frequencyUnit = FrequencyUnit::GHZ;
    else if (token == "S")
      _parameter = Parameter::S;
    else if (token == "Y")
      _parameter = Parameter::Y;
    else if (token == "Z")
      _parameter = Parameter::Z;
    else if (token == "H")
      _parameter = Parameter::H;
    else if (token == "G")
      _parameter = Parameter::G;
    else if (token == "DB")
      _format = Format::DB;
    else if (token == "MA")
      _format = Format::MA;
    else if (token == "RI")
      _format = Format::RI;
    else if (token.at(0) ==
             'R') {  // TODO: maybe .at() not necessary. verify later, value
                     // might be appended to R (eg. R50)
      iss >> _refResistance;  // TODO: double check if this works properly
    }
    // FIXME Handle Unknowns
  }
}

TouchstoneFile::readFile(const std::ifstream& FILE) {
  std::string currentLine;
  while (std::getline(FILE, currentLine)) {
    if (currentLine.empty() || currentLine.at(0) == '!' ||
        currentLine.at(0) == '#')
      continue;
    std::istringstream(currentLine) token;
    double freq, s11, s21, s12, s22;
    token >> freq;
    token >> s11_L;
    token >> s11_R;
    token >> s21_L;
    token >> s21_R;
    token >> s12_L;
    token >> s12_R;
    token >> s22_L;
    token >> s22_R;
    DataPoint point = {
      freq,
      {

      }
    }
  }
}