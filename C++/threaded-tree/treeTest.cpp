#include <iostream>
#include "threaded_tree.h"
#include <algorithm>
#include <cassert>
#include <random>

int main() {
    srand(time(NULL));
    threaded_tree<int> t;
    for (int i = 0; i < 10; ++i)
        t.insert(rand());
    auto v = t.in_order();
    assert(std::is_sorted(v.begin(), v.end()));


    for(auto s : t)
        std::cout << s << std::endl;

    return 0;
}
