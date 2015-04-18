#include <iostream>
#include <algorithm>
#include "linked_list.h"
#include <list>
#include "qp_benchmark.h"
#include <random>

int main(void){
    qap::List<int> one;
    std::list<int> two;

    qap::bm::compare_all(one, rand, two, rand, 1000000);
    return 0;
}
