#include "token.h"
#include "utils.h"
#include "var.h"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<Var> var_table;

void TokenStream::putback(Token t)
{
    buffer.push_back(t);
}

Token TokenStream::get()
{
    if (buffer.size() > 0) {
        Token t = buffer.back();
        buffer.pop_back();
        return t;
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
    } else if (ch == '+')
        return Token(Kind::plus);

    else if (ch == '-') return Token(Kind::minus);
    else if (ch == '*') return Token(Kind::mult);
    else if (ch == '/') return Token(Kind::division);
    else if (ch == '(') return Token(Kind::obrace);
    else if (ch == ')') return Token(Kind::cbrace);
    else if (ch == 'q') return Token(Kind::quit);
    else if (ch == '!') return Token(Kind::factorial);
    else if (ch == '^') return Token(Kind::power);
    else if (ch == '=') return Token(Kind::assignment);

    else if (std::isalpha(ch)) { // case of a name
        std::string s;
        s += ch;
        while (std::isalpha(static_cast<unsigned char>(is.peek())) || is.peek() == '_') {
            is.get(ch);
            s += ch;
        }
        if (s == "let")
            return Token(Kind::let);
        else if (s == "quit")
            return Token(Kind::quit);
        else
            return Token(Kind::name, s);
    }

    else
        throw std::runtime_error(std::string("bad token '") + ch + '\'');
}
