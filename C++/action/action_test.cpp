#include "action.h"
#include <iostream>

class Doer {
public:
    qap::action<int> on_even;
    qap::action<int> on_odd;

    void read() {
        int n;
        while (std::cin >> n) {
            if (n % 2 == 0)
                on_even(n);
            else
                on_odd(n);
        }
    }
};

void f(int x) {
    std::cout << x << " is even" << std::endl;
}

void f2(int x) {
    std::cout << x << " is even again..." << std::endl;
}

void g(int x) {
    std::cout << x << " is odd" << std::endl;
}

int main() {
    Doer d;
    d.on_even = f;
    d.on_even += f2;
    d.on_odd = g;
    d.read();
}
