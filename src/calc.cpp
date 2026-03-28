#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include "parser.h"
#include "token.h"
#include "utils.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "var.h"

void read_config()
{
    std::string line; // string to store input, defined here to be able to use it in catch
    try {
        const std::string config_path = std::string(std::getenv("HOME")) + "/.config/calc/calc.conf";
        std::ifstream config_file{config_path};
        if (!config_file) {
            std::cerr << color::red << "\ncan't find config file " << config_path << color::white << '\n';
            return;
        }
        for (; std::getline(config_file, line);) {
            std::istringstream is{line};
            TokenStream ts { is };
            Token next = ts.get();
            if (next.kind == Kind::quit)
                break;
            if (next.kind == Kind::eoe)
                continue;
            ts.putback(next);

            statement(ts);
        }
    } catch (std::exception &e) {
        std::cerr << color::red << "\nError in config statement: " << line << color::white << '\n';
        std::cerr << color::red << "Message: " << e.what() << color::white << '\n';
    }
}

void eval(std::string fname)
{
    std::string line; // string to store input, defined here to be able to use it in catch
    try {
        std::ifstream read_file{fname};
        if (!read_file) {
            std::cerr << color::red << "\ncan't find file " << fname << color::white << '\n';
            return;
        }
        for (; std::getline(read_file, line);) {
            std::istringstream is{line};
            TokenStream ts { is };
            Token next = ts.get();
            if (next.kind == Kind::quit)
                break;
            if (next.kind == Kind::eoe)
                continue;
            ts.putback(next);

            double val = statement(ts);
            next = ts.get();
            if (next.kind == Kind::print)
                std::cout << val << '\n';
        }
    } catch (std::exception &e) {
        std::cerr << color::red << "\nError in statement: " << line << color::white << '\n';
        std::cerr << color::red << "Message: " << e.what() << color::white << '\n';
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
            double val = statement(ts);
            next = ts.get();
            if (next.kind != Kind::eoe) { // if the string stram is not yet exahusted
                std::cerr << color::red << "bad statement" << color::white << '\n';
                continue;
            }
            set_value("ans", val);
            std::cout << color::green << format_double(val) << color::white << '\n';
        } catch (std::exception &e) {
            std::cerr << color::red << e.what() << color::white << '\n';
        } 
    }
}

int main(int argc, char **argv)
{
    define_name("ans", 0);
    read_config();
    if (argc > 1) {
        if (argc > 2) {
            std::cerr << "Please provide only one file\n";
            return 1;
        }
        eval(argv[1]);
        return 0;
    }
    repl();
}
