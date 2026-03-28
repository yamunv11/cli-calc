# Calculator design
## streams
The calculator uses streams for all sort of input.
- First we get the input line from the user and store it in a string.
- That string is then used to initialize a string stream.
- Then we create a token stream, which fetches tokens from that string stream to any function interested in calling Token_stream::get().
- when the string stream is exhausted and it returns EOF character, Token_stream::get() returns a eoe token, short for end of expression.
- if expression() parsed a whole expression without the next token being eoe, that means there's trailing garbage after our expression.

# grammar
Statement:\
    &emsp;Declaration\
    &emsp;Assignment\
    &emsp;Print\
    &emsp;Expression\
    &emsp;Expression Print
    
Print:\
    &emsp;;
    
Declaration:\
    &emsp;'let' Name '=' Expression
    
Assignment:\
    &emsp;Name = Expression
    
Print:\
    &emsp;print("str")
    
Expression:\
    &emsp;Term\
    &emsp;Term '+' Term\
    &emsp;Term '-' Term

Term:\
    &emsp;Factor\
    &emsp;Factor '*' Factor\
    &emsp;Factor '/' Factor

Factor:\
    &emsp;Primary '^' Primary

Primary:\
    &emsp;Number\
    &emsp;Name\
    &emsp;Name '(' List ')'\
    &emsp;'(' Expression ')'\
    &emsp;'-' Primary\
    &emsp;Primary '!'
    
List:\
    &emsp;'(' ')'\
    &emsp;'(' Expression, * ')'
