#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Line : public sf::Drawable, public sf::Transformable {
public:
  Line();

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  sf::VertexArray _verticies;
  sf::Color _color;
};

#endif // !LINE_H
