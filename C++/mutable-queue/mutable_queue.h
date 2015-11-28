#include <set>

namespace qap {

template <typename T>
struct mq_node {
    T key;
    int priority;

    mq_node(const std::pair<T, int>& p) {
        key = p.first;
        priority = p.second;
    }

    mq_node(const T& k) {
        key = k;
    }

    bool operator == (const mq_node& n) const {
        return key == n.key;
    }

    bool operator < (const mq_node& n) const {
        return priority < n.priority;
    }

    void operator = (const mq_node& n) {
        key = n.key;
        priority = n.priority;
    }
};

template <typename T>
class mutable_queue {
private:
    std::set<mq_node<T>> q_;

public:
    void insert(const std::pair<T, int>& p) {
        q_.insert(p);
    }

    void update(const std::pair<T, int>& p) {
        q_.erase(p.first);
        q_.insert(p);
    }

    mq_node<T> peek() {
        return *(q_.begin());
    }

    mq_node<T> pop() {
       auto cp = peek();
       q_.erase(q_.begin());
       return cp;
    }

    bool empty() {
        return q_.empty();
    }
};

}
