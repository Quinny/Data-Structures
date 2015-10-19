#ifndef _QP_FORWARD_LIST_H
#define _QP_FORWARD_LIST_H

namespace qap {

template <typename T>
class forward_list {
private:
    struct node {
        node* next_;
        T datum_;
        node(T const& x) : datum_(x), next_(nullptr) {};
    };

    node* tail_;

public:
    forward_list() : tail_(nullptr) {};

    void push_back(T const& x) {
        node* n = new node(x);
        if (tail_ == nullptr) {
            tail_ = 
        }
    }
};

}

#endif
