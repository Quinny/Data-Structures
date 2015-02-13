#include <iostream>
#include <cassert>
#include <random>
#include <set>
#include <algorithm>
#include "threaded_tree.h"
#include <iterator>
#define N 1000000

int main() {
    srand(time(NULL));
    qap::threaded_tree<int, std::greater<int>> t;

    for (int i = 0; i < 10; i++)
        t.insert(2 * i + 1);
    decltype(t)::iterator j = t.begin();
    while (j != t.end()) {
        std::cout << *(j++) << std::endl;
    }
}
