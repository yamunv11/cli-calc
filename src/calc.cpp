#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include "parser.h"
#include "token.h"
#include "utils.h"
#include "readline/readline.h"
#include "readline/history.h"

void read_config()
{
    std::string line; // string to store input, defined here to be able to use it in catch
    try {
        const std::string config_path = std::string(std::getenv("HOME")) + "/.config/calc/calc.conf";
        std::ifstream config_file{config_path};
        if (!config_file) {
            // ORIG
            // std::cerr << color::red << "can't find config file " << config_path << color::white << '\n';
            // DEBUG
            std::cerr << "can't find config file " << config_path << '\n';
            return;
        }
        for (; std::getline(config_file, line);) {
            std::istringstream is{line};
            TokenStream ts { is };
            expression(ts);
        }
    } catch (std::exception &e) {
        // ORIG
        // std::cerr << color::red << "Error in config expression: " << line << color::white << '\n';
        // DEBUG
        std::cerr << "Error in config expression: " << line << '\n';
        // ORIG
        // std::cerr << color::red << "Message: " << e.what() << color::white << '\n';
        // DEBUG
        std::cerr << "Message: " << e.what() << '\n';
    }
}

void repl()
{
    while (true) {
        try {
            const char *input_line = readline("> ");
            if (!input_line)
                break;
            else
                add_history(input_line);
            std::istringstream stream{input_line};
            TokenStream ts(stream);
            Token next = ts.get();
            if (next.kind == Kind::quit)
                break;
            if (next.kind == Kind::eoe)
                continue;
            ts.putback(next);
            double val = expression(ts);
            next = ts.get();
            if (next.kind != Kind::eoe) { // if the string stram is not yet exahusted
                // ORIG
                // std::cerr << color::red << "bad expression" << color::white << '\n';
                // DEBUG
                std::cerr << "bad expression" << '\n';
                continue;
            }
            // ORIG
            // std::cout << color::green << format_double(val) << color::white << '\n';
            // DEBUG
            std::cout << format_double(val) << '\n';
        } catch (std::exception &e) {
            // ORIG
            // std::cerr << color::red << e.what() << color::white << '\n';
            // DEBUG
            std::cerr << e.what() << '\n';
        } 
    }
}

int main()
{
    read_config();
    repl();
}
