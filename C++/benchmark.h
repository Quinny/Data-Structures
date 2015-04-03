#ifndef QP_BENCH_MARK_H_
#define QP_BENCH_MARK_H_

#include <chrono>
#include <iostream>
#include <cstddef> // for size_t

namespace qap {

namespace bm {

using namespace std::chrono;

// Takes a container and a generating function (no arguments)
// and performs n inserts on the container with the output of the generating
// function.  The time taken to do the inserts is reported in seconds.
template <typename Container, typename Gen>
void insert(Container& c, Gen g, std::size_t n) {
    auto t1 = high_resolution_clock::now();
    while (n--)
        c.insert(g());
    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << " seconds" << std::endl;
}

template <typename Container>
void iterate(Container& c) {
    auto t1 = high_resolution_clock::now();
    for (auto i : c)
    ; // suppress warnings with semi colon on next line
    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << std::endl;
}

} // bm namespace

} // qap namespace

#endif // include guard
