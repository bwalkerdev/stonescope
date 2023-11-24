#include "DataPoint.h"
#include "Options.h"
#include <fstream>
#include <string>
#include <vector>

#ifndef TOUCHSTONE_FILE_H
#define TOUCHSTONE_FILE_H

#include <vector>
/**
 * @class TouchstoneFile
 * @brief Class used to read in and parse a Touchstone File
 *
 */
class TouchstoneFile {
public:
  /**
   * @brief Build a Touchstone File and set all options to default
   */
  TouchstoneFile();  // constructor
  ~TouchstoneFile(); // TODO: Rule of 3
  TouchstoneFile(TouchstoneFile &other);
  TouchstoneFile operator=(TouchstoneFile &other);

  /**
   * @brief Build and open a Touchstone file. Set parameters based on file
   * parameters
   *
   * @param FILEPATH
   */
  TouchstoneFile(const std::string FILEPATH);

  /**
   * @brief Open a Touchstone file. Set parameters based on file parameters
   *
   * @param FILEPATH
   */
  void open(const std::string FILEPATH);

private:
  /**
   * @brief Set defaults based upon Touchstone File Spec
   */
  void _setDefaults();
  void _parseOptionLine(std::ifstream &file);
  void _parseDataLines(std::ifstream &file);
  FrequencyType _parseFreqT(const std::string &TOKEN);
  ParameterType _parseParamT(const std::string &TOKEN);
  ParameterFormat _parseParamFmt(const std::string &TOKEN);
  int _numPorts;
  std::vector<DataPoint *> _originalData;
  FrequencyType _freqT;
  ParameterType _paramT;
  ParameterFormat _paramFmt;
  double _refRes;
};

#endif // !TOUCHSTONE_FILE_H
