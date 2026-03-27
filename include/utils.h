#pragma once

#include <string>

/** colors used for output formatting */
namespace color {
    constexpr char green[] = "\033[92m";
    constexpr char red[]   =  "\033[33m";
    constexpr char white[] =  "\033[0m";
};

/**
 *Returns a pretty formatted string for outputting.
 *
 * @param is Number to be printed in numerical representation.
 * @return   Output ready string with ',' character as thousand seperator.
 */
std::string format_double(double value);

/**
 *Returns the factorial of a number.
 *
 * @param is Number to get the factorial of.
 * @return   Facotiral of that number.
 * @throws std::runtime_error If the number passed is not an integer.
 * @details  The function accepts a double deliberately, because one of its core
 *           functionalities is to throw an error when receiving a decimal number.
 */
long double factorial(double n);
