#ifndef _QP_DFA_H_
#define _QP_DFA_H_

#include <map>
#include <functional>
#include <set>

using state_id = std::size_t;
const state_id bad_input = -1;

template <typename T>
class dfa {

public:
    std::map<T, std::function<state_id(T)>> transition_;
    std::set<state_id> final_states_;

    void register_state(state_id i, std::function<state_id(T)> f,
            bool is_final = false) {
        transition_[i] = f;
        if (is_final)
            final_states_.insert(i);
    }

    template <typename Container>
    bool check(Container c) {
        state_id cur = 0;
        for (auto i: c) {
            cur = transition_[cur](i);
            if (cur == bad_input)
                return false;
        }
        return final_states_.find(cur) != final_states_.end();
    }
};

#endif
