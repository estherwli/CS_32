#include "provided.h"
#include "trie.h"
#include <string>
#include <vector>
#include <map>
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
	/*bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
*/

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
	map<int, int[]> compareResults; //int[] = {length, pos}; used to later compare matches from the same Genome
	string match;
	int h, f;
	int count = 0;
	results = m_library.find(fragment, exactMatchOnly); //stores all matches that met the minimumSearchLength requirement

	for (h = 0; h < results.size(); h++) { //O(h) where h is number of hits 
		const Genome* curGenome = &m_genomes[results[h].posInLibrary()];
		curGenome->extract(results[h].posInGenome(), fragment.size(), match); 
		for (f = 0; f < fragment.size(); f++) { //O(f) where f is the length of fragment
			if (exactMatchOnly && match[f] != fragment[f]) 
				break;
			else if (!exactMatchOnly && match[f] != fragment[f]) //there can be 1 mismatch; after that, treat it like exactMatchOnly
				exactMatchOnly = true; 
		}
		int pos = results[h].posInLibrary();
		if (compareResults.find(pos))
			DNAMatch newMatch;
			newMatch.genomeName = m_genomes[pos].name();
			newMatch.length = f;
			newMatch.position = results[h].posInGenome();
			compareResults[pos] = &newMatch;
		}
	}
	for (h = 0; h < compareResults.size(); h++) {
		if (compareResults[h] != nullptr && compareResults[h]->length >= minimumLength) {
			matches.push_back(*compareResults[h]);
			count++;
		}	
	}
	if (count == 0) //nothing was added to matches
		return false;
	return true;
}
//
//bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
//{
//	return false;  // This compiles, but may not be correct
//}

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

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

//bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
//{
//	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
//}
