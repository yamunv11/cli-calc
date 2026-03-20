#include <sstream>
#include <stdexcept>
#include "parser.h"
#include "token.h"
#include "readline/readline.h"
#include "readline/history.h"

void repl()
{
    while (true) {
        try {
            char *input_line = readline("> ");
            if (!input_line)
                break;
            else
                add_history(input_line);
            std::istringstream stream{input_line};
            Token_stream ts(stream);
            Token next = ts.get();
            if (next.kind == Kind::quit)
                break;
            else
                ts.putback(next);
            double val = expression(ts);
            next = ts.get();
            if (next.kind != Kind::eoe)
                throw std::runtime_error("bad expression");
            std::cout << val << '\n';
        } catch (std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
}

int main()
{
    repl();
}
