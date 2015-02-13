#ifndef _QP_THREADED_TREE_H_
#define _QP_THREADED_TREE_H_

#include "bool_mask.h"

namespace qap {

template <typename T>
struct Node {
    Node* left_;
    Node* right_;
    T datum_;
    bool_mask thread_mask;

    Node(T d) : datum_(d), left_(nullptr), right_(nullptr), thread_mask() {};
    ~Node() {
        if (!threaded_left())
            delete left_;
        if (!threaded_right())
            delete right_;
    }

    bool threaded_left() {
        return thread_mask[0];
    }

    void threaded_left(bool b) {
        if (b)
            thread_mask.set(0);
        else
            thread_mask.unset(0);
    }

    bool threaded_right() {
        return thread_mask[1];
    }

    void threaded_right(bool b) {
        if (b)
            thread_mask.set(1);
        else
            thread_mask.unset(1);
    }
};


// The depandancy tree got kind of messy
// This is a hacky fix, SHOULD BE RETHOUGHT SOON
#include "tt_iterators.h"


template <typename T, typename Compare = std::less<T>>
class threaded_tree {
    private:
        Node<T>* root_;
        std::size_t size_;
        Compare cmp;
        Node<T>* left_most(Node<T>* root);
        Node<T>* right_most(Node<T>* root);
        tt_iterator<T> insert(Node<T>* n, Node<T>* p);
    public:
        typedef tt_iterator<T> iterator;

        threaded_tree() : root_(nullptr), size_(0) {};
        ~threaded_tree() { delete root_; }

        tt_iterator<T> insert(T x);
        std::size_t size() const { return size_; }

        tt_iterator<T> begin() { return tt_iterator<T>(left_most(root_)); }
        tt_iterator<T> end() { return tt_iterator<T>(); }

        r_tt_iterator<T> rbegin() { return r_tt_iterator<T>(right_most(root_)); }
        r_tt_iterator<T> rend() { return r_tt_iterator<T>(); }
};

template <typename T, typename Compare>
tt_iterator<T> threaded_tree<T, Compare>::insert(T x) {
    Node<T>* n = new Node<T>(x);
    if (root_ == nullptr){
        ++size_;
        root_ = n;
        return begin();
    }
    else
        return insert(n, root_);
}

template <typename T, typename Compare>
tt_iterator<T> threaded_tree<T, Compare>::insert(Node<T>* n, Node<T>* p) {
    while (p != nullptr) {
        if (n->datum_ == p->datum_) {
            delete n;
            return tt_iterator<T>(p);
        }
        if (cmp(n->datum_, p->datum_)) {
            // When inserting node B to the left of A
            if (p->left_ == nullptr || p->threaded_left()) {
                ++size_;

                // set up right thread
                n->right_ = p; // thread the node up to its parent
                n->threaded_right(true);

                // set up left thread
                p->threaded_left(false);
                n->left_ = p->left_;
                n->threaded_left(true);

                // actually add
                p->left_ = n;
                return tt_iterator<T>(n);
            }
            else
                p = p->left_;
        }
        else {
            // When inserting node B to the right of A
            if (p->right_ == nullptr || p->threaded_right()) {
                ++size_;

                // set up right thread
                p->threaded_right(false); // A is not longer threaded
                n->right_ = p->right_; // thread B to A's old thread
                n->threaded_right(true); // B is now threaded

                // set up left thread
                n->left_ = p;
                n->threaded_left(true);

                // actually add
                p->right_ = n;
                return tt_iterator<T>(n);
            }
            else
                p = p->right_;
        }
    }
    return tt_iterator<T>();
}

template <typename T, typename Compare>
Node<T>* threaded_tree<T, Compare>::left_most(Node<T>* root) {
    if (root == nullptr)
        return nullptr;
    while (root->left_ != nullptr && !root->threaded_left())
        root = root->left_;
    return root;
}

template <typename T, typename Compare>
Node<T>* threaded_tree<T, Compare>::right_most(Node <T>* root) {
    if (root == nullptr)
        return nullptr;
    while (root->right_ != nullptr && !root->threaded_right())
        root = root->right_;
    return root;
}

}
#endif
