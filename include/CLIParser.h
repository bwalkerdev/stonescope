#ifndef CLIPARSER_H
#define CLIPARSER_H

#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @class CLIParser
 * @brief The CLIParser class is responsible for parsing command line arguments.
 */
class CLIParser {
public:
  CLIParser() = delete;

  /**
   * @brief Construct a new CLIParser from cli arguments
   *
   * @param argc Count of cli arguments
   * @param argv Cli arguments
   */
  CLIParser(int argc, char *argv[]);

  /**
   * @brief Retrieves the value of a command line argument.
   * @param arg The command line argument.
   * @return The value of the command line argument.
   * @throws std::invalid_argument if the command line argument is not valid.
   */
  std::string getArg(const std::string ARG) const;

  /**
   * @brief Check if the parser has a flag
   *
   * @param ARG Flag to check for
   * @return Turn if the flag is present
   */
  bool hasFlag(const std::string ARG) const;

  /**
   * @brief Prints the help message.
   */
  void printHelp() const;

  /**
   * @brief Set the description (Help Menu)
   */
  void setDescription(const std::string DESCRIPTION);

  /**
   * @brief Get the list of files
   */
  std::list<std::string> &getFiles();

private:
  /**
   * @brief Parses the command line arguments.
   * @param argc The number of command line arguments.
   * @param argv The array of command line arguments.
   */
  void _parse(int argc, char *argv[]);

  std::unordered_map<std::string, std::string>
      _args; /**< The map of command line arguments and their values. */

  std::list<std::string> _fileNames; /**< The list of _fileNames. */

  std::string
      _description; /**< The description of the command line arguments. */
};

#endif // CLIPARSER_H
