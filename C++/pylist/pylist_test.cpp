#include <iostream>
#include "pylist.h"
#include "pyfunctions.h"
#include <set>

int main() {
    qap::pylist<int> x{99, 100};
    std::vector<int> y = {1,2,3,4};
    std::set<int> s {1000, 1001, -5};
    x.extend(s);
    x += 10;
    x = x + 5 + y;
    x[0] = 2;
    x.sort(true);

    auto z = qap::py::map([](int x) { return "test"; }, x);
    auto zipper = qap::py::zip(x, z);

    zipper.sort();
    std::cout << zipper << std::endl;
    std::cout << x << std::endl;
    std::cout << qap::py::sum(x) << std::endl;
    std::cout << z << std::endl;

    std::cout << x.count(2) << std::endl;
    return 0;
}
