#include <iostream>
#include "Stack.h"

using namespace std;

int main(){
	Stack<int> s;

	s.push(5);
	s.push(6);

	int x=s.pop();
	s.pop();
	s.push(5);
	cout<<(s.empty())<<endl;
	return 0;
}