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

    T get() const {
        return value_;
    }

    template <typename U>
    optional<U> map(std::function<U(T)> f) {
        if (has_value_)
            return optional<U>(f(value_));
        return optional<U>();
    }

    T or_else(const T& v) const {
        if (has_value_)
            return value_;
        return v;
    }

    void if_present(std::function<void(T)> f) const {
        if (has_value_)
            f(value_);
    }

    optional<T> filter(std::function<bool(T)> p) const {
        if (p(value_))
            return optional(value_);
        return optional();
    }
};
