#include <iostream>
#include "threaded_tree.h"
#include <algorithm>
#include <cassert>
#include <random>
#include <map>

int main() {
    srand(time(NULL));
    qap::threaded_tree<int> t;
    for (int i = 0; i < 1000000; ++i)
        t.insert(rand());
    for(auto s : t);

    return 0;
}
