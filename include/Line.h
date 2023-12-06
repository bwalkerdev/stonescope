#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

class Line : public sf::Drawable, public sf::Transformable {
public:
  Line();
  void push_back(sf::Vector2f point);
  void pop_front();
  void setColor(sf::Color color);
  void setThickness(float thickness);
  sf::Vector2f getSize() const;
  void generateGeometry();

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  std::deque<sf::Vector2f> _points;
  sf::VertexArray _verticies;
  sf::Color _color;
  float _thickness;
};

#endif // !LINE_H
