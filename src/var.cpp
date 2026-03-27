#include "var.h"
#include <stdexcept>
#include <string>
#include <vector>

extern std::vector<Var> var_table;

bool is_declared(const std::string &n)
{
    for (const auto &v : var_table)
        if (v.name == n)
            return true;
    return false;
}

double get_value(const std::string &n)
{
    for (const auto &v : var_table)
        if (v.name == n)
            return v.value;
    throw std::runtime_error("undeclared identifier: " + n);
}

double set_value(const std::string &n, double val)
{
    for (auto &v : var_table)
        if (v.name == n) {
            v.value = val;
            return val;
        }
    throw std::runtime_error("undeclared identifier: " + n);
}

double define_name(const std::string &n, double val)
{
    if (is_declared(n))
        throw std::runtime_error("redefinition of variable: " + n);
    var_table.push_back(Var{n, val});
    return val;
}
