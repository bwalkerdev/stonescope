#ifndef PLOT_H
#define PLOT_H

#include "TouchstoneFile.h"
#include <SFML/Graphics.hpp>

class Plot {
public:
  Plot() = delete;
  Plot(TouchstoneFile &file);
  int getWidth();
  int getHeight();
  void draw(sf::RenderTarget &target);

private:
  int _width;
  int _height;
  int _padding;
  sf::Color _bgColor;
  sf::Vector2f normalize();
  // INFO: Might need to be something other than Vector2f
  sf::Vector2f getNextPoint();
  TouchstoneFile &_file;
};

#endif // !PLOT_H
