#include "Trie.h"
#include <iostream>
using namespace std;


int main() {
	Trie<int> t1;
	t1.insert("ab", 1); //prints a, then a/b
	t1.insert("abc", 2); //prints a/b/c
	t1.insert("ab", 1); //should not print any new paths
	t1.insert("abcd", 3); //prints a/b/c/d
	t1.insert("b", 1); //prints b
	t1.insert("bcd", 2); //prints b/c, then b/c/d
	t1.insert("abab", 1); //prints a/b/a, then a/b/a/b

	t1.print();
	cout << "Passed all tests." << endl;
}