#include "../include/Plot.h"
#include "../include/TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

int main() {
  int windowWidth = 1080;
  int windowHeight = 720;
  // Setup Resources
  sf::Font jetBrainsMono;
  if (!jetBrainsMono.loadFromFile(
          "./resources/JetBrainsMonoNerdFont-Medium.ttf")) {
    std::cout << "Error loading font" << std::endl;
  }
  sf::Text text;
  text.setFont(jetBrainsMono);
  text.setString(L"   STONKS"); // NOTE: L allows non-ascii characters
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);

  // Read Touchstone File
  TouchstoneFile file;
  file.open("./data/example.S2P");
  std::cout << "Finished" << std::endl;

  // Setup Plot
  int margin = 50;
  Plot plot(file, windowWidth, windowHeight, margin);

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "stonescope");

  // Main Loop
  sf::Event event;
  while (window.isOpen()) {
    window.clear();

    window.draw(text);
    plot.draw(window);

    window.display();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  return 0;
}
