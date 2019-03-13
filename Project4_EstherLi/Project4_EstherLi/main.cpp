//#include "provided.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <cstdlib>
//using namespace std;
//
//// Change the string literal in this declaration to be the path to the
//// directory that contains the genome data files we provide, e.g.,
//// "Z:/CS32/Geenomics/data" or "/Users/fred/cs32/Geenomics/data"
//
//const string PROVIDED_DIR = "C:/Users/Esther/Desktop/CS_32/Project4_EstherLi/data";
//
//const string providedFiles[] = {
//	"Ferroplasma_acidarmanus.txt",
//	"Halobacterium_jilantaiense.txt",
//	"Halorubrum_chaoviator.txt",
//	"Halorubrum_californiense.txt",
//	"Halorientalis_regularis.txt",
//	"Halorientalis_persicus.txt",
//	"Ferroglobus_placidus.txt",
//	"Desulfurococcus_mucosus.txt"
//};
//
//void createNewLibrary(GenomeMatcher*& library)
//{
//	cout << "Enter minimum search length (3-100): ";
//	string line;
//	getline(cin, line);
//	int len = atoi(line.c_str());
//	if (len < 3 || len > 100)
//	{
//		cout << "Invalid prefix size." << endl;
//		return;
//	}
//	delete library;
//	library = new GenomeMatcher(len);
//}
//
//void addOneGenomeManually(GenomeMatcher* library)
//{
//	cout << "Enter name: ";
//	string name;
//	getline(cin, name);
//	if (name.empty())
//	{
//		cout << "Name must not be empty." << endl;
//		return;
//	}
//	cout << "Enter DNA sequence: ";
//	string sequence;
//	getline(cin, sequence);
//	if (sequence.empty())
//	{
//		cout << "Sequence must not be empty." << endl;
//		return;
//	}
//	if (sequence.find_first_not_of("ACGTNacgtn") != string::npos)
//	{
//		cout << "Invalid character in DNA sequence." << endl;
//		return;
//	}
//	for (char ch : sequence)
//		ch = toupper(ch);
//	library->addGenome(Genome(name, sequence));
//}
//
//bool loadFile(string filename, vector<Genome>& genomes)
//{
//	ifstream inputf(filename);
//	if (!inputf)
//	{
//		cout << "Cannot open file: " << filename << endl;
//		return false;
//	}
//	if (!Genome::load(inputf, genomes))
//	{
//		cout << "Improperly formatted file: " << filename << endl;
//		return false;
//	}
//	return true;
//}
//
//void loadOneDataFile(GenomeMatcher* library)
//{
//	string filename;
//	cout << "Enter file name: ";
//	getline(cin, filename);
//	if (filename.empty())
//	{
//		cout << "No file name entered." << endl;
//		return;
//	}
//	vector<Genome> genomes;
//	if (!loadFile(filename, genomes))
//		return;
//	for (const auto& g : genomes)
//		library->addGenome(g);
//	cout << "Successfully loaded " << genomes.size() << " genomes." << endl;
//}
//
//void loadProvidedFiles(GenomeMatcher* library)
//{
//	for (const string& f : providedFiles)
//	{
//		vector<Genome> genomes;
//		if (loadFile(PROVIDED_DIR + "/" + f, genomes))
//		{
//			for (const auto& g : genomes)
//				library->addGenome(g);
//			cout << "Loaded " << genomes.size() << " genomes from " << f << endl;
//		}
//	}
//}
//
//void findGenome(GenomeMatcher* library, bool exactMatch)
//{
//	if (exactMatch)
//		cout << "Enter DNA sequence for which to find exact matches: ";
//	else
//		cout << "Enter DNA sequence for which to find exact matches and SNiPs: ";
//	string sequence;
//	getline(cin, sequence);
//	int minLength = library->minimumSearchLength();
//	if (sequence.size() < minLength)
//	{
//		cout << "DNA sequence length must be at least " << minLength << endl;
//		return;
//	}
//	cout << "Enter minimum sequence match length: ";
//	string line;
//	getline(cin, line);
//	int minMatchLength = atoi(line.c_str());
//	if (minMatchLength > sequence.size())
//	{
//		cout << "Minimum match length must be at least the sequence length." << endl;
//		return;
//	}
//	vector<DNAMatch> matches;
//	if (!library->findGenomesWithThisDNA(sequence, minMatchLength, exactMatch, matches))
//	{
//		cout << "No ";
//		if (exactMatch)
//			cout << " matches";
//		else
//			cout << " matches or SNiPs";
//		cout << " of " << sequence << " were found." << endl;
//		return;
//	}
//	cout << matches.size();
//	if (exactMatch)
//		cout << " matches";
//	else
//		cout << " matches and/or SNiPs";
//	cout << " of " << sequence << " found:" << endl;
//	for (const auto& m : matches)
//		cout << "  length " << m.length << " position " << m.position << " in " << m.genomeName << endl;
//}
//
//bool getFindRelatedParams(double& pct, bool& exactMatchOnly)
//{
//	cout << "Enter match percentage threshold (0-100): ";
//	string line;
//	getline(cin, line);
//	pct = atof(line.c_str());
//	if (pct < 0 || pct > 100)
//	{
//		cout << "Percentage must be in the range 0 to 100." << endl;
//		return false;
//	}
//	cout << "Require (e)xact match or allow (S)NiPs (e or s): ";
//	getline(cin, line);
//	if (line.empty() || (line[0] != 'e' && line[0] != 's'))
//	{
//		cout << "Response must be e or s." << endl;
//		return false;
//	}
//	exactMatchOnly = (line[0] == 'e');
//	return true;
//}
//
//void findRelatedGenomesManual(GenomeMatcher* library)
//{
//	cout << "Enter DNA sequence: ";
//	string sequence;
//	getline(cin, sequence);
//	int minLength = library->minimumSearchLength();
//	if (sequence.size() < minLength)
//	{
//		cout << "DNA sequence length must be at least " << minLength << endl;
//		return;
//	}
//	double pctThreshold;
//	bool exactMatchOnly;
//	if (!getFindRelatedParams(pctThreshold, exactMatchOnly))
//		return;
//
//	vector<GenomeMatch> matches;
//	library->findRelatedGenomes(Genome("x", sequence), 2 * minLength, exactMatchOnly, pctThreshold, matches);
//	if (matches.empty())
//	{
//		cout << "    No related genomes were found" << endl;
//		return;
//	}
//	cout << "    " << matches.size() << " related genomes were found:" << endl;
//	cout.setf(ios::fixed);
//	cout.precision(2);
//	for (const auto& m : matches)
//		cout << " " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
//}
//
//void findRelatedGenomesFromFile(GenomeMatcher* library)
//{
//	string filename;
//	cout << "Enter name of file containing one or more genomes to find matches for: ";
//	getline(cin, filename);
//	if (filename.empty())
//	{
//		cout << "No file name entered." << endl;
//		return;
//	}
//	vector<Genome> genomes;
//	if (!loadFile(filename, genomes))
//		return;
//	double pctThreshold;
//	bool exactMatchOnly;
//	if (!getFindRelatedParams(pctThreshold, exactMatchOnly))
//		return;
//
//	int minLength = library->minimumSearchLength();
//	for (const auto& g : genomes)
//	{
//		vector<GenomeMatch> matches;
//		library->findRelatedGenomes(g, 2 * minLength, exactMatchOnly, pctThreshold, matches);
//		cout << "  For " << g.name() << endl;
//		if (matches.empty())
//		{
//			cout << "    No related genomes were found" << endl;
//			continue;
//		}
//		cout << "    " << matches.size() << " related genomes were found:" << endl;
//		cout.setf(ios::fixed);
//		cout.precision(2);
//		for (const auto& m : matches)
//			cout << "     " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
//	}
//}
//
//void showMenu()
//{
//	cout << "        Commands:" << endl;
//	cout << "         c - create new genome library      s - find matching SNiPs" << endl;
//	cout << "         a - add one genome manually        r - find related genomes (manual)" << endl;
//	cout << "         l - load one data file             f - find related genomes (file)" << endl;
//	cout << "         d - load all provided data files   ? - show this menu" << endl;
//	cout << "         e - find matches exactly           q - quit" << endl;
//}
//
//int main()
//{
//	const int defaultMinSearchLength = 10;
//
//	cout << "Welcome to the Gee-nomics test harness!" << endl;
//	cout << "The genome library is initially empty, with a default minSearchLength of " << defaultMinSearchLength << endl;
//	showMenu();
//
//	GenomeMatcher* library = new GenomeMatcher(defaultMinSearchLength);
//
//	for (;;)
//	{
//		cout << "Enter command: ";
//		string command;
//		if (!getline(cin, command))
//			break;
//		if (command.empty())
//			continue;
//		switch (tolower(command[0]))
//		{
//		default:
//			cout << "Invalid command " << command << endl;
//			break;
//		case 'q':
//			delete library;
//			return 0;
//		case '?':
//			showMenu();
//			break;
//		case 'c':
//			createNewLibrary(library);
//			break;
//		case 'a':
//			addOneGenomeManually(library);
//			break;
//		case 'l':
//			loadOneDataFile(library);
//			break;
//		case 'd':
//			loadProvidedFiles(library);
//			break;
//		case 'e':
//			findGenome(library, true);
//			break;
//		case 's':
//			findGenome(library, false);
//			break;
//		case 'r':
//			findRelatedGenomesManual(library);
//			break;
//		case 'f':
//			findRelatedGenomesFromFile(library);
//			break;
//		}
//	}
//}
//
//
//
//
//
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
	//t1.print();

	t1.insert("baaaa", 10);
	t1.insert("abaaa", 11);
	t1.insert("aabaa", 12);
	t1.insert("aaaba", 13);
	t1.insert("aaaab", 14);

	vector<int> result = t1.find("aaaaa", false);
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;

	cout << endl << "Passed all tests in test1()." << endl;
}

