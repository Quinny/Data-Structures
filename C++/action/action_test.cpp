#include "action.h"
#include <iostream>

void sq (int x) {
    std::cout << x * x << std::endl;
}

void cube (int x) {
    std::cout << x * x * x << std::endl;
}

int main() {
    qap::action<int> f;
    f += sq;
    f += cube;
    f(4);
}
