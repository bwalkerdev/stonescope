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

sf::Text *buildText(std::string inFile, sf::Font &font, int margin) {
  sf::Text *text = new sf::Text();
  text->setFont(font);
  text->setString("Touchstone Plot: " +
                  inFile); // NOTE: L allows non-ascii characters
  text->setCharacterSize(24);
  text->setFillColor(sf::Color::White);
  text->setPosition(margin, margin / 4.0); //
  return text;
}

TSPlot *buildPlot(std::string inFile, sf::Font &font, int winWidth,
                  int winHeight, int margin) {

  TouchstoneFile *file = new TouchstoneFile();
  file->open(inFile);

  TSPlot *tsPlot = new TSPlot(*file, font);
  tsPlot->setWidth(winWidth - 2 * margin);
  tsPlot->setHeight(winHeight - 2 * margin);
  tsPlot->setBgColor(sf::Color::White);
  tsPlot->setPosition(margin, margin);
  tsPlot->setPadding(100);
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
}

int main(int argc, char *argv[]) {
  // Default Values
  std::string inFile;
  std::string outFile;
  int windowWidth = 1920;
  int windowHeight = 1080;
  bool outputToFile;

  CLIParser cli(argc, argv);
  cli.setDescription(
      "\nProgram Usage:\n"
      "  <input path>     : File to plot\n"
      "  -o <output path> : Output path for img. Omit flag for GUI\n"
      "  -w <width>       : Window or img width\n"
      "  -h <height>      : Window or img height\n"
      "  --help           : Display this help message\n"
      "\nExample: stonescope ./in.S2P -o ./out.png");
  // important things to grab from user at startup or by cli
  // 1. filepath
  // 2. window size
  // 3. plot type (s2p, s1p, s3p, s4p)
  // 4. plot lhs or rhs
  // 5. output to display or file

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
        buildPlot(fileName, jetBrainsMono, windowWidth, windowHeight, 50);

    sf::Text *pText = buildText(fileName, jetBrainsMono, 50);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "stonescope");

    // Main Loop
    sf::Event event;
    while (window.isOpen()) {
      window.clear();
      window.draw(*pText);
      window.draw(*pPlot);
      if (outputToFile) {
        sf::Texture texture;
        texture.create(windowWidth, windowHeight);
        texture.update(window);
        sf::Image image = texture.copyToImage();
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
    delete pPlot;
    delete pText;
  }

  return 0;
}
