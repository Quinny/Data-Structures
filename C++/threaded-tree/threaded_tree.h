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

    Node(T const& d) : datum_(d), left_(nullptr), right_(nullptr), thread_mask() {};
    ~Node() {
        if (!threaded_left())
            delete left_;
        if (!threaded_right())
            delete right_;
    }

    bool threaded_left() const {
        return thread_mask[0];
    }

    void threaded_left(bool b) {
        if (b)
            thread_mask.set(0);
        else
            thread_mask.unset(0);
    }

    bool threaded_right() const {
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
        Node<T>* left_most(Node<T>* root) const;
        Node<T>* right_most(Node<T>* root) const;
        tt_iterator<T> insert(Node<T>* n, Node<T>* p);
        void copy_tree(Node<T>* root);

    public:
        using iterator = tt_iterator<T>;

        threaded_tree() : root_(nullptr), size_(0) {};
        threaded_tree(threaded_tree<T, Compare>&& t) : root_(t.root_) {
            std::swap(size_, t.size_);
            t.root_ = nullptr;
        }
        threaded_tree(threaded_tree<T, Compare> const& t) {
            root_ = nullptr;
            size_ = 0;
            // calls insert so handles size
            copy_tree(t.root_);
        }
        ~threaded_tree() { delete root_; }

        tt_iterator<T> insert(T const& x);
        tt_iterator<T> find(T const& x) const;
        bool contains(T const& x) const {
            return find(x) != end();
        }
        std::size_t size() const { return size_; }

        tt_iterator<T> begin() const { return tt_iterator<T>(left_most(root_)); }
        tt_iterator<T> end() const { return tt_iterator<T>(); }

        r_tt_iterator<T> rbegin() const { return r_tt_iterator<T>(right_most(root_)); }
        r_tt_iterator<T> rend()  const { return r_tt_iterator<T>(); }
};

template <typename T, typename Compare>
tt_iterator<T> threaded_tree<T, Compare>::insert(T const& x) {
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
tt_iterator<T> threaded_tree<T, Compare>::find(T const& x) const {
    Node<T>* cur = root_;
    while (cur != nullptr) {
        if (cur->datum_ == x)
            return tt_iterator<T>(cur);
        if (x < cur->datum_) {
            if (cur->threaded_left())
                return tt_iterator<T>();
            cur = cur->left_;
        }
        else {
            if (cur->threaded_right())
                return tt_iterator<T>();
            cur = cur->right_;
        }
    }
    return tt_iterator<T>();
}

template <typename T, typename Compare>
Node<T>* threaded_tree<T, Compare>::left_most(Node<T>* root) const {
    if (root == nullptr)
        return nullptr;
    while (root->left_ != nullptr && !root->threaded_left())
        root = root->left_;
    return root;
}

template <typename T, typename Compare>
Node<T>* threaded_tree<T, Compare>::right_most(Node <T>* root) const {
    if (root == nullptr)
        return nullptr;
    while (root->right_ != nullptr && !root->threaded_right())
        root = root->right_;
    return root;
}

template <typename T, typename Compare>
void threaded_tree<T, Compare>::copy_tree(Node<T>* root) {
    if (root == nullptr)
        return;
    insert(root->datum_);
    if (!root->threaded_left())
        copy_tree(root->left_);
    if (!root->threaded_right())
        copy_tree(root->right_);
}

}
#endif
