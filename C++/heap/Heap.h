#ifndef QP_HEAP_H__
#define QP_HEAP_H__

#include <vector>
#include <cstddef>
/*
	PARENT CHILD RELATIONS:

	parent index = ((i+1)/2)-1
	left child   = (2*i)+1
	right child  = (2*i)+2
*/

namespace qap {

template <typename T>
class heap {
	private:
		std::vector<T> heap_;

    public:
        heap() = default;
        heap(heap<T> const& h) {
            heap_ = h.heap_;
        }
        heap (heap<T>&& h) {
            std::swap(heap_, h.heap_);
        }
		void push(T const&);
		void pop();
		T top() const;

		bool empty() const;
        std::size_t size() const;

        typename std::vector<T>::const_iterator cbegin() const {
            return heap_.cbegin();
        }

        typename std::vector<T>::const_iterator cend() const {
            return heap_.cend();
        }
	private:
		void up_heap();
		void down_heap();
};

template <typename T>
bool heap<T>::empty() const {
	return heap_.size() == 0;
}

template <typename T>
std::size_t heap<T>::size() const {
	return heap_.size();
}

template <typename T>
void heap<T>::push(T const& val) {
	heap_.push_back(val);
	up_heap();
}

template <typename T>
void heap<T>::up_heap() {
	for(std::size_t i = heap_.size() - 1; i > 0;){
		//the index of the parent node
        std::size_t parent=((i + 1) / 2) - 1;
        //if the parent is greater than the child then we
        //are done
		if(heap_[parent] > heap_[i])
            break;
		std::swap(heap_[parent], heap_[i]); //otherwise swap them and continue
		i = parent;
	}
}

template <typename T>
void heap<T>::down_heap() {
	int i = 0;
	while(true){
        std::size_t left_child = 2 * i + 1;
        std::size_t right_child = 2 * i + 2;

        //reached the bottom of the heap, cant move the element any lower
		if(left_child >= heap_.size())
            break;
	    //start the swap index at the left child because it will always exist
	    int swap_index = left_child;
        if(right_child < heap_.size() && heap_[right_child] > heap_[left_child])
			swap_index = right_child;

		if(heap_[i] > heap_[swap_index])
            break;
		std::swap(heap_[i], heap_[swap_index]);
		i = swap_index;
	}
}

template <typename T>
void heap<T>::pop() {
	std::swap(heap_.front(), heap_.back());
	heap_.pop_back();
	down_heap();
}

template <typename T>
T heap<T>::top() const {
	return heap_.front();
}

} // namespace qap

//ifndef QP_HEAP__
#endif
