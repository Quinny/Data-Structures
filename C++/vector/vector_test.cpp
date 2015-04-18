#include "vector.h"
#include <iostream>
#include <cassert>
#include "qp_bm"
#include <random>

int main(){
    qap::vector<int> v;
    std::vector<int> v2;
    qap::bm::compare_all(v, rand, rand, 
                        v2, rand, rand, 10000000);
}
