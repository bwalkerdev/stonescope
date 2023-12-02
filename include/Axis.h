#ifndef AXIS_H
#define AXIS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <tuple>

enum class AxisType { X, Y };

class Axis : public sf::Drawable, public sf::Transformable {

public:
  Axis(sf::Font &font);
  ~Axis() = default;
  void setLineThickness(double lineThickness);
  void setMin(double min);
  void setMax(double max);
  void setType(AxisType type);
  void setLength(double length);
  void setAxisColor(sf::Color color);
  void setTickColor(sf::Color color);
  void setStepSize(double stepSize);
  void setFont(const sf::Font &font);
  void setYAxisLabel(std::string label);
  struct AxisLabelContainer {
    std::string x;
    std::string y;
  };
  void setXAxisLabel(std::string label);
  // TODO: Add function for getting size of axis

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  double _stepSize;
  double _lineThickness;
  double _length;
  double _min;
  double _max;
  AxisType _type;
  sf::Color _axisColor;
  sf::Color _tickColor;
  sf::Font &_font;
  AxisLabelContainer _axisLabel;
  void setupAxis(sf::RectangleShape &axis) const;
  void setupTick(sf::RectangleShape &tick, const double pixelStepSize) const;
  void setupNumbers(sf::Text &text) const;
  int calcTickCount() const;
  double calcPixelStepSize() const;
  void updateTickPosition(sf::RectangleShape &tick, double pixelStepSize) const;
  void setNumberPosition(sf::Text &text, const sf::Vector2f offset,
                         const sf::RectangleShape tick,
                         const int iteration) const;
};

#endif // !AXIS_H
