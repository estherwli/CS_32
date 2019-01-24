#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet() 
	: m_set() {
}

bool SSNSet::add(unsigned long ssn) {
	return m_set.insert(ssn);
}

int SSNSet::size() const {
	return m_set.size();
}

void SSNSet::print() const {
	ItemType temp;
	for (int i = 0; i < m_set.size(); i++) {
		m_set.get(i, temp);
		cout << temp << endl;
	}
}

