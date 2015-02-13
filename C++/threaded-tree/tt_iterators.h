#ifndef _QP_TT_ITERATORS_H_
#define _QP_TT_ITERATORS_H_
#include "threaded_tree.h"

/*
 * Threaded tree forward iterators for iterating through the elements
 * in increasing order
 */

template <typename T>
class tt_iterator {
    Node<T>* n;
    public:
        tt_iterator(Node<T>* t) : n(t) {};
        tt_iterator() : n(nullptr) {};
        bool operator == (tt_iterator<T> const& t) const {
            return t.n == n;
        }

        bool operator != (tt_iterator<T> const& t) const {
            return t.n != n;
        }

        T operator *() const {
            return n->datum_;
        }

        tt_iterator<T>& operator ++() {
            // if the current node is threaded, simply traverse the thread
            if (n->threaded_right())
                n = n->right_;
            else
                // otherwise move to the left most node in the right tree
                // (which will be guarunteed to be threaded)
                n = left_most(n->right_);
            return *this;
        }

        tt_iterator<T> operator ++(int) {
            tt_iterator<T> tmp = *this;
            operator++();
            return tmp;
        }

    private:
        Node<T>* left_most(Node<T>* root) const {
            if (root == nullptr)
                return nullptr;
            while (root->left_ != nullptr && !root->threaded_left())
                root = root->left_;
            return root;
        }
};

/*
 * Reverse iterators for moving in decreasing order through the elements
 */

template <typename T>
class r_tt_iterator {
    Node<T>* n;
    public:
        r_tt_iterator(Node<T>* t) : n(t) {};
        r_tt_iterator() : n(nullptr) {};
        bool operator == (r_tt_iterator<T> const& t) const {
            return t.n == n;
        }

        bool operator != (r_tt_iterator<T> const& t) const {
            return t.n != n;
        }

        T operator *() const {
            return n->datum_;
        }

        r_tt_iterator<T>& operator ++() {
            // if the current node is threaded, simply traverse the thread
            if (n->threaded_left())
                n = n->left_;
            else
                // otherwise move to the left most node in the right tree
                // (which will be guarunteed to be threaded)
                n = right_most(n->left_);
            return *this;
        }

        r_tt_iterator<T> operator ++(int) {
            r_tt_iterator<T> tmp = *this;
            operator++();
            return tmp;
        }

    private:
        Node<T>* right_most(Node<T>* root) const {
            if (root == nullptr)
                return nullptr;
            while (root->right_ != nullptr && !root->threaded_right())
                root = root->right_;
            return root;
        }
};


#endif
