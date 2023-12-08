/**
 * @file DataPoint.h
 * @brief DataPoint struct definition, used to store a single data point in the
 * TouchstoneFile class
 * @author Bryce Walker
 */

#include <vector>

#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <vector>
struct DataPoint {
  double frequency;
  std::vector<double> lhs;
  std::vector<double> rhs;
};

#endif // !DATAPOINT_H
