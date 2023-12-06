#include "Axis.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>

Axis::Axis(sf::Font &font) : _font(font) {
  _stepSize = 1;
  _lineThickness = 1;
  _length = 0;
  _min = 0;
  _max = 0;
  _type = AxisType::X;
  _axisColor = sf::Color::Black;
  _tickColor = sf::Color::Black;
}

void Axis::setupAxis(sf::RectangleShape &axis) const {
  if (_type == AxisType::Y) {
    axis.setSize(sf::Vector2f(_lineThickness, _length));
  } else if (_type == AxisType::X) {
    axis.setSize(sf::Vector2f(_length, _lineThickness));
  }
  axis.setFillColor(_axisColor);
}

void Axis::setupTick(sf::RectangleShape &tick,
                     const double pixelStepSize) const {
  tick.setFillColor(_tickColor);
  if (_type == AxisType::Y) {
    tick.setSize(sf::Vector2f(_lineThickness * 3, _lineThickness));
    tick.setOrigin(sf::Vector2f(_lineThickness * 2, _lineThickness / 2));
  } else if (_type == AxisType::X) {
    tick.setSize(sf::Vector2f(_lineThickness, _lineThickness * 3));
    tick.setOrigin(sf::Vector2f(
        _lineThickness / 2,
        _lineThickness *
            2)); // NOTE: Set origin to center of tick perpindicuar to axis
  }
  if (_type == AxisType::Y) {
    tick.setPosition(_lineThickness, _length - pixelStepSize);
  } else if (_type == AxisType::X) {
    tick.setPosition(pixelStepSize, _lineThickness);
  }
}

int Axis::calcTickCount() const {
  int delta = std::ceil(_max) - std::floor(_min);
  return static_cast<int>(delta / _stepSize);
}

double Axis::calcPixelStepSize() const { return _length / calcTickCount(); }

void Axis::updateTickPosition(sf::RectangleShape &tick,
                              double pixelStepSize) const {
  if (_type == AxisType::Y) {
    tick.setPosition(tick.getPosition() - sf::Vector2f(0, pixelStepSize));
  } else if (_type == AxisType::X) {
    tick.setPosition(tick.getPosition() + sf::Vector2f(pixelStepSize, 0));
  }
}

void Axis::setupNumbers(sf::Text &text) const {
  text.setFont(_font);
  text.setCharacterSize(20);
  text.setFillColor(_tickColor);
}

void Axis::setNumberPosition(sf::Text &text, const sf::Vector2f offset,
                             const sf::RectangleShape tick,
                             const int iteration) const {
  text.setString(std::to_string(static_cast<int>(
      _stepSize * iteration + _min + 1))); // INFO: Check if this is correct
  sf::FloatRect numberBox;
  numberBox = text.getLocalBounds();
  if (_type == AxisType::Y) {
    text.setOrigin(numberBox.getSize().x, numberBox.getSize().y / 2.0);
    text.setPosition(tick.getPosition().x - offset.y, tick.getPosition().y);
  } else if (_type == AxisType::X) {
    text.setOrigin(numberBox.getSize().x / 2.0, 0);
    text.setPosition(tick.getPosition().x, tick.getPosition().y + offset.x);
  }
}

void Axis::setupAxisLabels(sf::Text &text, int spacing) const {
  text.setFont(_font);
  text.setFillColor(_tickColor);
  text.setCharacterSize(35);
  text.setString(_axisLabel);
  sf::FloatRect labelBox;

  if (_type == AxisType::Y) {
    labelBox = text.getLocalBounds();
    text.setOrigin(labelBox.getSize().x / 2, labelBox.getSize().y);
    text.setRotation(270);
    text.setPosition(-spacing, _length / 2); // TODO: Make x set by user
  } else if (_type == AxisType::X) {
    labelBox = text.getLocalBounds();
    text.setOrigin(labelBox.getSize().x / 2, labelBox.getSize().y);
    text.setPosition(_length / 2,
                     spacing + 10); // TODO: Make x set by user
  }
}

void Axis::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::RectangleShape axis;
  setupAxis(axis);

  sf::Text axisLabel;
  setupAxisLabels(axisLabel, 50);

  int count = calcTickCount();
  double pixelStepSize =
      calcPixelStepSize(); // NOTE: Must be a double for calcs even-though
                           // pixels cannot be fractional

  sf::RectangleShape tick;
  setupTick(tick, pixelStepSize);

  sf::Text numbers;
  setupNumbers(numbers);

  states.transform *= getTransform();
  for (int i = 0; i < count; i++) {
    setNumberPosition(numbers, sf::Vector2(3.0f, 9.0f), tick, i);
    target.draw(tick, states);
    target.draw(numbers, states);
    updateTickPosition(tick, pixelStepSize);
  }
  target.draw(axis, states);
  target.draw(axisLabel, states);
};

void Axis::setLineThickness(double lineThickness) {
  _lineThickness = lineThickness;
}

void Axis::setMin(double min) { _min = min; }

void Axis::setMax(double max) { _max = max; }

void Axis::setType(AxisType type) { _type = type; }

void Axis::setLength(double length) { _length = length; }

void Axis::setAxisColor(sf::Color color) { _axisColor = color; }

void Axis::setTickColor(sf::Color color) { _tickColor = color; }

void Axis::setStepSize(double stepSize) { _stepSize = stepSize; }

void Axis::setFont(const sf::Font &font) { _font = font; }

void Axis::setLabel(const std::string label) { _axisLabel = label; }
