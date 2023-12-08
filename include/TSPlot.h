/**
 * @file TSPlot.h
 * @brief Definition of the Touchstone file plot class.
 * @author Bryce Walker
 */

#ifndef TS_PLOT_H
#define TS_PLOT_H

#include "Axis.h"
#include "Line.h"
#include "TouchstoneFile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <string>

/**
 * @brief Class for creating and managing a plot from Touchstone data.
 *
 * TSPlot is responsible for generating a graphical representation of Touchstone
 * data, including creating axes, lines, and managing visual elements such as
 * colors and fonts.
 */
class TSPlot : public sf::Drawable, public sf::Transformable {
public:
  TSPlot() = delete;

  /**
   * @brief Construct a new TSPlot object.
   *
   * @param file Reference to a TouchstoneFile object containing the data to
   * plot.
   * @param font Reference to a sf::Font object for text rendering.
   */
  TSPlot(TouchstoneFile &file, sf::Font &font);

  /**
   * @brief Destroy the TSPlot object.
   *
   * Cleans up dynamically allocated components of the plot.
   */
  ~TSPlot();

  // Setter methods
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

  /**
   * @brief Generates the geometric components of the plot.
   *
   * This method creates and positions all drawable elements of the plot,
   * including the background, axes, and lines.
   */
  void generateGeometry();

  /**
   * @brief Adds a line to the plot.
   *
   * @param param The parameter index to plot.
   * @param color The color of the line.
   */
  void addLine(int param, sf::Color color);

  /**
   * @brief Container for axis labels.
   */
  struct AxisLabelContainer {
    std::string x; ///< Label for the X-axis.
    std::string y; ///< Label for the Y-axis.
  };

private:
  /**
   * @brief Draws the plot to a render target.
   *
   * @param target Render target to draw the plot on.
   * @param states Current render states.
   */
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  sf::Vector2f
  _calcPerPixelFactor(); ///< Calculates the scaling factor per pixel.
  void _setOrigin();     ///< Sets the origin point for the plot.

  // Member variables
  TouchstoneFile &_file;         ///< Reference to Touchstone data file.
  sf::Vector2f _size;            ///< Size of the plot.
  sf::Vector2f _plotSize;        ///< Size of the plotting area.
  double _padding;               ///< Padding around the plot.
  double _lineThickness;         ///< Thickness of the plot lines.
  sf::Vector2f _origin;          ///< Origin point of the plot.
  sf::Color _bgColor;            ///< Background color of the plot.
  sf::Color _axisColor;          ///< Color of the axes.
  sf::Color _tickColor;          ///< Color of the tick marks.
  sf::Vector2f _axisStepSize;    ///< Step size for axis ticks.
  AxisLabelContainer _axisLabel; ///< Container for axis labels.
  sf::Font &_font;               ///< Font used for text rendering.
  std::list<sf::Drawable *>
      _plotComponents; ///< List of drawable components of the plot.
  std::list<sf::Drawable *> _lines; ///< List of lines in the plot.
};

#endif // !TS_PLOT_H
