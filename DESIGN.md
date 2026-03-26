# Calculator design
## streams
The calculator uses streams for all sort of input.
- First we get the input line from the user and store it in a string.
- That string is then used to initialize a string stream.
- Then we create a token stream, which fetches tokens from that string stream to any function interested in calling Token_stream::get().
- when the string stream is exhausted and it returns EOF character, Token_stream::get() returns a eoe token, short for end of expression.
- if expression() parsed a whole expression without the next token being eoe, that means there's trailing garbage after our expression.

# grammar
Expression:
    Term
    Term + Term
    Term - Term

Term:
    Factor
    Factor * Factor
    Factor / Factor

Factor:
    Primary ^ Primary

Primary:
    Number
    Variable
    (Expression)
    Primary!
    -Primary
