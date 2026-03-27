#include "parser.h"
#include "token.h"
#include "utils.h"
#include "var.h"
#include "func.h"
#include <cmath>
#include <stdexcept>

double statement(TokenStream &ts)
{
    Token t = ts.get();
    switch (t.kind) {
    case Kind::let:
        return declaration(ts);
    case Kind::name: {
        Token next = ts.get();
        if (next.kind == Kind::assignment) {
            if (!is_declared(t.name))
                throw std::runtime_error("undeclared identfier: " + t.name);
            else
                return set_value(t.name, expression(ts));
        } else {
            ts.putback(next);
            ts.putback(t);
            return expression(ts);            
        }
    }
    default:
        ts.putback(t);
        return expression(ts);
    }
}

double declaration(TokenStream &ts)
{
    Token var_name = ts.get();
    if (var_name.kind != Kind::name)
        throw std::runtime_error("bad expression");
    Token ass = ts.get();
    if (ass.kind != Kind::assignment)
        throw std::runtime_error("bad expression");
    double left = expression(ts);
    define_name(var_name.name, left);
    return left;
}

double expression(TokenStream &ts)
{
    double left = term(ts);
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
        case Kind::minus:
            left -= term(ts);
            next = ts.get();
            break;
        case Kind::plus:
            left += term(ts);
            next = ts.get();
            break;
        default:
            ts.putback(next);
            return left;
        }
    }
}

double term(TokenStream &ts)
{
    double left = factor(ts);
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
        case Kind::mult:
            left *= factor(ts);
            next = ts.get();
            break;
        case Kind::division: {
            double d = factor(ts);
            if (d == 0)
                throw std::runtime_error("divion by zero");
            left /= d;
            next = ts.get();
            break;
        }
        default:
            ts.putback(next);
            return left;
        }
    }
}

double factor(TokenStream &ts)
{
    double left = primary(ts);
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
        case Kind::power: {
            double exponent = primary(ts);
            left = std::pow(left, exponent);
            next = ts.get();
            break;
        }
        default:
            ts.putback(next);
            return left;
        }
    }
}

double primary(TokenStream &ts)
{
    Token next = ts.get();
    double val = 0;
    switch (next.kind) {
    case Kind::minus: {
        return -1 * primary(ts);
    }
    case Kind::obrace: {
        val = expression(ts);
        next = ts.get();
        if (next.kind != Kind::cbrace)
            throw std::runtime_error("')' expected");
        break;
    }
    case Kind::num:
        val = next.value;
        break;
    case Kind::name: {
        Token is_funcall = ts.get();
        if (is_funcall.kind == Kind::obrace) {
            if (next.name == "print") {
                next = ts.get();
                if (next.kind != Kind::str)
                    throw std::runtime_error("No string to print");
                std::cout << next.name;
            } else
                val = funcall(next.name, list(ts));
            is_funcall = ts.get();
            if (is_funcall.kind != Kind::cbrace)
                throw std::runtime_error("')' expected");
        }
        else {
            ts.putback(is_funcall);
            val = get_value(next.name);
        }
        break;
    }
    default:
        throw std::runtime_error("primary expected");
    }
    next = ts.get();
    while (next.kind == Kind::factorial) {
        val = factorial(val);
        next = ts.get();
    }
    ts.putback(next);
    return val;
}

std::vector<double> list(TokenStream &ts)
{
    std::vector<double> list;
    Token next = ts.get();
    if (next.kind == Kind::cbrace) {
        ts.putback(next);
        return list;
    }
    else
        ts.putback(next);

    while (true) {
        list.push_back(expression(ts));
        next = ts.get();
        switch (next.kind) {
        case Kind::comma:
            continue;
        case Kind::cbrace:
            ts.putback(next);
            return list;
        default:
            throw std::runtime_error("invalid list syntax");
        }
    }
}    
