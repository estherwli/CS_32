#include "Trie.h"
#include <iostream>
using namespace std;


int main() {
	Trie<int> t1;
	t1.insert("a", 1);
	t1.insert("b", 2);
	t1.insert("abc", 2);
	t1.insert("abd", 2);
	t1.insert("bc", 3);
	t1.print();
	cout << "Passed all tests." << endl;
}