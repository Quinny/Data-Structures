#ifndef _QP_BK_TREE_H_
#define _QP_BK_TREE_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

namespace qap {

// Helper function for comparing two strings
// and computing the edit distance between them
//
// Maybe generalize this for all containers?
unsigned lev_dist(std::string const& s1, std::string const& s2) {
    const std::size_t len1 = s1.size();
    const std::size_t len2 = s2.size();

    std::vector<unsigned> col(len2 + 1);
    std::vector<unsigned> prev_col(len2 + 1);

    for (unsigned i = 0; i < prev_col.size(); ++i)
        prev_col[i] = i;
    for (unsigned i = 0; i < len1; ++i) {
        col[0] = i + 1;
        for (unsigned j = 0; j < len2; ++j) {
            unsigned cmp = !(s1[i] == s2[j]);
            col[j + 1] =
                std::min({prev_col[j + 1] + 1, col[j] + 1, prev_col[j] + cmp});
        }
        col.swap(prev_col);
    }
    return prev_col[len2];
}

// Node structure for bk_tree
// Maps lev distances to other nodes
struct bk_node {
    // maps lev_distance to new node
    std::map<int, bk_node*> edges_;
    std::string word_;

    bk_node(std::string const& s) : word_(s) {};
};

class bk_tree {

private:
    bk_node* root_;

public:
    bk_tree() : root_(nullptr) {};
    ~bk_tree();
    void insert(std::string const&);
    void print() const;
    void print(bk_node*) const;
    // find all strings within n units of input string
    std::vector<std::string> find_all(std::string const& s, int n) const;
};

bk_tree::~bk_tree() {
    if (root_ == nullptr)
        return;
    std::queue<bk_node*> q;
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

std::vector<std::string>
bk_tree::find_all(std::string const& s, int n) const {
    std::queue<bk_node*> q;
    std::vector<std::string> results;
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

void bk_tree::insert(std::string const& s) {
    if (root_ == nullptr) {
        root_ = new bk_node(s);
        return;
    }
    bk_node* curpos = root_;
    while (true) {
        auto dist = lev_dist(curpos->word_, s);
        // test insert with nullptr to avoid allocating memory
        auto test = curpos->edges_.insert({dist, nullptr});
        // If the insertion was successfull, then the node did not exist
        if (test.second) {
            test.first->second = new bk_node(s);
            return;
        }
        curpos = test.first->second;
    }
}

} // qap namesapce

#endif // include guard