void test2() {
	Genome g1("dog", "GATTACA");
	cout << endl << g1.length() << endl;
	cout << g1.name() << endl;
	string frag = "";
	assert(g1.extract(4, -2, frag) == false && frag == "");
	assert(g1.extract(-4, 2, frag) == false && frag == "");
	assert(g1.extract(0, 10, frag) == false && frag == "");
	assert(g1.extract(0, 2, frag) == true && frag == "GA");
	assert(g1.extract(5, 2, frag) == true && frag == "CA");

	cout << endl << "Passed all tests in test2()." << endl;
}

void test3() {
	cout << endl;
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

	cout << endl << "Passed all tests in test3()." << endl;
}

void test4() {
	Genome g1("Genome 1", "ACTG");
	Genome g2("Genome 2", "TCGACT");
	Genome g3("Genome 3", "TCTCG");
	Genome g4("Genome 4", "AXAXCDE");
	GenomeMatcher gm(2); //minimumSearchLength is 3
	gm.addGenome(g1);
	gm.addGenome(g2);
	gm.addGenome(g3);
	gm.addGenome(g4);
	vector<FragmentInfo> result = gm.library()->find("AB", false);
	cout << result.size() << endl;
	for (int i = 0; i < result.size(); i++)
		cout << result[i].m_posInGenome << endl;

	cout << endl << "Passed all tests in test4()." << endl;

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

	cout << endl << "Passed all tests in test5()." << endl;
}

void test6() {
	Genome g1("Genome 1", "AAAXBBBXCCCXDDDXEEEE");
	Genome g2("Genome 2", "XXAAAAXCCCCXEEEEX");
	Genome g3("Genome 3", "AAAAAAAAAAAAAAAA");
	Genome g4("Genome 4", "XABBXBBC");
	Genome g5("FRAGMENT", "AAAABBBBCCCCDDDDEEEE");
	GenomeMatcher gm(2);
	vector<GenomeMatch> matches;
	vector<DNAMatch> matches2;
	gm.addGenome(g1);
	gm.addGenome(g2);
	gm.addGenome(g3);
	gm.addGenome(g4);
	gm.findRelatedGenomes(g5, 3, true, 1, matches);
	//gm.findGenomesWithThisDNA("ABCDABCDABCDABCD", 4, true, matches2);
	for (int i = 0; i < matches.size(); i++)
		cout << endl << matches[i].genomeName << ", " << matches[i].percentMatch << "%" << endl;

	cout << endl << "Passed all tests in test6()." << endl;
}

int main() {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	cout << endl <<  "Passed all tests!" << endl;
}