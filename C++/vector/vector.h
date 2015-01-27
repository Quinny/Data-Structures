#ifndef QP_VECTOR_H
#define QP_VECTOR_H

#include <cstring>
#include <memory>

template <typename T>
class vector {
    private:
        std::size_t max_size_, size_;
        T* data_;
        void resize();
    public:
        // Constructors and destructor
        vector() : max_size_{10}, size_{0} {
            data_ = new T[max_size_];
        }
        vector(vector<T>& v) : size_{v.size()}, max_size_{v.size()} {
            data_ = new T[v.size()];
            std::copy(v.begin(), v.end(), data_);
        }
        vector(std::initializer_list<T> d) : size_{d.size()}, max_size_{d.size()} {
            data_ = new T[d.size()];
            std::copy(d.begin(), d.end(), data_);
        }
        ~vector() {
            delete[] data_;
        }
        
        // Adding/deleting
        void push_back(T x);
        template <typename iter>
        void assign(iter first, iter last);
        void assign(std::size_t n, const T& v);

        // Iterators
        T* begin() { return data_; }
        T* end() { return data_ + size_; }
        T& front() { return data_[0]; }
        T& back() { return data_[size_ - 1]; }

        // Info functions
        std::size_t size() const { return size_; }
        std::size_t max_size() const { return max_size_; }
        bool empty() const { return size_ == 0; }
        
        // Memory functions
        void resize(std::size_t n);
        void shrink_to_fit();
        void reserve(std::size_t n);

        // Operators
        T& operator[](std::size_t i)  { return data_[i]; }
        T const& operator[](std::size_t i) const { return data_[i]; }
        void operator=(vector<T> v);
};

template <typename T>
void vector<T>::resize() {
    max_size_ *= 2;
    T* tmp = new T[max_size_];
    std::copy(data_, data_ + size_, tmp);
    delete[] data_;
    data_ = tmp;
}

template <typename T>
void vector<T>::push_back(T x) {
    if(size_ >= max_size_)
        resize();
    *(data_ + size_++) = x;
}

template <typename T>
void vector<T>::operator=(vector<T> v) {
    size_ = v.size();
    max_size_ = v.size();
    delete[] data_;
    data_ = new T[max_size_];
    std::copy(v.begin(), v.end(), data_);
}

template <typename T>
void vector<T>::resize(std::size_t n){
    if(n == max_size_) return;
    T* tmp = new T[n];
    if(size_ > n){
        std::copy(data_, data_ + n, tmp);
        size_ = n;
    }
    else
        std::copy(data_, data_ + size_, tmp);
    delete[] data_;
    max_size_ = n; 
    data_ = tmp;
}

template <typename T>
void vector<T>::shrink_to_fit(){
    if(size_ == max_size_) return;
    T* tmp = new T[size_];
    std::copy(data_, data_ + size_, tmp);
    delete[] data_;
    data_ = tmp;
    max_size_ = size_;
}

template <typename T>
void vector<T>::reserve(std::size_t n){
    if(n > max_size_)
        resize(n);
}

template <typename T>
template <typename iter>
void vector<T>::assign(iter first, iter last){
    size_t n = last - first;
    resize(n);
    for(std::size_t i = 0; i < n; i++)
        data_[i] = *(first++);
    size_ = n;
}

template <typename T>
void vector<T>::assign(std::size_t n, const T& v){
    resize(n);
    for(std::size_t i = 0; i < n; i++)
        data_[i] = v;
    size_ = n;
}
#endif // include guard
