#pragma once

#include <string>

class Var {
public:
    std::string name;
    double value;
    Var(std::string n, double v) : name { n } , value { v } {
    }
};

double get_value(const std::string &name);
double set_value(const std::string &name, double val);
bool is_declared(const std::string &name);
double define_name(const std::string &name, double val);
