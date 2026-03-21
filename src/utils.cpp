#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>

double read_num(std::istream& is)
{
    std::string s;
    char c, previous = '\0';
    for (; is.get(c); previous = c) { // makes sure there's no succssive , or .
        if (std::isdigit(c)) {
            s += c;
        } else if (c == '.' ){
            if (c == previous)
                throw std::runtime_error("bad expression");
            s += c;
        } else if (c == ',') {
            if (c == previous)
                throw std::runtime_error("bad expression");
            continue;
        } else {
            is.putback(c);
            break;
        }
    }
    if (c == ',')
        throw std::runtime_error("bad token");
    return std::stod(s);
}

std::string format_double(double value)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(10) << value;
    std::string s = oss.str();

    while (s.back() == '0')
        s.pop_back();
    if (s.back() == '.')
        s.pop_back();

    size_t dot_pos = s.find('.');
    std::string int_part = (dot_pos == std::string::npos) ? s : s.substr(0, dot_pos);
    std::string frac_part = (dot_pos == std::string::npos) ? "" : s.substr(dot_pos + 1);

    bool negative = (int_part[0] == '-');
    std::string digits = negative ? int_part.substr(1) : int_part;

    if (!digits.empty()) {
        std::string with_commas;
        int count = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            with_commas.push_back(digits[i]);
            ++count;
            if (count % 3 == 0 && i != 0)
                with_commas.push_back(',');
        }
        std::reverse(with_commas.begin(), with_commas.end());
        digits = with_commas;
    }

    int_part = negative ? "-" + digits : digits;

    if (frac_part.empty())
        return int_part;
    else
        return int_part + "." + frac_part;
}

double factorial(double n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}
