#include <iostream>
#include "optional.h"

int main() {
    optional<int> x;

    x.if_present([](int y) { std::cout << y << std::endl;});
}
