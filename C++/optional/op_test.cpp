#include <iostream>
#include "optional.h"

optional<int> try_parse(std::string s) {
    int ret = 0, i = 0, sign = 1;
    if (s[i] == '-') {
        sign = -1;
        ++i;
    }

    for (; i < s.size(); ++i) {
        if (!std::isdigit(s[i]))
            return optional<int>();
        ret = (ret * 10) + (s[i] - '0');
    }
    return optional<int>(ret * sign);
}

int main() {
    optional<int> x = try_parse("-1234");
    x.if_present([](int y) { std::cout << y << std::endl;});

    optional<int> z = try_parse("a-1234");
    z.if_present([](int y) { std::cout << y << std::endl;});
}
