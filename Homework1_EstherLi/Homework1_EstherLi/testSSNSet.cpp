#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	SSNSet s;
	assert(s.size() == 0);
	ItemType x = 123456789;
	assert(s.add(x));
	assert(!(s.add(x))); // s unchanged by get failure
	assert(s.add(223456789));
	assert(s.size() == 2);
	assert(s.add(11111111));
	assert(s.add(22222222));
	assert(s.size() == 4);
	s.print();
	cout << "Passed all tests" << endl;
}