template <typename T>
struct node {
    node* next_;
    T datum_;

    node(const T& d): next_(nullptr), datum_(d) {};
};


template <typename T>
struct queue {
    node<T>* head_;
    node<T>* tail_;

    queue(): head_(nullptr), tail_(nullptr) {};

    void push(const T& d) {
        auto n = new node<T>(d);

        if (head_ == nullptr) {
            head_ = n;
            tail_ = n;
            return;
        }

        tail_->next_ = n;
        tail_ = n;
    }

    T pop() {
        auto ret = head_->datum_;
        auto old = head_;
        head_ = head_->next_;
        delete old;
        return ret;
    }

    T peek() {
        return head_->datum_;
    }

    bool empty() {
        return head_ == nullptr;
    }

    ~queue() {
        while (!empty())
            pop();
    }
};
