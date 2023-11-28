
/**
 * @file Plot.h
 * @brief Defines the Plot class for creating and rendering plots.
 */

#ifndef PLOT_H
#define PLOT_H

#include "TouchstoneFile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @class Plot
 * @brief Represents a plot that can be drawn on a render target.
 */
class Plot {
public:
  /**
   * @brief Deleted default constructor.
   */
  Plot() = delete;

  /**
   * @brief Constructs a Plot object with the specified parameters.
   * @param file The TouchstoneFile object containing the data for the plot.
   * @param windowWidth The width of the window in pixels.
   * @param windowHeight The height of the window in pixels.
   * @param margin The margin size in pixels.
   */
  Plot(TouchstoneFile &file, const int windowWidth, const int windowHeight,
       const int margin);

  /**
   * @brief Gets the width of the plot.
   * @return The width of the plot in pixels.
   */
  int getWidth();

  /**
   * @brief Gets the height of the plot.
   * @return The height of the plot in pixels.
   */
  int getHeight();

  /**
   * @brief Draws the plot on the specified render target.
   * @param target The render target to draw the plot on.
   */
  void draw(sf::RenderTarget &target);

private:
  int _width;               /**< The width of the plot in pixels. */
  int _height;              /**< The height of the plot in pixels. */
  int _padding;             /**< The padding size in pixels. */
  int _margin;              /**< The margin size in pixels. */
  int _lineThickness;       /**< The thickness of the plot lines in pixels. */
  int _yStepSize;           /**< The step size for the y-axis in pixels. */
  int _xStepSize;           /**< The step size for the x-axis in pixels. */
  sf::Vector2f _origin;     /**< The origin point of the plot. */
  sf::Color _bgColor;       /**< The background color of the plot. */
  sf::Vector2f normalize(); /**< Normalizes the plot coordinates. */
  sf::Vector2f getNextPoint(); /**< Gets the next point to plot. */
  TouchstoneFile &
      _file; /**< The TouchstoneFile object containing the data for the plot. */

  /**
   * @brief Draws the background of the plot on the specified render target.
   * @param target The render target to draw the background on.
   */
  void drawBackground(sf::RenderTarget &target);

  /**
   * @brief Draws the axes of the plot on the specified render target.
   * @param target The render target to draw the axes on.
   */
  void drawAxes(sf::RenderTarget &target);

  /**
   * @brief Draws the plot lines on the specified render target.
   * @param target The render target to draw the plot lines on.
   */
  void drawPlot(sf::RenderTarget &target);
};

#endif // !PLOT_H
