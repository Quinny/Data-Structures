#include <iostream>
#include <random>
#include "hash_table.h"
#include <cassert>
#include <time.h>
#include <unordered_map>

#include "../benchmark.h"

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
    //std::cout << "inserting mine" << std::endl;
    //qap::bm::insert(t, gen, 1000000);

   // std::cout << "inserting theirs" << std::endl;
    std::unordered_map<std::string, int> m;
    //qap::bm::insert(m, gen, 1000000);
/*
    std::cout << "Assuring that lookup works..." << std::endl;
    qap::hash_table<std::string, int> t2;
    for (auto i : m)
        t2.insert({i.first, i.second});
    for (auto i : m)
        assert(t2.find(i.first).value == i.second);
    std::cout << "yup its good" << std::endl;
    assert(t2.size() == m.size());

    std::cout << "iterating mine" << std::endl;
    qap::bm::iterate(t);
    std::cout << "iterating theirs" << std::endl;
    qap::bm::iterate(m);
    
    std::cout << "copying mine" << std::endl;
    qap::bm::copy(t);
    std::cout << "copying theirs" << std::endl;
    qap::bm::copy(m);
    
    std::cout << "moving mine" << std::endl;
    qap::bm::move(t);
    std::cout << "moving theirs" << std::endl;
    qap::bm::move(m);*/

    qap::bm::compare_all(t, m, gen, 1000000);
    
    return 0;
}
