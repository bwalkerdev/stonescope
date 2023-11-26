#include "Plot.h"
#include "TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Plot::Plot(TouchstoneFile &file) : _file(file) {
  _padding = 25; // TODO: Make selectable
  _width = static_cast<int>(_file.getMaxFreq() + _padding);
  _height = static_cast<int>(_file.getMaxRHS() + _padding);
  _bgColor = sf::Color::White;
}

void Plot::draw(sf::RenderTarget &target) {
  sf::RectangleShape background(sf::Vector2f(_width, _height));
  background.setFillColor(_bgColor);
  target.draw(background);
}

int Plot::getWidth() { return _width; }

int Plot::getHeight() { return _height; }
