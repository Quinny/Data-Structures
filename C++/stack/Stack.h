#ifndef QP_STACK_H__
#define QP_STACK_H__

namespace qap {

template <typename T>
struct node {
	T datum_;
	node<T>* next_;

	node() : next_(nullptr) {};
	node(T const& val) : next_(nullptr), datum_(val) {};
};

template <typename T>

struct stack {
    node<T>* head_;
	stack() : head_(nullptr) {};

    stack(stack<T> const& s) : head_(nullptr) {
       node<T>* tmp = s.head_;
       while (tmp != nullptr) {
           push(tmp->datum_);
           tmp = tmp->next_;
        }
    }

    stack(stack<T>&& s) : head_(s.head_) {
        s.head_ = nullptr;
    }

    ~stack() {
        while (!empty())
            pop();
    }

    void push(T const& val){
		node<T>* n = new node<T>(val);
		n->next_ = head_;
		head_ = n;
	}
	
    T peek() const {
		return head_->datum_;
	}

	void pop() {
		node<T>* tmp = head_;
		head_ = head_->next_;
		delete tmp;
	}

	bool empty(){
		return head_ == nullptr;
	}
};

} // qap namespace

//ifndef QP_STACK_H__
#endif
