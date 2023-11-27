#ifndef PLOT_H
#define PLOT_H

#include "TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Plot {
public:
  Plot() = delete;
  Plot(TouchstoneFile &file, const int windowWidth, const int windowHeight,
       const int margin);
  int getWidth();
  int getHeight();
  void draw(sf::RenderTarget &target);

private:
  int _width;
  int _height;
  int _padding;
  int _margin;
  int _lineThickness;
  int _stepSize;
  sf::Vector2f _origin;
  sf::Color _bgColor;
  sf::Vector2f normalize();
  // INFO: Might need to be something other than Vector2f
  sf::Vector2f getNextPoint();
  TouchstoneFile &_file;
  void drawBackground(sf::RenderTarget &target);
  void drawAxes(sf::RenderTarget &target);
};

#endif // !PLOT_H
