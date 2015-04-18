#include <iostream>
#include <random>
#include "hash_table.h"
#include <cassert>
#include <time.h>
#include <unordered_map>

#include "qp_bm"

std::string random_string() {
    std::string s = "abcdefghijklmnopqrstuvwxyz";
    std::string ret = "";
    for(int i = 0; i < (rand() % 16) + 1; ++i)
        ret += s[rand() % 26];
    return ret;
}

std::pair<std::string, int> gen() {
    return std::make_pair(random_string(), rand());
}

int main(void){
    srand(time(NULL));
    qap::hash_table<std::string, int> t;
    std::unordered_map<std::string, int> m;
    qap::bm::compare_all(t, gen, random_string,
                        m, gen, random_string, 10000000);
    return 0;
}
