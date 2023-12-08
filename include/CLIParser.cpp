/**
 * @file CLIParser.cpp
 * @brief Implementation of the command line parser class
 * @author Bryce Walker
 */

#include "CLIParser.h"
#include <iostream>
#include <stdexcept>

CLIParser::CLIParser(int argc, char *argv[]) { _parse(argc, argv); }

void CLIParser::_parse(int argc, char *argv[]) {

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg[0] == '-') { // arg is a key
      std::string val = "";
      if (i + 1 < argc) {
        if (argv[i + 1][0] != '-') {
          val = argv[i + 1];
          i++;
        }
      }
      _args[arg] = val;
    } else {
      _fileNames.push_back(arg);
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

std::list<std::string> &CLIParser::getFiles() { return _fileNames; }
