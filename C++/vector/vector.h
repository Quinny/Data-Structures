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
        

        void push_back(T x);

        T* begin() { return data_; }
        T* end() { return data_ + size_; }
        
        std::size_t size() const { return size_; }
 
        T& operator[](std::size_t i)  { return data_[i]; }
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
#endif // include guard
