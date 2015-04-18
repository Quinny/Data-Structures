#include <iostream>
#include "heap.h"
#include <random>
#include <cassert>
#include <algorithm>
#include "qp_bm"
#include <queue>

int main(void){
    qap::heap<int> h;
    std::priority_queue<int> q;
    qap::bm::compare_all(h, rand, rand,
                         q, rand, rand, 1000000);
    assert(std::is_heap(h.cbegin(), h.cend()));
    return 0;
}
