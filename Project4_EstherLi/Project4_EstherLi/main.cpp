#include "Trie.h"
#include <iostream>
#include<vector>
using namespace std;


int main() {
	Trie<int> t1;
	//t1.insert("ab", 1); //prints a, then a/b
	//t1.insert("abc", 2); //prints a/b/c
	//t1.insert("ab", 3); //should not print any new paths
	//t1.insert("abcd", 4); //prints a/b/c/d
	//t1.insert("b", 5); //prints b
	//t1.insert("bcd", 6); //prints b/c, then b/c/d
	//t1.insert("abab", 7); //prints a/b/a, then a/b/a/b
	//t1.insert("abcabc", 8);
	//t1.insert("abcab", 9);
	t1.insert("baaaa", 10);
	t1.insert("abaaa", 11);
	t1.insert("aabaa", 12);
	t1.insert("aaaba", 13);
	t1.insert("aaaab", 14);

	vector<int> result = t1.find("aaaaa", false);
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;

	cout << "Passed all tests." << endl;
}