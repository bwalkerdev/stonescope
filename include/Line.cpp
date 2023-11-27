#include "Line.h"

void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(_verticies, states);
}
