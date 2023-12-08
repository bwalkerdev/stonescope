/**
 * @file Axis.h
 * @brief Definition of the axis class. Builds an axis for use in the TSPlot
 * class.
 * @author Bryce Walker
 */

#ifndef AXIS_H
#define AXIS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>

/**
 * @class Axis
 * @brief Represents a graphical axis (either X or Y) in a chart or graph.
 *
 * Axis class is responsible for drawing an axis, including its ticks and
 * labels. It inherits from sf::Drawable and sf::Transformable to utilize SFML's
 * drawing and transformation capabilities.
 */
class Axis : public sf::Drawable, public sf::Transformable {

public:
  /**
   * @brief Constructor for the Axis class.
   * @param font Reference to an sf::Font object used for drawing text.
   */
  Axis(sf::Font &font);

  /**
   * @brief Default destructor.
   */
  ~Axis() = default;

  /**
   * @enum AxisType
   * @brief Enumerates the types of axes, either X or Y.
   */
  enum class AxisType { X, Y };

  /**
   * @brief Sets the thickness of the axis line.
   * @param lineThickness The thickness of the line.
   */
  void setLineThickness(double lineThickness);

  /**
   * @brief Sets the minimum value of the axis.
   * @param min The minimum axis value.
   */
  void setMin(double min);

  /**
   * @brief Sets the maximum value of the axis.
   * @param max The maximum axis value.
   */
  void setMax(double max);

  /**
   * @brief Sets the type of the axis (X or Y).
   * @param type The axis type.
   */
  void setType(AxisType type);

  /**
   * @brief Sets the length of the axis.
   * @param length The length of the axis.
   */
  void setLength(double length);

  /**
   * @brief Sets the color of the axis line.
   * @param color The color of the axis line.
   */
  void setAxisColor(sf::Color color);

  /**
   * @brief Sets the color of the tick marks on the axis.
   * @param color The color of the ticks.
   */
  void setTickColor(sf::Color color);

  /**
   * @brief Sets the step size between ticks on the axis.
   * @param stepSize The step size.
   */
  void setStepSize(double stepSize);

  /**
   * @brief Sets the font used for axis labels and numbers.
   * @param font The font to be used.
   */
  void setFont(const sf::Font &font);

  /**
   * @brief Sets the label for the axis.
   * @param label The label of the axis.
   */
  void setLabel(const std::string label);

  /**
   * @brief Sets the padding around the axis.
   * @param padding The padding value.
   */
  void setPadding(double padding);

private:
  // Overridden from sf::Drawable.
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  // Private member variables.
  double _stepSize;
  double _lineThickness;
  double _length;
  double _min;
  double _max;
  double _padding;
  AxisType _type;
  sf::Color _axisColor;
  sf::Color _tickColor;
  sf::Font &_font;
  std::string _axisLabel;

  /**
   * @enum TextType
   * @brief Enumerates the types of text used in the axis, either NUMBER or
   * LABEL.
   */
  enum class TextType { NUMBER, LABEL };

  // Private member functions.
  double _calcTextSize(TextType type) const;
  void _setupAxis(sf::RectangleShape &axis) const;
  void _setupTick(sf::RectangleShape &tick, const double pixelStepSize) const;
  void _setupNumbers(sf::Text &text) const;
  void _setupAxisLabels(sf::Text &text) const;
  int _calcTickCount() const;
  double _calcPixelStepSize() const;
  void _updateTickPosition(sf::RectangleShape &tick,
                           double pixelStepSize) const;
  void _setNumberPosition(sf::Text &text, const sf::Vector2f offset,
                          const sf::RectangleShape tick,
                          const int iteration) const;
};

#endif // !AXIS_H
