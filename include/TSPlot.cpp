#include "TSPlot.h"
#include "Axis.h"
#include "Line.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

TSPlot::TSPlot(TouchstoneFile &file, sf::Font &font)
    : _file(file), _font(font) {
  _size = sf::Vector2f(0, 0);
  _plotSize = sf::Vector2f(0, 0);
  _padding = 0;
  _lineThickness = 0;
  _origin = sf::Vector2f(0, 0);
  _bgColor = sf::Color::Black;
}

TSPlot::~TSPlot() {
  for (auto drawable : _plotComponents) {
    delete drawable;
  }
  for (auto line : _lines) {
    delete line;
  }
}

sf::Vector2f TSPlot::_calcPerPixelFactor() {
  float x = _plotSize.x / std::ceil(_file.getMaxFreq());
  float y = _plotSize.y / std::ceil(_file.getMaxLHS());
  return sf::Vector2f(x, y);
}

void TSPlot::addLine(int param, sf::Color color) {
  Line *line = new Line();
  line->setColor(color);

  for (unsigned long i = 0; i < _file.getNumPoints(); ++i) {
    line->push_back(_file.at(i, TouchstoneFile::Side::LHS, param));
  }
  line->generateGeometry();
  line->setScale(_calcPerPixelFactor());
  line->setPosition(_origin);
  _lines.push_back(line);
}

void TSPlot::generateGeometry() {
  sf::RectangleShape *background = new sf::RectangleShape(_size);
  background->setFillColor(_bgColor);
  _plotComponents.push_back(background);

  Axis *yAxis = new Axis(_font);
  yAxis->setLength(_plotSize.y);
  yAxis->setAxisColor(_axisColor);
  yAxis->setTickColor(_tickColor);
  yAxis->setLineThickness(_lineThickness);
  yAxis->setOrigin(_lineThickness, _plotSize.y);
  yAxis->setPosition(_origin);
  yAxis->setStepSize(_axisStepSize.y);
  yAxis->setMax(_file.getMaxLHS());
  yAxis->setMin(_file.getMinLHS());
  yAxis->setType(AxisType::Y);
  yAxis->setFont(_font);
  yAxis->setLabel(_axisLabel.y);
  _plotComponents.push_back(yAxis);
  // yAxis.setOrigin(sf::Vector2f(_lineThickness, _plotSize.y));
  // yAxis.setPosition(_origin);
  //
  Axis *xAxis = new Axis(_font);
  xAxis->setLength(_plotSize.x);
  xAxis->setAxisColor(_axisColor);
  xAxis->setTickColor(_tickColor);
  xAxis->setLineThickness(_lineThickness);
  xAxis->setOrigin(0, 0);
  xAxis->setPosition(_origin);
  xAxis->setStepSize(_axisStepSize.x);
  xAxis->setMax(_file.getMaxFreq());
  xAxis->setMin(_file.getMinFreq());
  xAxis->setType(AxisType::X);
  xAxis->setFont(_font);
  xAxis->setLabel(_axisLabel.x);
  _plotComponents.push_back(xAxis);
}

void TSPlot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (auto drawable : _plotComponents) {
    target.draw(*drawable, states);
  }
  for (auto line : _lines) {
    target.draw(*line, states);
  }
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
