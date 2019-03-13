#include "Trie.h"
#include "provided.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
using namespace std;

void test1() {
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
	//t1.print();

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

void test2() {
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

void test4() {
	Genome g1("Genome 1", "ACTG");
	Genome g2("Genome 2", "TCGACT");
	Genome g3("Genome 3", "TCTCG");
	Genome g4("Genome 4", "AXAXCDE");
	GenomeMatcher gm(2); //minimumSearchLength is 3
	//gm.addGenome(g1);
	//gm.addGenome(g2);
	//gm.addGenome(g3);
	gm.addGenome(g4);
	vector<FragmentInfo> result = gm.library()->find("AB", false);
	cout << result.size() << endl;
	for (int i = 0; i < result.size(); i++)
		cout << result[i].m_posInGenome << endl;

}

void test5() {
	Genome g1("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
	Genome g2("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
	Genome g3("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");
	Genome g4("Genome 4", "ABAXCDE"); //("GAATAC", 2, false, matches) should return pos 2, length 4
	Genome g5("Genome 5", "ABABXDE");
	Genome g6("Genome 6", "ABABCXE");
	Genome g7("Genome 7", "ABABCDX");
	Genome g8("Genome 8", "ABXBCDE");
	Genome g9("Genome 9", "AXAYCDE");
	GenomeMatcher gm(4); //minimumSearchLength is 4
	GenomeMatcher myGM(2); //minimumSearchLength is 2
	gm.addGenome(g1);
	gm.addGenome(g2);
	gm.addGenome(g3);
	myGM.addGenome(g4);
	myGM.addGenome(g5);
	myGM.addGenome(g6);
	myGM.addGenome(g7);
	myGM.addGenome(g8);
	myGM.addGenome(g9);

	vector<DNAMatch> matches;
	assert(myGM.findGenomesWithThisDNA("AB", 2, true, matches) == true && matches.size() == 5);
	matches.clear();
	assert(myGM.findGenomesWithThisDNA("AB", 2, false, matches) == true && matches.size() == 6);
	matches.clear();
	assert(myGM.findGenomesWithThisDNA("ABC", 2, true, matches) == true && matches.size() == 5);
	matches.clear();
	assert(myGM.findGenomesWithThisDNA("ABC", 3, true, matches) == true && matches.size() == 2);
	matches.clear();
	assert(myGM.findGenomesWithThisDNA("ABC", 3, false, matches) == true && matches.size() == 6);
	matches.clear();
	assert(myGM.findGenomesWithThisDNA("ABCD", 4, true, matches) == true && matches.size() == 1);
	matches.clear();

	assert(gm.findGenomesWithThisDNA("GAAG", 4, true, matches) == true && matches.size() == 3);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAATAC", 4, true, matches) == true && matches.size() == 2);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAATAC", 6, true, matches) == false && matches.size() == 0);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAATAC", 6, false, matches) == true && matches.size() == 2);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GTATAT", 6, false, matches) == true && matches.size() == 2);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAATACG", 6, false, matches) == true && matches.size() == 2);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches) == true && matches.size() == 3);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches) == true && matches.size() == 2);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches) == true && matches.size() == 1);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches) == true && matches.size() == 1);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAAG", 3, true, matches) == false && matches.size() == 0);
	matches.clear();
	assert(gm.findGenomesWithThisDNA("GAAG", 5, true, matches) == false && matches.size() == 0);

	//bool result;
	//result = myGM.findGenomesWithThisDNA("AB", 2, false, matches);
	//if (result == true)
	//	cout << "Result: true" << endl;
	//else
	//	cout << "Result: false" << endl;
	//for (int i = 0; i < matches.size(); i++) {
	//	cout << matches[i].genomeName << endl;
	//	cout << "length: " << matches[i].length << endl;
	//	cout << "position: " << matches[i].position << endl;
	//	cout << "" << endl;
	//}

}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	cout << "Passed all tests!" << endl;
}