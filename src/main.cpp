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
      "  -f <input path>  : File to plot\n"
      "  -o <output path> : Output path for img. Omit flag for GUI\n"
      "  -w <width>       : Window or img width\n"
      "  -h <height>      : Window or img height\n"
      "  --help           : Display this help message\n"
      "\nExample: stonescope -f ./in.S2P -o ./out.png");
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
    inFile = cli.getArg("-f");
  } catch (...) {
    std::cout << "Error: No input file specified" << std::endl;
    cli.printHelp();
    return 2;
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

  // Setup Resources
  sf::Font jetBrainsMono;
  if (!jetBrainsMono.loadFromFile(
          "./resources/JetBrainsMonoNerdFont-Medium.ttf")) {
    std::cout << "Error loading font" << std::endl;
  }
  // Read Touchstone File
  // filePath = "./data/1.S2P";
  TouchstoneFile file;
  file.open(inFile);

  // Setup Plot
  int margin = 50;
  // Plot plot(file, windowWidth, windowHeight, margin);
  //
  //
  TSPlot tsPlot(file, jetBrainsMono);

  tsPlot.setWidth(windowWidth - 2 * margin);
  tsPlot.setHeight(windowHeight - 2 * margin);
  tsPlot.setBgColor(sf::Color::White);
  tsPlot.setPosition(margin, margin);
  tsPlot.setPadding(100);
  tsPlot.setLineThickness(3);
  tsPlot.setAxisColor(sf::Color::Black);
  tsPlot.setAxisStepSize(sf::Vector2f(1, 1));
  tsPlot.setXAxisLabel("Frequency (GHz)");
  tsPlot.setYAxisLabel("Magnitude (dB)");
  tsPlot.addLine(0, sf::Color::Red);
  tsPlot.addLine(1, sf::Color::Blue);
  tsPlot.addLine(2, sf::Color::Green);
  tsPlot.addLine(3, sf::Color::Magenta);

  sf::Text text;
  text.setFont(jetBrainsMono);
  text.setString("Touchstone Plot: " +
                 inFile); // NOTE: L allows non-ascii characters
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(margin, margin / 4.0);

  tsPlot.generateGeometry();
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "stonescope");

  // Main Loop
  sf::Event event;
  while (window.isOpen()) {
    window.clear();

    window.draw(text);
    // plot.draw(window);
    window.draw(tsPlot);

    if (outputToFile) {
      sf::Texture texture;
      texture.create(windowWidth, windowHeight);
      texture.update(window);
      sf::Image image = texture.copyToImage();
      image.saveToFile(outFile);
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

  return 0;
}
