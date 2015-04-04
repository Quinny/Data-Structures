#include <iostream>
#include "Heap.h"

using namespace std;

int main(void){

	Heap<int> h;

	h.insert(7);
	h.insert(8);
	h.insert(9);
	h.insert(5);

	cout<<(h.pop())<<endl;

	cout<<(h.empty())<<endl;


	h.print();	

	return 0;
}