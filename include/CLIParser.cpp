#include "CLIParser.h"
#include <iostream>
#include <stdexcept>

CLIParser::CLIParser(int argc, char *argv[]) { _parse(argc, argv); }

void CLIParser::_parse(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    std::string key = argv[i];
    if (key[0] == '-') {
      if (i + 1 < argc) {
        _args[key] = argv[i + 1];
      } else {
        _args[key] = "";
      }
    }
  }
}

std::string CLIParser::getArg(const std::string arg) const {
  std::string val = "";
  try {
    val = _args.at(arg);
  } catch (...) {
    throw std::invalid_argument(arg + " is not a valid argument");
  }
  return val;
}

void CLIParser::printHelp() const { std::cout << _description << std::endl; }

void CLIParser::setDescription(const std::string DESCRIPTION) {
  _description = DESCRIPTION;
}

bool CLIParser::hasFlag(const std::string ARG) const {
  try {
    _args.at(ARG);
  } catch (...) {
    return false;
  }
  return true;
}
