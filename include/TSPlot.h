#ifndef TS_PLOT_H
#define TS_PLOT_H

#include "Axis.h"
#include "TouchstoneFile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
class TSPlot : public sf::Drawable, public sf::Transformable {
public:
  TSPlot() = delete;
  TSPlot(TouchstoneFile &file, sf::Font &font);
  ~TSPlot() = default;
  void setWidth(double width);
  void setHeight(double height);
  void setPadding(double padding);
  void setLineThickness(double lineThickness);
  void setBgColor(sf::Color bgColor);
  void setAxisColor(sf::Color axisColor);
  void setTickColor(sf::Color tickColor);
  void setAxisStepSize(sf::Vector2f stepSize);
  void setYAxisLabel(std::string label);
  void setXAxisLabel(std::string label);
  void setFont(sf::Font font);

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void _setOrigin();
  TouchstoneFile &_file;
  sf::Vector2f _size;
  sf::Vector2f _plotSize;
  double _padding;
  double _lineThickness;
  sf::Vector2f _origin;
  sf::Color _bgColor;
  sf::Color _axisColor;
  sf::Color _tickColor;
  sf::Vector2f _axisStepSize;
  Axis::AxisLabelContainer _axisLabel;
  sf::Font &_font;
  // std::vector<std::vector<TSLine>> _lines;
};

#endif // !TS_PLOT_H
