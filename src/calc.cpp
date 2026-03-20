#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "parser.h"
#include "token.h"
#include "utils.h"
#include "readline/readline.h"
#include "readline/history.h"

void read_config()
{
    std::string config_path = std::string(std::getenv("HOME")) + "/.config/calc/calc.conf";
    std::ifstream config_file{config_path};
    if (!config_file) {
        std::cerr << "can't find config file " << config_path << '\n';
        return;
    }
    for (std::string line; std::getline(config_file, line);) {
        std::istringstream is{line};
        Token_stream ts { is };
        std::cout << expression(ts) << '\n';
    }
}

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
            if (next.kind != Kind::eoe) {
                std::cerr << color::red << "bad expression" << color::white << '\n';
                continue;
            }
            std::cout << color::green << format_double(val) << color::white << '\n';
        } catch (std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
}

int main()
{
    read_config();
    repl();
}
