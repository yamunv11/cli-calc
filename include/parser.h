#pragma once

#include "token.h"

double statement(TokenStream &ts);
double declaration(TokenStream &ts);

/**
 *Reads and evaluates an expression from a token stream.
 *
 * @param  ts The token stream to read from.
 * @return    The value for the parsed expression.
 * @see       token.h for more info about token streams.
 * @see       grammar.txt for more info about what is an expression.
 */
double expression(TokenStream& ts);

/**
 *Reads and evaluates a term from a token stream.
 *
 * @param  ts The token stream to read from.
 * @return    The value for the parsed term.
 * @see       token.h for more info about token streams.
 * @see       grammar.txt for more info about what is a term.
 */
double term(TokenStream& ts);

/**
 *Reads and evaluates a primary from a token stream.
 *
 * @param  ts The token stream to read from.
 * @return    The value for the parsed primary.
 * @see       token.h for more info about token streams.
 * @see       grammar.txt for more info about what is a primary.
 */
double primary(TokenStream& ts);
double value(TokenStream &ts);
double factor(TokenStream &ts);
