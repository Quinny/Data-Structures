#include <functional>

template <typename T>
class optional {
private:
    T value_;
    bool has_value_;

public:
    optional(): has_value_(false) {};
    optional(const T& v): value_(v), has_value_(true) {};

    bool is_present() const {
        return has_value_;
    }

    T or_else(const T& v) {
        if (has_value_)
            return value_;
        return v;
    }

    void if_present(std::function<void(T)> f) {
        if (has_value_)
            f(value_);
    }
};
