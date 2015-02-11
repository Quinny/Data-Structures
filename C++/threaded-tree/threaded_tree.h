#ifndef _QP_THREADED_TREE_H_
#define _QP_THREADED_TREE_H_

#include <vector> // just for testing the sorted-ness

template <typename T>
struct Node {
    Node(T d) : datum_(d), left_(nullptr), right_(nullptr), is_threaded(false) {};

    Node* left_;
    Node* right_;
    T datum_;
    // if false, the right child is the actual right child
    // if true, the right child is the next node in the in-order traversal
    bool is_threaded;
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

        void operator ++() {
            if (n->is_threaded)
                n = n->right_;
            else
                n = left_most(n->right_);
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
        Node<T>* left_most(Node<T>* root);

    public:
        threaded_tree() : root_(nullptr) {};
        void insert(T x);
        void insert(Node<T>* n, Node<T>* p);
        // just for testing purposes
        std::vector<T> in_order();

        tt_iterator<T> begin() { return tt_iterator<T>(root_); }
        tt_iterator<T> end() { return tt_iterator<T>(nullptr); }
};

template <typename T>
void threaded_tree<T>::insert(T x) {
    Node<T>* n = new Node<T>(x);
    if (root_ == nullptr)
        root_ = n;
    else
        insert(n, root_);
}

template <typename T>
void threaded_tree<T>::insert(Node<T>* n, Node<T>* p) {
    if (n->datum_ < p->datum_) {
        if (p->left_ == nullptr) {
            p->left_ = n;
            n->right_ = p;
            n->is_threaded = true;
        }
        else
            insert(n, p->left_);
    }
    else {
        if (p->right_ == nullptr || p->is_threaded) {
            p->is_threaded = false;
            n->right_ = p->right_;
            n->is_threaded = true;
            p->right_ = n;
        }
        else
            insert(n, p->right_);
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

template <typename T>
std::vector<T> threaded_tree<T>::in_order() {
    auto cur = left_most(root_);
    std::vector<T> v;
    while (cur != nullptr) {
        v.push_back(cur->datum_);
        if (cur->is_threaded)
            cur = cur->right_;
        else
            cur = left_most(cur->right_);
    }
    return v;
}

#endif
