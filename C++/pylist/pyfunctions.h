#ifndef _QP_PY_FUNCTIONS_H_
#define _QP_PY_FUNCTIONS_H_
#include "pylist.h"

namespace qap {

namespace py {

template <typename T, typename Pred>
pylist<T> filter(Pred p, pylist<T> const& l) {
    pylist<T> n;
    for (auto const& i : l) {
        if (p(i))
            n.append(i);
    }
    return n;
}

template <typename T, typename Trans>
auto map(Trans f, pylist<T> const& l) -> pylist<decltype(f(T{}))> {
    pylist<decltype(f(T{}))> n;
    for (auto const& i : l)
        n.append(f(i));
    return n;
}

template <typename T, typename Red>
T reduce(Red f, pylist<T> const& l, T init) {
    T ret = init;
    for (auto const& i : l)
        ret = f(i, ret);
    return ret;
}

template <typename T>
pylist<std::pair<std::size_t, T>>
enumerate(pylist<T> const& l) {
    pylist<std::pair<std::size_t, T>> n;
    std::size_t cur = 0;
    for (auto const& i : l) {
        n.append({cur, i});
        ++cur;
    }
    return n;
}

template <typename T, typename U>
pylist<std::pair<T, U>>
zip(pylist<T> const& l1, pylist<U> const& l2) {
    pylist<std::pair<T, U>> n;
    for (std::size_t i = 0; i < std::min(l1.size(), l2.size()); ++i)
        n.append({l1[i], l2[i]});
    return n;
}

// specialized version of reduce for convienice
template <typename T>
T sum(pylist<T> const& l) {
    return reduce(
            [](T x, T y) { return x + y; },
            l, 0
        );
}

} // namespace py

} // namespace qap

#endif // include guard
