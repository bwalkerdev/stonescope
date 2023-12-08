#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

/**
 * @class Line
 * @brief Represents a drawable line in a graphical application using SFML.
 *
 * Line class allows for the creation and manipulation of a line object.
 * It inherits from sf::Drawable and sf::Transformable for drawing and
 * transformation capabilities in SFML.
 */
class Line : public sf::Drawable, public sf::Transformable {
public:
  /**
   * @brief Constructor for Line class.
   */
  Line();

  /**
   * @brief Adds a point to the end of the line.
   * @param point The point to be added, of type sf::Vector2f.
   */
  void push_back(sf::Vector2f point);

  /**
   * @brief Removes the first point from the line.
   */
  void pop_front();

  /**
   * @brief Sets the color of the line.
   * @param color The color of the line, of type sf::Color.
   */
  void setColor(sf::Color color);

  /**
   * @brief Sets the thickness of the line.
   * @param thickness The thickness of the line, as a float.
   */
  void setThickness(float thickness);

  /**
   * @brief Gets the size of the bounding box of the line.
   * @return The size of the line's bounding box, as sf::Vector2f.
   */
  sf::Vector2f getSize() const;

  /**
   * @brief Generates the geometry of the line based on its points.
   *
   * This method updates the internal VertexArray to reflect any changes made to
   * the line's points.
   */
  void generateGeometry();

private:
  // Overridden from sf::Drawable.
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  std::deque<sf::Vector2f> _points; ///< Deque of points defining the line.
  sf::VertexArray _verticies;       ///< Vertex array to store line vertices.
  sf::Color _color;                 ///< Color of the line.
  float _thickness;                 ///< Thickness of the line.
};

#endif // !LINE_H
