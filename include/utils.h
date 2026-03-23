#pragma once
#include <iostream>

/** colors used for output formatting */
namespace color {
    constexpr char green[] = "\033[92m";
    constexpr char red[]   =  "\033[33m";
    constexpr char white[] =  "\033[0m";
};

/**
 * Reads a numeric value from an input stream, ignoring commas as thousand separators.
 * The stream may contain a sequence of digits, optionally with a single decimal point.
 * Commas are ignored but must not appear consecutively or adjacent to a decimal point.
 *
 * @param is  Input stream to read from.
 * @return    The parsed double value.
 * @throws std::runtime_error  If the input format is invalid (e.g., multiple commas,
 *                             consecutive separators, or a trailing comma).
 */
double read_num(std::istream& is);

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
int factorial(double n);
