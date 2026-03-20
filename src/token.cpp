#include "token.h"
#include <cctype>
#include <iostream>
#include <stdexcept>

Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    is >> ch;

    if (is.eof()) {
        return Token(Kind::eoe);
    }

    if (ch == '.' || std::isdigit(ch)) {
        is.putback(ch);
        double d;
        is >> d;
        return Token(Kind::num, d);
    }
    else if (ch == '+') return Token(Kind::plus);
    else if (ch == '-') return Token(Kind::minus);
    else if (ch == '*') return Token(Kind::mult);
    else if (ch == '/') return Token(Kind::division);
    else if (ch == '(') return Token(Kind::obrace);
    else if (ch == ')') return Token(Kind::cbrace);
    else if (ch == 'q') return Token(Kind::quit);
    else throw std::runtime_error("bad token");
}

void Token_stream::putback(Token t)
{
    if (full)
        throw std::runtime_error("putback into full buffer");
    buffer = t;
    full = true;
}
