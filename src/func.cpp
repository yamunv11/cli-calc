#include <cmath>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "token.h"
#include "parser.h"
#include "readline/readline.h"
#include "readline/history.h"

double funcall(const std::string &name, const std::vector<double> &arguments_list)
{
    if (name == "dte")
        return arguments_list.at(0) * 50;
    else if (name == "etd")
        return arguments_list.at(0) / 50;
    else if (name == "sqrt")
        return std::sqrt(arguments_list.at(0));
    else if (name == "input") {
        const char* input_line = readline("");
        if (!input_line)
            throw std::runtime_error("input error");
        else
            add_history(input_line);
        std::istringstream is { input_line };
        TokenStream ts { is };
        double val = statement(ts);
        return val;

    } else
        throw std::runtime_error("unkown function " + name);
}
