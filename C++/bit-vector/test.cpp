#include "bit_vector.hpp"
#include <iostream>
#include <cassert>

int main(){
    qap::bit_vector<sizeof(long) * 8> b;
	b.set();
	b.flip(0);
	long check = b.to_integral<long>();
	std::cout << check << std::endl;
	std::cout << b << std::endl;
    assert(b.to_integral<long>() == LONG_MAX);
    qap::bit_vector<sizeof(int) * 8> b2;
    b2.set();
    b2.flip(0);
    std::cout << b2 << std::endl;
    assert(b2.to_integral<int>() == INT_MAX);
    return 0;
}
