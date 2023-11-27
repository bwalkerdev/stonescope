#include "Plot.h"
#include "TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

Plot::Plot(TouchstoneFile &file, const int windowWidth, const int windowHeight,
           const int margin)
    : _file(file) {
  _margin = margin;
  _width = (windowWidth - 2 * _margin);
  _height = (windowHeight - 2 * _margin);
  _bgColor = sf::Color::White;
  _padding = 50;
  _lineThickness = 3;
  _stepSize = 1;
  _origin = sf::Vector2f(_margin + _padding, _margin + _height - _padding);
}

void Plot::draw(sf::RenderTarget &target) {
  drawBackground(target);
  drawAxes(target);
}

int Plot::getWidth() { return _width; }

int Plot::getHeight() { return _height; }

void Plot::drawBackground(sf::RenderTarget &target) {
  sf::RectangleShape background(sf::Vector2f(_width, _height));
  background.setOrigin(sf::Vector2f(0, _height));
  background.setPosition(sf::Vector2f(_margin, _margin + _height));
  background.setFillColor(_bgColor);
  target.draw(background);
}

void Plot::drawAxes(sf::RenderTarget &target) {
  // TEXT
  sf::Font jetBrainsMono;
  if (!jetBrainsMono.loadFromFile(
          "./resources/JetBrainsMonoNerdFont-Medium.ttf")) {
    throw std::invalid_argument("./resources/JetBrainsMonoNerdFont-Medium.ttf");
    std::cerr << "Error loading font" << std::endl;
  }
  sf::Text text;
  text.setFont(jetBrainsMono);
  text.setCharacterSize(8);
  text.setFillColor(sf::Color::Black);

  // TICKS
  sf::RectangleShape xAxis(sf::Vector2f(_width - _padding * 2, _lineThickness));
  sf::RectangleShape yAxis(
      sf::Vector2f(_lineThickness, _height - _padding * 2));
  yAxis.setOrigin(yAxis.getSize());
  xAxis.setPosition(_origin);
  yAxis.setPosition(_origin);
  xAxis.setFillColor(sf::Color::Blue);
  yAxis.setFillColor(sf::Color::Blue);
  target.draw(xAxis);
  target.draw(yAxis);
  int yAxisMax = std::ceil(_file.getMaxLHS()); // TODO: Make selectable
  int yAxisMin = static_cast<int>(_file.getMinLHS());
  int deltaY = yAxisMax - yAxisMin;
  int yNumSteps = deltaY / _stepSize;
  double pixelStepSize = yAxis.getSize().y / static_cast<double>(yNumSteps);

  // LOOP VARIABLES
  sf::Vector2f currentPosition = _origin - sf::Vector2f(6, pixelStepSize);
  int currentYVal = yAxisMin + _stepSize;
  for (int i = 0; i < yNumSteps; i++) {
    sf::RectangleShape tick(sf::Vector2f(9, _lineThickness));
    tick.setFillColor(sf::Color::Red);
    tick.setPosition(currentPosition);
    target.draw(tick);
    text.setString(std::to_string(currentYVal));
    // Calculate the width of the text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.getSize());
    // Set the position
    text.setPosition(currentPosition -
                     sf::Vector2f(9, -(textRect.getSize().y / 2.0)));
    target.draw(text);
    // Update loop variables
    currentPosition -= sf::Vector2f(0, pixelStepSize);
    currentYVal += _stepSize;
  }
}
