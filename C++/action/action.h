#ifndef _QP_action_H_
#define _QP_action_H_

#include <vector>

namespace qap {

template <typename... In>
class action {

public:
    using value_type = void (*)(In...);

private:
    std::vector<value_type> functions_;

public:
    action () {};

    action (const value_type& f) {
        functions_.push_back(f);
    }

    action (value_type&& f) {
        functions_.emplace_back(std::move(f));
    }

    typename std::vector<value_type>::iterator begin() const {
        return functions_.begin();
    }

    typename std::vector<value_type>::iterator end() const {
        return functions_.end();
    }

    void operator += (value_type f) {
        functions_.push_back(f);
    }

    void operator += (action<In...> f) {
        for (auto&& i : f.functions_)
            functions_.push_back(i);
    }

    void operator ()(In... args) const {
        for (auto&& i : functions_)
            i(args...);
    }

}; // action class

} // qap namespace

#endif // include guard
