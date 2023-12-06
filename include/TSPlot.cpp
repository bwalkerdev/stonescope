#include "TSPlot.h"
#include "Axis.h"
#include "Line.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

TSPlot::TSPlot(TouchstoneFile &file, sf::Font &font)
    : _file(file), _font(font) {
  _size = sf::Vector2f(0, 0);
  _plotSize = sf::Vector2f(0, 0);
  _padding = 0;
  _lineThickness = 0;
  _origin = sf::Vector2f(0, 0);
  _bgColor = sf::Color::Black;
}

void TSPlot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::RectangleShape background(_size);
  background.setFillColor(_bgColor);

  Axis yAxis(_font);
  yAxis.setLength(_plotSize.y);
  yAxis.setAxisColor(_axisColor);
  yAxis.setTickColor(_tickColor);
  yAxis.setLineThickness(_lineThickness);
  yAxis.setOrigin(_lineThickness, _plotSize.y);
  yAxis.setPosition(_origin);
  yAxis.setStepSize(_axisStepSize.y);
  yAxis.setMax(_file.getMaxLHS());
  yAxis.setMin(_file.getMinLHS());
  yAxis.setType(AxisType::Y);
  yAxis.setFont(_font);
  yAxis.setLabel(_axisLabel.y);
  // yAxis.setOrigin(sf::Vector2f(_lineThickness, _plotSize.y));
  // yAxis.setPosition(_origin);
  //
  Axis xAxis(_font);
  xAxis.setLength(_plotSize.x);
  xAxis.setAxisColor(_axisColor);
  xAxis.setTickColor(_tickColor);
  xAxis.setLineThickness(_lineThickness);
  xAxis.setOrigin(0, 0);
  xAxis.setPosition(_origin);
  xAxis.setStepSize(_axisStepSize.x);
  xAxis.setMax(_file.getMaxFreq());
  xAxis.setMin(_file.getMinFreq());
  xAxis.setType(AxisType::X);
  xAxis.setFont(_font);
  xAxis.setLabel(_axisLabel.x);

  Line line;
  line.setColor(sf::Color::Red);
  for (unsigned long i = 0; i < _file.getNumPoints(); ++i) {
    line.push_back(_file.at(i, TouchstoneFile::Side::LHS, 0));
  }
  line.generateGeometry();
  sf::Vector2f scaleFactor = sf::Vector2f(_plotSize.x / line.getSize().x,
                                          _plotSize.y / line.getSize().y);
  line.setScale(scaleFactor);
  line.setPosition(_origin);

  Line secondParam;
  secondParam.setColor(sf::Color::Blue);
  for (unsigned long i = 0; i < _file.getNumPoints(); ++i) {
    secondParam.push_back(_file.at(i, TouchstoneFile::Side::LHS, 1));
  }
  secondParam.generateGeometry();
  sf::Vector2f scaleFactor2 =
      sf::Vector2f(_plotSize.x / secondParam.getSize().x,
                   _plotSize.y / secondParam.getSize().y);
  secondParam.setScale(scaleFactor2);
  secondParam.setPosition(_origin);

  states.transform *= getTransform();
  target.draw(background, states);
  target.draw(yAxis, states);
  target.draw(xAxis, states);
  target.draw(line, states);
  target.draw(secondParam, states);
}

void TSPlot::setWidth(double width) {
  _size.x = width;
  _setOrigin();
}

void TSPlot::setHeight(double height) {
  _size.y = height;
  _setOrigin();
}

void TSPlot::setPadding(double padding) {
  _padding = padding;
  _plotSize = _size - sf::Vector2f(2 * _padding, 2 * _padding);
  _setOrigin();
}

void TSPlot::setLineThickness(double lineThickness) {
  _lineThickness = lineThickness;
}
void TSPlot::setBgColor(sf::Color bgColor) { _bgColor = bgColor; }

void TSPlot::_setOrigin() {
  _origin = sf::Vector2f(_padding, _size.y - _padding);
}

void TSPlot::setAxisStepSize(sf::Vector2f stepSize) {
  _axisStepSize = stepSize;
}

void TSPlot::setAxisColor(sf::Color axisColor) { _axisColor = axisColor; }

void TSPlot::setTickColor(sf::Color tickColor) { _tickColor = tickColor; }

void TSPlot::setFont(sf::Font font) { _font = font; }

void TSPlot::setXAxisLabel(std::string label) { _axisLabel.x = label; }

void TSPlot::setYAxisLabel(std::string label) { _axisLabel.y = label; }
