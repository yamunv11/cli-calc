#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include "token.h"
#include "parser.h"

double funcall(const std::string &name, const std::vector<double> &arguments_list)
{
    if (name == "dte")
        return arguments_list.at(0) * 50;
    else if (name == "etd")
        return arguments_list.at(0) / 50;
    else if (name == "sqrt")
        return std::sqrt(arguments_list.at(0));
    else if (name == "input") {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream is { line };
        TokenStream ts { is };
        double val = statement(ts);
        return val;

    } else
        throw std::runtime_error("unkown function " + name);
}
