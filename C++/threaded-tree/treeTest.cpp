#include <iostream>
#include <random>
#include <set>
#include "threaded_tree.h"
#include <chrono>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <limits.h>
#include "qp_benchmark.h"

#define N 1000000
using namespace std::chrono;

template <typename Tree>
void insert_benchmark(Tree t);

template <typename Tree>
void iteration_benchmark(Tree t);

std::default_random_engine gen;
std::uniform_int_distribution<int> dst(INT_MIN, INT_MAX);

int main() {
    qap::threaded_tree<int> t;
    std::set<int> s;
    /*gen.seed(time(NULL));
    insert_benchmark(t);
    insert_benchmark(s);

    iteration_benchmark(t);
    iteration_benchmark(s);*/
    qap::bm::compare_all(t, rand, s, rand, 1000000);
}

template <typename Tree>
void iteration_benchmark(Tree t) {
    auto t1 = high_resolution_clock::now();
    for (auto i : t)
    ;
    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << std::endl;
    std::vector<int> v(N);
    std::copy(t.begin(), t.end(), v.begin());
    assert(std::is_sorted(v.begin(), v.end()));
}

template <typename Tree>
void insert_benchmark(Tree t) {
    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        t.insert(dst(gen));
    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << std::endl;
}
