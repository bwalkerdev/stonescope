#include "Line.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

Line::Line() {}

void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(_verticies, states);
}

void Line::push_back(sf::Vector2f point) { _points.push_back(point); }

void Line::pop_front() { _points.pop_front(); }

void Line::setColor(sf::Color color) { _color = color; }

void Line::setThickness(float thickness) { _thickness = thickness; }

sf::Vector2f Line::getSize() const { return _verticies.getBounds().getSize(); }

void Line::generateGeometry() {
  _verticies.setPrimitiveType(sf::LineStrip);
  _verticies.clear();
  _verticies.resize(_points.size());
  for (unsigned long i = 0; i < _points.size(); ++i) {
    _verticies[i].position.x = _points.at(i).x;
    _verticies[i].position.y = -_points.at(i).y;
    _verticies[i].color = _color;
  }
}
