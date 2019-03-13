#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class GenomeMatcherImpl
{
public:
	GenomeMatcherImpl(int minSearchLength);
	void addGenome(const Genome& genome);
	int minimumSearchLength() const;
	bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
	bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;


	//REMOVE BEFORE TURNING IT IN LMAO


	Trie<FragmentInfo>* library() { return &m_library; }
	/////////////////////////////////////////////////////////////


private:
	struct greater {
		bool operator()(const pair<string, double>& a, const pair<string, double>& b) const {
			if (a.second > b.second || a.second == b.second && a.first <= b.first)
				return true;
			if (a.second < b.second || a.second == b.second && a.first > b.first)
				return false;
		}
	};
	int partition(vector<pair<string, double>> vec, int low, int high);
	void quickSort(vector<pair<string, double>> vec, int first, int last);
	int m_minSearchLength;
	vector<Genome> m_genomes;
	Trie<FragmentInfo> m_library;
};


GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	m_minSearchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	int posInLibrary = m_genomes.size();
	m_genomes.push_back(genome);
	for (int i = 0; i < genome.length() - minimumSearchLength() + 1; i++) {
		string fragment;
		FragmentInfo info(posInLibrary, i);
		genome.extract(i, minimumSearchLength(), fragment);
		m_library.insert(fragment, info);
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return m_minSearchLength;
}

int GenomeMatcherImpl::partition(vector<pair<string, double>> vec, int low, int high) {
	int pivotIndex = low;
	pair<string, double> pivot = vec[low];
	do {
		while (low <= high && ((vec[low].second) > pivot.second ||
			((vec[low].second) == pivot.second) && (vec[low].first <= pivot.first)))
			low++;
		while (vec[high].second < pivot.second ||
			((vec[low].second) == pivot.second) && (vec[low].first > pivot.first))
			high--;
		if (low < high)
			swap(vec[low], vec[high]);
	} while (low < high);
	swap(vec[pivotIndex], vec[high]);
	pivotIndex = high;
	return pivotIndex;
}

void GenomeMatcherImpl::quickSort(vector<pair<string, double>> vec, int first, int last) {
	if (last - first >= 1) {
		int pivotIndex = partition(vec, first, last);
		quickSort(vec, first, pivotIndex - 1);
		quickSort(vec, pivotIndex + 1, last);
	}
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength,
	bool exactMatchOnly, vector<DNAMatch>& matches) const {
	if (fragment.size() < minimumLength || minimumLength < minimumSearchLength())
		return false;
	vector<FragmentInfo> results;
	unordered_map<int, DNAMatch> compare; //used to later compare matches from the same Genome
	unordered_map<int, DNAMatch>::iterator it;
	string match;
	int h, f, posInLibrary, posInGenome;
	int count = 0;
	bool originalReq = exactMatchOnly;
	results = m_library.find(fragment.substr(0, minimumSearchLength()), exactMatchOnly); //stores all matches that met the minimumSearchLength requirement

	for (h = 0; h < results.size(); h++) { //O(h) where h is number of hits 
		exactMatchOnly = originalReq; //ensures previous iteration's changes does not affect the original exactMatchOnly requirement
		posInLibrary = results[h].posInLibrary();
		posInGenome = results[h].posInGenome();
		(m_genomes[posInLibrary]).extract(posInGenome, minimumSearchLength(), match);
		if (fragment.substr(0, minimumSearchLength()) != match) //the prefix already has 1 mismatch, so treat it like exactMatchOnly from now on
			exactMatchOnly = true;
		for (f = minimumSearchLength(); f < fragment.size(); f++) { //O(f) where f is the length of fragment
			(m_genomes[posInLibrary]).extract(posInGenome, f + 1, match); //extract remaining chars 1 at a time
			if (exactMatchOnly && match.size() > f && match[f] != fragment[f])
				break;
			else if (!exactMatchOnly && match[f] != fragment[f]) //there can be 1 mismatch; treat it like exactMatchOnly from now on
				exactMatchOnly = true;
		}
		if (f >= minimumLength) {
			it = compare.find(posInLibrary);
			if (it == compare.end()) { //this is the first match of its genome
				DNAMatch bestMatch;
				bestMatch.genomeName = m_genomes[posInLibrary].name();
				bestMatch.length = f;
				bestMatch.position = posInGenome;
				compare[posInLibrary] = bestMatch;
			}
			else if ((it->second).length < f) { //this match is longer than the previous longest match of its genome
				(it->second).length = f;
				(it->second).position = posInGenome;
			}
		}
	}
	it = compare.begin();
	while (it != compare.end()) { //O(h), where h is number of hits
		matches.push_back(it->second);
		count++;
		it++;
	}
	if (count == 0) //nothing was pushed to matches
		return false;
	return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly,
	double matchPercentThreshold, vector<GenomeMatch>& results) const {
	if (fragmentMatchLength < minimumSearchLength())
		return false;
	string fragment;
	vector<pair<string, double>> toSort;
	vector<pair<string, double>>::iterator itSort;
	vector<DNAMatch> matches;
	vector<DNAMatch>::iterator itVec;
	unordered_map<string, double> tally;
	unordered_map<string, double>::iterator itMap;
	int count = 0;
	int length = query.length() - (query.length() % fragmentMatchLength);
	int numFragments = length / fragmentMatchLength;
	cout.setf(ios::fixed);
	cout.precision(2);

	for (int i = 0; i < length; i += fragmentMatchLength) {
		query.extract(i, fragmentMatchLength, fragment);
		findGenomesWithThisDNA(fragment, fragmentMatchLength, exactMatchOnly, matches);
	}
	for (itVec = matches.begin(); itVec != matches.end(); itVec++) { //use a map to keep track of the match count of each genome
		//cout << "# of hits: " << matches.size() << endl;
		//cout << itVec->genomeName << ", Pos: " << itVec->position << ", Length: " << itVec->length << endl;
		itMap = tally.find(itVec->genomeName);
		if (itMap == tally.end())
			tally[itVec->genomeName] = 1.0;
		else
			tally[itVec->genomeName] += 1.0;
	}
	for (itMap = tally.begin(); itMap != tally.end(); itMap++) //move tallied genomes from map to vector to sort
		toSort.push_back(*itMap);
	sort(toSort.begin(), toSort.end(), greater());
	for (itSort = toSort.begin(); itSort != toSort.end(); itSort++) {
		GenomeMatch gMatch;
		gMatch.genomeName = itSort->first;
		gMatch.percentMatch = (itSort->second) * 100.0 / numFragments;
		results.push_back(gMatch);
		count++;
	}
	if (count == 0)
		return false;
	return true;	
}


//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
	m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
	delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
	m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
	return m_impl->minimumSearchLength();
}


//REMOVE THIS BEFORE TURNING IT IN!!!!!!!!!!!!!!!
Trie<FragmentInfo>* GenomeMatcher::library() {
	return m_impl->library();
}
////////////////////////////////////////////////////////////

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
