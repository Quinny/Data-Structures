#ifndef QP_LINKED_LIST_H__
#define QP_LINKED_LIST_H__

namespace qap {

template <typename T>
struct Node {
    T datum_;
    Node<T>* next_;
    Node <T>* prev_;

    Node(): next_(nullptr),prev_(nullptr) {};
    Node(T const& val): datum_(val),next_(nullptr),prev_(nullptr) {};
};

template <typename T>
class list_iterator {
    private:
    Node<T>* n;

    public:
    list_iterator() : n(nullptr) {};
    list_iterator(Node<T>* t) : n(t) {};

    list_iterator& operator ++ () {
        n = n->next_;
        return *this;
    }

    list_iterator& operator -- () {
        n = n->prev_;
        return *this;
    }

    list_iterator operator -- (int) {
        list_iterator<T> tmp = *this;
        n = n->prev_;
        return tmp;
    }

    list_iterator operator ++ (int) {
        list_iterator<T> tmp = *this;
        n = n->next_;
        return tmp;
    }

    bool operator == (list_iterator<T> const& it) {
        return n == it.n;
    }

    bool operator != (list_iterator<T> const& it) {
        return n != it.n;
    }

    T& operator * () {
        return n->datum_;
    }
};

template <typename T>
struct List {
    Node<T>* head_;
    Node<T>* tail_;
    List(): head_(nullptr), tail_(nullptr) {};

    list_iterator<T> begin() {
        return list_iterator<T>(head_);
    }

    list_iterator<T> end() {
        return list_iterator<T>();
    }

    void push_front(T const& val) {
        Node<T>* n = new Node<T>(val);
        n->next_ = head_;
        head_->prev_ = n;
        head_ = n;
    }

    void push_back(T const& val) {
        Node <T>* n = new Node<T>(val);
        if(head_ == nullptr && tail_ == nullptr){
            head_ = n;
            tail_ = n;
        }
        else {
            n->prev_ = tail_;
            tail_->next_ = n;
            tail_ = n;
        }
    }

    void pop_front() {
        Node<T>* tmp = head_;
        head_ = head_->next_;
        head_->prev_ = nullptr;
        delete tmp;
    }

    void pop_back() {
        Node<T>* tmp = tail_;
        tail_ = tail_->prev_;
        tail_->next_ = nullptr;
        delete tmp;
    }

    bool empty() {
        return head_ == nullptr;
    }
};

}
//#ifndef QP_LINKED_LIST_H__
#endif
