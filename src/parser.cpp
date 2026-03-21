#include "token.h"
#include <stdexcept>
#include "parser.h"
#include "utils.h"

double expression(Token_stream& ts)
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

double term(Token_stream& ts)
{
    double left = primary(ts);
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
        case Kind::mult:
            left *= primary(ts);
            next = ts.get();
            break;
        case Kind::division: {
            double d = primary(ts);
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

double primary(Token_stream& ts)
{
    Token next = ts.get();
    switch (next.kind) {
    case Kind::minus: {
        next = ts.get();
        if (next.kind != Kind::num)
            throw std::runtime_error("primary expected");
        Token is_fac = ts.get();
        if (is_fac.kind == Kind::fac)
            throw std::runtime_error("factorial requries a postive integer");
        else
            ts.putback(is_fac);
        return -1 * next.value;
    }
    case Kind::num: {
        Token is_fac = ts.get();
        if (is_fac.kind == Kind::fac)
            return factorial(next.value);
        else
            ts.putback(is_fac);
        return next.value;
    }
    case Kind::obrace: {
        double val = expression(ts);
        next = ts.get();
        if (next.kind != Kind::cbrace)
            throw std::runtime_error("')' expected");
        Token is_fac = ts.get();
        if (is_fac.kind == Kind::fac)
            return factorial(val);
        else
            ts.putback(is_fac);
        return val;
    }
    default:
        throw std::runtime_error("primary expected");
    }
}
