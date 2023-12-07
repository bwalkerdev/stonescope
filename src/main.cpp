#include "../include/CLIParser.h"
#include "../include/TSPlot.h"
#include "../include/TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

/**
 * @brief Build a text object containing the file name
 *
 * @param inFile Filename to display
 * @param font Font to be used
 * @param margin  Plot margin. Used to calc text placement
 * @param charSize Font size
 * @return Text object
 */
sf::Text *buildText(std::string inFile, sf::Font &font, int margin,
                    int charSize) {
  sf::Text *text = new sf::Text();
  text->setFont(font);
  text->setString("Touchstone Plot: " +
                  inFile); // NOTE: L allows non-ascii characters
  text->setCharacterSize(charSize);
  text->setFillColor(sf::Color::White);
  text->setPosition(margin, margin / 4.0); //
  return text;
}

/**
 * @brief Build a TSPlot object
 *
 * @param inFile  Filename to plot
 * @param font  Font to be used
 * @param winWidth Total width of window
 * @param winHeight Total height of window
 * @param margin  Margin around plot
 * @return TSPlot object on success, nullptr on failure
 */
TSPlot *buildPlot(std::string inFile, sf::Font &font, int winWidth,
                  int winHeight, int margin) {

  TouchstoneFile *file = new TouchstoneFile();
  try {
    file->open(inFile);

    TSPlot *tsPlot = new TSPlot(*file, font);
    tsPlot->setWidth(winWidth - 2 * margin);
    tsPlot->setHeight(winHeight - 2 * margin);
    tsPlot->setBgColor(sf::Color::White);
    tsPlot->setPosition(margin, margin);
    tsPlot->setPadding((winWidth + winHeight / 2.0) * 0.07);
    tsPlot->setLineThickness(3);
    tsPlot->setAxisColor(sf::Color::Black);
    tsPlot->setAxisStepSize(sf::Vector2f(1, 1));
    tsPlot->setXAxisLabel("Frequency (GHz)");
    tsPlot->setYAxisLabel("Magnitude (dB)");
    tsPlot->addLine(0, sf::Color::Red);
    tsPlot->addLine(1, sf::Color::Blue);
    tsPlot->addLine(2, sf::Color::Green);
    tsPlot->addLine(3, sf::Color::Magenta);
    tsPlot->generateGeometry();
    return tsPlot;
  } catch (...) {
    delete file;
    std::cerr << "Error: Unable to open provided file" << std::endl;
    return nullptr;
  }
}

/**
 * @brief Main entry point for program
 *
 * @param argc Count of command line arguments
 * @param argv Command line arguments
 * @return int 0 on success, non-zero on failure
 */
int main(int argc, char *argv[]) {
  // Default Values
  std::string inFile;
  std::string outFile;
  int windowWidth = 1080;
  int windowHeight = 720;
  bool outputToFile;

  CLIParser cli(argc, argv);
  cli.setDescription(
      "\n== Program Usage ==\n"
      "  <input path>     : File to plot. You can provide multiple files in\n"
      "                     image mode. GUI mode only supports one file\n"
      "  -o <output path> : Output path for image. Omit flag to run in GUI\n"
      "                     mode.\n"
      "  -w <width>       : Window or image width. Default is 1080px\n"
      "  -h <height>      : Window or image height. Default is 720px\n"
      "  --help           : Display this help message\n"
      "\nExample: stonescope ./data/in.S2P -w 1920 -h 1080\n"
      "Example: stonescope ./data/1.s2p ./2.s2p o ./output/data.png\n");

  if (argc == 1) {
    cli.printHelp();
    return 1;
  }

  if (cli.hasFlag("--help")) {
    cli.printHelp();
    return 0;
  }

  try {
    windowWidth = std::stoi(cli.getArg("-w"));
  } catch (...) {
  }

  try {
    windowHeight = std::stoi(cli.getArg("-h"));
  } catch (...) {
  }

  try {
    outFile = cli.getArg("-o");
    outputToFile = true;
    std::cout << "== Running in IMG mode ==" << std::endl;
  } catch (...) {
    outputToFile = false;
    std::cout << "== Running in GUI mode ==" << std::endl;
  }

  std::list<std::string> &files = cli.getFiles();

  if (files.empty()) {
    std::cout << "Error: No input files specified" << std::endl;
    cli.printHelp();
    return 2;
  } else if (files.size() > 1 && !outputToFile) {
    std::cout << "Error: GUI only supports plotting one file at a time"
              << std::endl;
    return 3;
  }

  // Setup Resources
  sf::Font jetBrainsMono;
  if (!jetBrainsMono.loadFromFile(
          "./resources/JetBrainsMonoNerdFont-Medium.ttf")) {
    std::cout << "Error loading font" << std::endl;
  }

  int fileIDX = 0;
  for (auto &fileName : files) {
    std::cout << "Plotting: " << fileName << std::endl;
    TSPlot *pPlot =
        buildPlot(fileName, jetBrainsMono, windowWidth, windowHeight,
                  (windowWidth + windowHeight / 2.0) * 0.03);

    if (pPlot == nullptr) {
      return 4; // Invalid file
    }

    sf::Text *pText = buildText(fileName, jetBrainsMono,
                                (windowWidth + windowHeight / 2.0) * 0.03,
                                (windowWidth + windowHeight / 2.0) * 0.0175);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "stonescope");

    // Main Loop
    sf::Event event;
    while (window.isOpen()) {
      window.clear();
      window.draw(*pText);
      window.draw(*pPlot);
      if (outputToFile) {
        // Image logic
        sf::Texture texture;
        texture.create(windowWidth, windowHeight);
        texture.update(window);
        sf::Image image = texture.copyToImage();
        // Add index to file name if multiple files are provided
        if (files.size() > 1) {
          std::string iterOutFile = outFile;
          unsigned long dotIDX = iterOutFile.find_last_of('.');
          iterOutFile.insert(dotIDX, "-" + std::to_string(fileIDX));
          image.saveToFile(iterOutFile);
        } else {
          image.saveToFile(outFile);
        }
        window.close();
      } else {
        window.display();
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
          }
        }
      }
    }
    ++fileIDX;

    // Clean up resources
    delete pPlot;
    delete pText;
  }

  return 0;
}
