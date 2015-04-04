#ifndef QP_STACK_H__
#define QP_STACK_H__


template <typename T>

struct Node{
	T datum_;
	Node<T>* next_;

	Node():next_(nullptr){};
	Node(T const& val):next_(nullptr), datum_(val) {};
};

template <typename T>

struct Stack{

	Node<T>* head_;

	Stack():head_(nullptr) {};

	void push(T const& val){
		Node<T>* n=new Node<T>(val);
		n->next_=head_;
		head_=n;
	}

	T peek(){
		return head_->datum_;
	}

	T pop(){
		T tmp=peek();
		Node<T>* oldHead=head_;
		head_=head_->next_;
		delete oldHead;
		return tmp;
	}

	bool empty(){
		return head_==nullptr;
	}


};



//ifndef QP_STACK_H__
#endif
