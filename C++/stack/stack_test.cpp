#include <iostream>
#include "Stack.h"
#include "qp_bm"
#include <random>
#include <stack>
#include <vector>

int main(){
    qap::stack<int> s1;
    std::vector<int> s2;
    qap::bm::compare_all(s1, rand, rand,
                        s2, rand, rand, 1000000);
    return 0;
}
