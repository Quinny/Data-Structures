#ifndef _QP_THREADED_TREE_H_
#define _QP_THREADED_TREE_H_

#include <vector> // just for testing the sorted-ness

namespace qap {

template <typename T>
struct Node {
    Node* left_;
    Node* right_;
    T datum_;
    // if false, the right child is the actual right child
    // if true, the right child is the next node in the in-order traversal
    bool is_threaded;

    Node(T d) : datum_(d), left_(nullptr), right_(nullptr), is_threaded(false) {};
    ~Node() {
        delete left_;
        if (!is_threaded)
            delete right_;
    }
};

template <typename T>
class tt_iterator {
    Node<T>* n;
    public:
        tt_iterator(Node<T>* t) : n(t) {};
        bool operator == (tt_iterator<T> const& t) {
            return t.n == n;
        }

        bool operator != (tt_iterator<T> const& t) {
            return t.n != n;
        }

        T operator *() {
            return n->datum_;
        }

        tt_iterator<T>& operator ++() {
            // if the current node is threaded, simply traverse the thread
            if (n->is_threaded)
                n = n->right_;
            else
                // otherwise move to the left most node in the right tree
                // (which will be guarunteed to be threaded)
                n = left_most(n->right_);
            return *this;
        }

    private:
        Node<T>* left_most(Node<T>* root) {
            if (root == nullptr)
                return nullptr;
            while (root->left_ != nullptr)
                root = root->left_;
            return root;
        }
};


template <typename T>
class threaded_tree {
    private:
        Node<T>* root_;
        std::size_t size_;

        Node<T>* left_most(Node<T>* root);
        std::pair<tt_iterator<T>, bool> insert(Node<T>* n, Node<T>* p);
    public:
        threaded_tree() : root_(nullptr), size_(0) {};
        ~threaded_tree() { delete root_; }

        std::pair<tt_iterator<T>, bool> insert(T x);
        std::size_t size() const { return size_; }

        tt_iterator<T> begin() { return tt_iterator<T>(root_); }
        tt_iterator<T> end() { return tt_iterator<T>(nullptr); }
};

template <typename T>
std::pair<tt_iterator<T>, bool> threaded_tree<T>::insert(T x) {
    Node<T>* n = new Node<T>(x);
    if (root_ == nullptr){
        root_ = n;
        return std::make_pair(begin(), true);
    }
    else
        return insert(n, root_);
}

template <typename T>
std::pair<tt_iterator<T>, bool> threaded_tree<T>::insert(Node<T>* n, Node<T>* p) {
    if (n->datum_ == p->datum_) {
        delete n;
        return std::make_pair(tt_iterator<T>(p), false);
    }
    if (n->datum_ < p->datum_) {
        // When inserting node B to the left of A
        if (p->left_ == nullptr) {
            p->left_ = n; // assign the left value
            n->right_ = p; // thread the node up to its parent
            n->is_threaded = true;
            return std::make_pair(tt_iterator<T>(n), true);
        }
        else
            return insert(n, p->left_);
    }
    else {
        // When inserting node B to the right of A
        if (p->right_ == nullptr || p->is_threaded) {
            p->is_threaded = false; // A is not longer threaded
            n->right_ = p->right_; // thread B to A's old thread
            n->is_threaded = true; // B is now threaded
            p->right_ = n;
            return std::make_pair(tt_iterator<T>(n), true);
        }
        else
            return insert(n, p->right_);
    }
}

template <typename T>
Node<T>* threaded_tree<T>::left_most(Node<T>* root) {
    if (root == nullptr)
        return nullptr;
    while (root->left_ != nullptr)
        root = root->left_;
    return root;
}

}
#endif
