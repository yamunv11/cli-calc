#include "utils.h"
#include "token.h"
#include <cctype>
#include <iostream>
#include <stdexcept>

Token TokenStream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;

    if (!(is >> ch)) {
        if (is.eof())
            return Token(Kind::eoe);
        else
            throw std::runtime_error("input error");
    }

    if (ch == '.' || std::isdigit(ch)) {
        is.putback(ch);
        double d = read_num(is);
        return Token(Kind::num, d);
    }

    else if (ch == '+') return Token(Kind::plus);
    else if (ch == '-') return Token(Kind::minus);
    else if (ch == '*') return Token(Kind::mult);
    else if (ch == '/') return Token(Kind::division);
    else if (ch == '(') return Token(Kind::obrace);
    else if (ch == ')') return Token(Kind::cbrace);
    else if (ch == 'q') return Token(Kind::quit);
    else if (ch == '!') return Token(Kind::factorial);
    else if (ch == '^') return Token(Kind::power);
    else throw std::runtime_error(std::string("bad token '") + ch + '\'');
}

void TokenStream::putback(Token t)
{
    if (full)
        throw std::runtime_error("putback into full buffer");
    buffer = t;
    full = true;
}
