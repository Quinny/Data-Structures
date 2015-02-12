#include <iostream>
#include "threaded_tree.h"
#include <cassert>
#include <random>
#include <set>
#include <algorithm>

int main() {
    srand(time(NULL));
    qap::threaded_tree<int> t;
    //std::set<int> t;
    for (int i = 0; i < 1000000; ++i)
        t.insert(rand());
    for (auto i : t)
    ;
    return 0;
}
