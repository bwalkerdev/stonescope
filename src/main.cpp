#include "../include/TSPlot.h"
#include "../include/TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

int main() {
  // important things to grab from user at startup or by cli
  // 1. filepath
  // 2. window size
  // 3. plot type (s2p, s1p, s3p, s4p)
  // 4. plot lhs or rhs
  // 5. output to display or file
  //

  std::string filePath = "./data/example-large.S2P";

  int windowWidth = 2000;
  int windowHeight = 1200;
  // Setup Resources
  sf::Font jetBrainsMono;
  if (!jetBrainsMono.loadFromFile(
          "./resources/JetBrainsMonoNerdFont-Medium.ttf")) {
    std::cout << "Error loading font" << std::endl;
  }

  // Read Touchstone File
  TouchstoneFile file;
  file.open("./data/example-large.S2P");
  std::cout << "Finished" << std::endl;

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

  sf::Text text;
  text.setFont(jetBrainsMono);
  text.setString("Plotting: " +
                 filePath); // NOTE: L allows non-ascii characters
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(margin, margin / 4.0);

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "stonescope");

  // Main Loop
  sf::Event event;
  while (window.isOpen()) {
    window.clear();

    window.draw(text);
    // plot.draw(window);
    window.draw(tsPlot);

    window.display();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  return 0;
}
