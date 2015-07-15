#ifndef _QP_BK_TREE_H_
#define _QP_BK_TREE_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

namespace qap {

// Helper function for comparing containers
// and computing the edit distance between them
template <typename T,
         template <typename, typename ...> class Container>
unsigned lev_dist(Container<T> const& s1, Container<T> const& s2) {
    const std::size_t len1 = s1.size();
    const std::size_t len2 = s2.size();

    std::vector<unsigned> col(len2 + 1);
    std::vector<unsigned> prev_col(len2 + 1);

    for (unsigned i = 0; i < prev_col.size(); ++i)
        prev_col[i] = i;
    unsigned i = 0;
    for (auto it1 : s1) {
        col[0] = i + 1;
        unsigned j = 0;
        for (auto it2 : s2) {
            unsigned cmp = !(it1 == it2);
            col[j + 1] =
                std::min({prev_col[j + 1] + 1, col[j] + 1, prev_col[j] + cmp});
            ++j;
        }
        col.swap(prev_col);
        ++i;
    }
    return prev_col[len2];
}

// Node structure for bk_tree
// Maps lev distances to other nodes
template <typename T>
struct bk_node {
    // maps lev_distance to new node
    std::map<int, bk_node*> edges_;
    T word_;

    bk_node(T const& s) : word_(s) {};
};

template <typename T = char,
         template <typename, typename ...> class Container = std::basic_string>
class bk_tree {

public:
    using value_type = T;
    using container_type = Container<T>;

private:
    bk_node<container_type>* root_;

public:
    bk_tree() : root_(nullptr) {};
    bk_tree(bk_tree<value_type, Container>&& n) {
        root_ = n.root_;
        n.root_ = nullptr;
    }

    // copy constructor requires some thought...

    ~bk_tree();
    void insert(container_type const&);
    void print() const;
    void print(bk_node<container_type>*) const;
    // find all strings within n units of input string
    std::vector<container_type> find_all(container_type const& s, int n) const;
};

template <typename T,
         template <typename, typename ...> class Container>
std::vector<Container<T>>
bk_tree<T, Container>::find_all(container_type const& s, int n) const {
    std::queue<bk_node<container_type>*> q;
    std::vector<container_type> results;
    q.push(root_);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int d = lev_dist(s, cur->word_);
        // if the current node is within our tolerance, then add it
        if (d <= n)
            results.push_back(cur->word_);
        // query all nodes in the range
        // [d - n, d + n]
        for (int i = -1 * n; i <= n; ++i) {
            if (d + i < 0)
                continue;
            auto test = cur->edges_.find(d + i);
            if (test != cur->edges_.end())
                q.push(test->second);
        }
    }
    return results;
}

template <typename T,
         template <typename, typename ...> class Container>
void bk_tree<T, Container>::insert(container_type const& s) {
    if (root_ == nullptr) {
        root_ = new bk_node<container_type>(s);
        return;
    }
    bk_node<container_type>* curpos = root_;
    while (true) {
        auto dist = lev_dist(curpos->word_, s);
        // test insert with nullptr to avoid allocating memory
        auto test = curpos->edges_.insert({dist, nullptr});
        // If the insertion was successfull, then the node did not exist
        if (test.second) {
            test.first->second = new bk_node<container_type>(s);
            return;
        }
        curpos = test.first->second;
    }
}

template <typename T,
         template <typename, typename ...> class Container>
bk_tree<T, Container>::~bk_tree() {
    if (root_ == nullptr)
        return;
    std::queue<bk_node<container_type>*> q;
    q.push(root_);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto i : cur->edges_)
            q.push(i.second);
        cur->edges_.clear();
        delete cur;
    }
}

} // qap namesapce

#endif // include guard
