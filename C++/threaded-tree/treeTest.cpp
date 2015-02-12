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
    qap::threaded_tree<int> t;
    //std::set<int> t;
    for (int i = 0; i < N; i++)
        t.insert(rand());
    std::vector<int> v(N);
    std::copy(t.begin(), t.end(), v.begin());
    assert(std::is_sorted(v.begin(), v.end()));

    std::copy(t.rbegin(), t.rend(), v.begin());
    assert(std::is_sorted(v.begin(), v.end(), [] (int x, int y) { return x > y; }));
    int c = 0;
    for (auto i : t)
        ++c;
    std::cout << c << std::endl;
    c = 0;
    for (auto i = t.rbegin(); i != t.rend(); ++i)
        ++c;
    std::cout << c << std::endl;
    return 0;
}
