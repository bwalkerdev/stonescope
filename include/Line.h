#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Line {
public:
  void draw(sf::RenderTarget &target);

private:
  sf::Color _color;
  sf::Vector2f _currentPoint;
  sf::Vector2f _nextPoint;
};

#endif // !LINE_H
