/**
 * @file Options.h
 * @brief Enumeration of options that a Touchstone file could potentially have
 * @author Bryce Walker
 */

#ifndef OPTIONS_H
#define OPTIONS_H

enum class FrequencyType { GHz, MHz, KHz, Hz };

enum class ParameterType { S, Y, Z, H, G };

enum class ParameterFormat { DB, MA, RI };

#endif // !OPTIONS_H
