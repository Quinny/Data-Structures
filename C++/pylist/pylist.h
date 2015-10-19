#ifndef _QP_PYLIST_H_
#define _QP_PYLIST_H_
#include <vector>
#include <iostream>
#include <algorithm>

// Implementation of a python-like list structure
// Designed for ease of use as opposed to performance and type safety

namespace qap {

template <typename T>
class pylist {
private:
    std::vector<T> list_;

public:
    using iterator = typename std::vector<T>::const_iterator;

    // ------------------
    // Constructors
    // ------------------
    pylist() : list_{} {};

    pylist(std::vector<T> const& v) : list_(v) {};

    pylist(std::initializer_list<T> const& init) : list_(init) {
        /*for (auto const& i : init)
            append(i);*/
    }

    // Allow pylist to be constructed with any container
    // type as long as as the types match
    template <typename Container>
    pylist(Container c) {
        for (auto const& i : c)
            append(i);
    }

    pylist(pylist const& other) : list_(other.list_) {};
    pylist(pylist&& other) {
        std::swap(list_, other.list_);
    }

    iterator begin() const {
        return list_.begin();
    }
    iterator end() const {
        return list_.end();
    }
    std::size_t size() const {
        return list_.size();
    }

    // --------------------
    // Modifying functions
    // --------------------
    void append(T const& x) {
        list_.push_back(x);
    }

    T pop() {
        list_.pop_back();
    }

    template <typename Container>
    void extend(Container const& c) {
        for (auto const& i : c)
            list_.push_back(i);
    }

    template <typename Compare = std::less<T>>
    void sort(bool reverse_ = false) {
        Compare c;
        std::sort(list_.begin(), list_.end(), c);
        if (reverse_)
            reverse();
    }

    void reverse() {
        std::reverse(list_.begin(), list_.end());
    }

    std::size_t count(T const& x) {
        std::size_t c = 0;
        for (auto const& i : list_) {
            if (i == x)
                ++c;
        }
        return c;
    }

    void insert(std::size_t i, T const& x) {
        list_.insert(i, x);
    }


    // ---------------------
    // Operators
    // ---------------------
    // Most of the python operators return a new instance
    // of a list so things like:
    // x = x + {1,2,3} + 5 are possible
    template <typename Container>
    pylist operator + (Container const& c) const {
        pylist<T> n = *this;
        for (auto const& i : c)
            n.append(i);
        return n;
    }

    pylist operator + (T const& x) const {
        std::vector<T> n = list_;
        n.push_back(x);
        return pylist(n);
    }

    template <typename Container>
    void operator += (Container const& c) {
        extend(c);
    }

    void operator += (T const& x) {
        append(x);
    }

    pylist& operator = (pylist<T>&& p) {
        std::swap(list_, p.list_);
        return *this;
    }

    pylist& operator = (pylist<T> const& p) {
        list_ = p.list_;
        return *this;
    }

    T& operator[] (std::size_t i) {
        return list_[i];
    }

    T operator[] (std::size_t i) const {
        return list_[i];
    }
};

// Tuple style pair print
template <typename T, typename U>
std::ostream& operator << (std::ostream& out, std::pair<T, U> const& p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

// Python style printing
template <typename T>
std::ostream& operator << (std::ostream& out, pylist<T> const& p) {
    out << "[";
    for (auto i = p.begin(); i != p.end(); ++i) {
        out << *i;
        if (std::next(i) != p.end())
            out << ", ";
    }
    out << "]";
    return out;
}

} // namespace qap

#endif // include guard
