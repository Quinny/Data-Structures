//Header guards to prevent double inclusions (same file being included twice)

#ifndef QP_LINKED_LIST_H__
#define QP_LINKED_LIST_H__

template <typename T>

struct Node{

	T datum_;
	Node<T>* next_;
	Node <T>* prev_;

	Node(): next_(nullptr),prev_(nullptr) {};
	Node(T const& val): datum_(val),next_(nullptr),prev_(nullptr) {};

};


template <typename T>

//over load the insertion (<<) operator for ostream so that Nodes will display nicely with std::cout<<Node

std::ostream& operator << (std::ostream& os, Node<T> const& n){
	os<<n.datum_;
	return os;
}


template <typename T>

struct List{
	Node<T>* head_;
	Node<T>* tail_;
	List(): head_(nullptr),tail_(nullptr) {}


	void insert(T const& val){
		Node <T>* n=new Node<T>(val);

		if(head_==nullptr && tail_==nullptr){
			head_=n;
			tail_=n;
			return;
		}
		n->prev_=tail_;
		tail_->next_=n;
		tail_=n;
	}

	void insertOrdered(T const& val){
		Node <T>* n=new Node<T>(val);

		if(n->datum_ < head_->datum_){ //inserted value is less than the first value
			n->next_=head_;
			head_->prev_=n;
			head_=n;
			return;
		}

		if(n->datum_ > tail_->datum_){ //inserted value is greater than the last value
			insert(val);
			return;
		}

		Node<T>* tmp=head_; //somewhere in between
		while(tmp->next_!=nullptr && n->datum_ > tmp->next_->datum_)
			tmp=tmp->next_;
		insertAfter(n,tmp);
	}

	bool member(T const& val){
		Node<T>* tmp=head_;

		while(tmp!=nullptr){
			if(tmp->datum_==val)
				return true;
			tmp=tmp->next_;
		}
		return false;
	}

	Node<T>* find(T const& val){
		Node<T>* tmp=head_;
		while(tmp!=nullptr){
			if(tmp->datum_==val)
				return tmp;
			tmp=tmp->next_;
		}
		return nullptr;
	}

	void remove(T const& val){
		Node<T>* del=find(val);

		if(del==nullptr)
			return;

		if(del==head_){
			Node<T>* oldHead=head_;
			head_=head_->next_;
			head_->prev_=nullptr;
			delete oldHead;
			return;
		}

		if(del==tail_){
			Node<T>* oldTail=tail_;
			tail_=tail_->prev_;
			tail_->next_=nullptr;
			delete oldTail;
			return;
		}

		Node <T>* tmp2=del->prev_;
		del->prev_->next_=del->next_;
		del->next_->prev_=tmp2;
		delete del;
	}

	void insertAfter(Node<T>* n, Node<T>* after){
		n->prev_=after;
		n->next_=after->next_;
		after->next_->prev_=n;
		after->next_=n;
	}

	void reverse(){
		Node<T>* tmp=head_;

		head_=tail_;
		tail_=tmp;
		
		Node<T>* tmp2;
		while(tmp!=nullptr){
			tmp2=tmp->prev_;
			tmp->prev_=tmp->next_;
			tmp->next_=tmp2;
			tmp=tmp->prev_;
		}
	}

};


template <typename T>

std::ostream& operator << (std::ostream& os, List<T> const& l){
	Node<T>* tmp=l.head_;
	os<<"(";
	while(tmp!=nullptr){
		os<<(*tmp);
		if(tmp->next_!=nullptr)
			os<<",";
		tmp=tmp->next_;
	}
	os<<")";
	return os;
}


//#ifndef QP_LINKED_LIST_H__
#endif
