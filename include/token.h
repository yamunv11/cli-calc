#pragma once

#include <iostream>

enum class Kind {
    num = 1000,
    eoe,
    plus = '+',
    minus = '-',
    division = '/',
    mult = '*',
    obrace = '(',
    cbrace = ')',
    quit = 'q'
};

class Token {
public:
    Kind kind;
    double value;
    Token(Kind k, double v)
        : kind(k), value(v) {}
    Token(Kind k)
        : kind(k), value(0) {}
};

class Token_stream {
public:
    Token_stream(std::istream& s) : is(s) {} 
    Token get();
    void putback(Token t);

private:
    std::istream& is;
    Token buffer = {Kind::num};
    bool full = false;
};
