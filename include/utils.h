#pragma once
#include <iostream>

namespace color {
    constexpr char green[] = "\033[92m";
    constexpr char red[]   =  "\033[33m";
    constexpr char white[] =  "\033[0m";
};

double read_num(std::istream& is);
std::string format_double(double value);
double factorial(double n);
