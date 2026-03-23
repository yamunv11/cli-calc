#pragma once

#include <iostream>

/**
 *A type to store the kinds of tokens we can handle in our calculator.
 */
enum class Kind {
    num = 1000,
    eoe,
    plus,
    minus,
    division,
    mult,
    obrace,
    cbrace,
    factorial,
    power,
    quit
};

/**
 *A type to represent tokens.
 *A token must have a kind an optionally a value of the kind is num.
 */
class Token {
public:
    Kind kind; /**< The member kind of type Kind to represent the kind of the token. */
    double value; /**< The member value of type double to optionally represent the numerical value of tokens of Kind::num. */
    Token(Kind k, double v)
        : kind(k), value(v) {}
    Token(Kind k)
        : kind(k), value(0) {}
};

/**
 *A type to represent a stream of tokens
 */
class TokenStream {
public:
    TokenStream(std::istream& s) : is(s) {} 
    Token get();                /**< Method to get a token of the stream. */
    void putback(Token t);      /**< Method to put back a token to the stream for later use. */

private:
    std::istream& is;           /**< Input stream to tokenize. */
    /**
     * Temporary buffer to store tokens from putback() for later use.
     * Next get() would return this token if full = true
     */
    Token buffer = {Kind::num}; 
    bool full = false;          /**< if true, next get() will return buffer */
};
