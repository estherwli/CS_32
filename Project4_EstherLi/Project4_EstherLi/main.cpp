#include "Trie.h"
#include "provided.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
using namespace std;

void test1() {
	Trie<int> t1;
	t1.insert("ab", 1); //prints a, then a/b
	t1.insert("abc", 2); //prints a/b/c
	t1.insert("ab", 3); //should not print any new paths
	t1.insert("abcd", 4); //prints a/b/c/d
	t1.insert("b", 5); //prints b
	t1.insert("bcd", 6); //prints b/c, then b/c/d
	t1.insert("abab", 7); //prints a/b/a, then a/b/a/b
	t1.insert("abcabc", 8);
	t1.insert("abcab", 9);
	t1.print();

	t1.insert("baaaa", 10);
	t1.insert("abaaa", 11);
	t1.insert("aabaa", 12);
	t1.insert("aaaba", 13);
	t1.insert("aaaab", 14);

	vector<int> result = t1.find("aaaaa", false);
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;

	cout << "Passed all tests in test1()." << endl;
}

void test2(){
	Genome g1("dog", "GATTACA");
	cout << g1.length() << endl;
	cout << g1.name() << endl;
	string frag = "";
	assert(g1.extract(4, -2, frag) == false && frag == "");
	assert(g1.extract(-4, 2, frag) == false && frag == "");
	assert(g1.extract(0, 10, frag) == false && frag == "");
	assert(g1.extract(0, 2, frag) == true && frag == "GA");
	assert(g1.extract(5, 2, frag) == true && frag == "CA");

	cout << "Passed all tests in test2()." << endl;
}

void test3() {
	string filename = "C:/Users/Esther/Desktop/CS_32/Project4_EstherLi/data/Desulfurococcus_mucosus.txt";
	ifstream infile(filename);
	if (!infile) {
		cout << "Cannot	open " << filename << endl;
		return;
	}
	
	string filename2 = "C:/Users/Esther/Desktop/CS_32/Project4_EstherLi/data/Ferroglobus_placidus.txt";
	ifstream infile2(filename2);
	if (!infile2) {
		cout << "Cannot	open " << filename2 << endl;
		return;
	}

	vector<Genome> vg;
	bool success = Genome::load(infile, vg);
	bool success2 = Genome::load(infile2, vg);
	if (success && success2) {
		cout << "Loaded " << vg.size() << " genome(s) successfully:" << endl;
		for (int k = 0; k != vg.size(); k++)
			cout << vg[k].name() << endl;
	}
	else
		cout << "Error loading genome data" << endl;
	
}

int main() {
	//test1();
	//test2();
	test3();
}