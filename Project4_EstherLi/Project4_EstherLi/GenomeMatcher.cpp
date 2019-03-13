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

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const {
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
			if (exactMatchOnly && match[f] != fragment[f])
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

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	if (fragmentMatchLength < minimumSearchLength())
		return false;
	string fragment;
	vector<DNAMatch> matches;
	vector<DNAMatch>::iterator itVec;
	unordered_map<string, double> tally;
	unordered_map<string, double>::iterator itMap;
	int length = query.length() - (query.length() % fragmentMatchLength);
	for (int i = 0; i < length; i += fragmentMatchLength) {
		query.extract(i, fragmentMatchLength, fragment);
		findGenomesWithThisDNA(fragment, fragmentMatchLength, exactMatchOnly, matches);
	}
	itVec = matches.begin();
	while (itVec != matches.end()) {
		itMap = tally.find(itVec->genomeName);
		if (itMap == tally.end())
			tally[itVec->genomeName] = 1.0 / length;
		else
			tally[itVec->genomeName] += 1.0 / length;
	}
	



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
