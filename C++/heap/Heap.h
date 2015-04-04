#ifndef QP_HEAP_H__
#define QP_HEAP_H__

#include <vector>

template <typename T>


/*

	PARENT CHILD RELATIONS:

	parent index = ((i+1)/2)-1
	left child   = (2*i)+1
	right child  = (2*i)+2



*/

class Heap{

	private:
		std::vector<T> heap_;

	public:
		void insert(T const&);
		void print();
		T pop();
		T peek();

		bool empty();
		int size();

	private:
		void upHeap();
		void downHeap();
};


template <typename T>

bool Heap<T>::empty(){
	return heap_.size()==0;
}

template <typename T>

int Heap<T>::size(){
	return heap_.size();
}

template <typename T>

void Heap<T>::insert(T const& val){
	heap_.push_back(val);
	upHeap();
}

template <typename T>

void Heap<T>::upHeap(){
	for(int i=heap_.size()-1;i>0;){
		int parent=((i+1)/2)-1; //the index of the parent node

		if(heap_[parent] > heap_[i]) //if the parent is greater than the child then were done
			break;

		std::swap(heap_[parent],heap_[i]); //otherwise swap them and continue

		i=parent;
	}
}


template <typename T>

void Heap<T>::downHeap(){
	int i=0;

	while(true){
		int leftChild=2*i+1;
		int rightChild=2*i+2;

		if(leftChild>=heap_.size()) break; //reached the bottom of the heap, cant move the element any lower

		int swapIndex=leftChild; //start the swap index at the left child because it will always exist

		if(rightChild < heap_.size() && heap_[rightChild] > heap_[leftChild] ){ //if the right child exists, and is greater than the left child
			swapIndex=rightChild;
		}

		if(heap_[i] > heap_[swapIndex]) break; //if the current node is greater than its greatest child, then order is restored

		std::swap(heap_[i],heap_[swapIndex]); //swap the current index with the greater of its 2 children

		i=swapIndex; //update the current;
	}
}

template <typename T>

void Heap<T>::print(){
	for(int i=0;i<heap_.size();i++){
		std::cout<<(heap_[i])<<" ";
	}
	std::cout<<std::endl;
}

template <typename T>

T Heap<T>::pop(){
	T val=heap_.front();
	std::swap(heap_.front(),heap_.back());
	heap_.pop_back();
	downHeap();
	return val;
}

template <typename T>

T Heap<T>::peek(){
	return heap_.front();
}



//ifndef QP_HEAP__
#endif
