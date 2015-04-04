#include "bit_vector.hpp"
#include <iostream>

int main(){
	bit_vector<sizeof(long) * 8> b;
	b.set();
	b.flip(0);
	long check = b.to_integral<long>();
	std::cout << check << std::endl;
	std::cout << b.to_string() << std::endl;
	std::cout << b.size() << std::endl;
	return 0;
}
