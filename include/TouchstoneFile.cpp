#include "TouchstoneFile.h"
#include "Options.h"
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

TouchstoneFile::TouchstoneFile() { _setDefaults(); }

TouchstoneFile::TouchstoneFile(const std::string FILEPATH) { open(FILEPATH); }

TouchstoneFile::~TouchstoneFile() {
  std::cout << "Called ~TouchstoneFile" << std::endl; // FIXME: Acutally clean
                                                      // up resources
}

void TouchstoneFile::_setDefaults() {
  // From Touchstone file spec
  _numPorts = 2;
  _freqT = FrequencyType::GHz;
  _paramT = ParameterType::S;
  _paramFmt = ParameterFormat::MA;
  _refRes = 50;
}

void TouchstoneFile::open(const std::string FILEPATH) {
  // Find the position of 's' and 'p' in the filename, the number between them
  // gives us the number of ports
  size_t posS = FILEPATH.rfind('S'); // FIXME: This only works if S is capital
  size_t posP = FILEPATH.rfind('P'); // FIXME: This only works if p is capital

  if (posS != std::string::npos && posP != std::string::npos && posS < posP) {
    std::string portStr = FILEPATH.substr(posS + 1, posP - posS - 1);

    // Convert the extracted string to an integer
    try {
      _numPorts = std::stoi(portStr);
    } catch (const std::exception &) {
      std::cerr << "Invalid port number in filename: " << FILEPATH << std::endl;
      throw;
    }
  } else {
    std::cerr << "Invalid filename format: " << FILEPATH << std::endl;
    throw std::invalid_argument("Invalid filename format");
  }

  // Open file
  std::ifstream file;
  file.open(FILEPATH);

  if (file.fail()) {
    std::cerr << "Unable to open file: " << FILEPATH << std::endl;
    throw std::invalid_argument("Invalid file path");
  }

  _parseOptionLine(file);
  _parseDataLines(file);
}

void TouchstoneFile::_parseOptionLine(std::ifstream &file) {
  std::string line;

  while (std::getline(file, line)) {
    if (!line.empty() && line.at(0) == '#') {
      std::stringstream lineStream(line);
      std::string token;

      // Skip # char
      lineStream >> token;

      _setDefaults();

      while (lineStream >> token) {
        for (size_t i = 0; i < token.length(); ++i) {
          token.at(i) = tolower(token.at(i));
        }
        if (token == "ghz" || token == "mhz" || token == "khz" ||
            token == "ghz") {
          _freqT = _parseFreqT(token);
        } else if (token == "s" || token == "y" || token == "z" ||
                   token == "h" || token == "g") {
          _paramT = _parseParamT(token);
        } else if (token == "ma" || token == "db" || token == "ri") {
          _paramFmt = _parseParamFmt(token);
        } else if (token == "r") {
          double refRes;
          if (lineStream >> refRes) {
            _refRes = refRes;
          }
        }
      }
      break; // Break after processing the option line
    }
  }
}

void TouchstoneFile::_parseDataLines(std::ifstream &file) {
  std::string line;

  while (std::getline(file, line)) {
    // Check for comment
    if (!line.empty() && line.at(0) != '!') {
      std::stringstream lineStream(line);
      std::string token;
      DataPoint *point = new DataPoint;

      lineStream >> token;                 // Get frequency value
      point->frequency = std::stod(token); // WARNING: Could throw

      bool lhs = true;

      while (lineStream >> token) {
        if (lhs) {
          point->lhs.push_back(std::stod(token)); // WARNING: Could throw
        } else {
          point->rhs.push_back(std::stod(token));
        }
        lhs = !lhs;
      }
      _originalData.push_back(point);
    }
  }
}

FrequencyType TouchstoneFile::_parseFreqT(const std::string &TOKEN) {
  if (TOKEN == "ghz") {
    return FrequencyType::GHz;
  } else if (TOKEN == "mhz") {
    return FrequencyType::MHz;
  } else if (TOKEN == "khz") {
    return FrequencyType::KHz;
  } else if (TOKEN == "hz") {
    return FrequencyType::Hz;
  }

  std::cerr << "Unknown frequency type: " << TOKEN << std::endl;
  throw std::invalid_argument("Invalid frequency type token");
}

ParameterType TouchstoneFile::_parseParamT(const std::string &TOKEN) {
  if (TOKEN == "s") {
    return ParameterType::S;
  } else if (TOKEN == "y") {
    return ParameterType::Y;
  } else if (TOKEN == "z") {
    return ParameterType::Z;
  } else if (TOKEN == "h") {
    return ParameterType::H;
  } else if (TOKEN == "g") {
    return ParameterType::G;
  }

  std::cerr << "Unknown parameter type: " << TOKEN << std::endl;
  throw std::invalid_argument("Invalid parameter type token");
}

ParameterFormat TouchstoneFile::_parseParamFmt(const std::string &TOKEN) {
  if (TOKEN == "ma") {
    return ParameterFormat::MA;
  } else if (TOKEN == "db") {
    return ParameterFormat::DB;
  } else if (TOKEN == "ri") {
    return ParameterFormat::RI;
  }

  std::cerr << "Unknown parameter format: " << TOKEN << std::endl;
  throw std::invalid_argument("Invalid parameter format token");
}
