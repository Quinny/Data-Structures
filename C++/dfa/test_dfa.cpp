#include "dfa.h"
#include <iostream>

state_id q0(char c) {
    if (c == '1')
        return 0;
    if (c == '0')
        return 1;
    return bad_input;
}

state_id q1(char c) {
    if (c == '0')
        return 1;
    if (c == '1')
        return 0;
    return bad_input;
}

int main() {
    dfa<char> a;
    a.register_state(0, q0);
    a.register_state(1, q1, true);
    
    std::string s = "10010010x";
    std::cout << a.check(s) << std::endl;
    return 0;
}
