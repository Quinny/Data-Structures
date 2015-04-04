#include "vector.h"
#include <iostream>
#include <cassert>
#include "qp_benchmark.h"
#include <random>

int main(){
    qap::vector<int> v;
    std::vector<int> v2;
    qap::bm::compare_all(v, rand, v2, rand, 1000000);
}
