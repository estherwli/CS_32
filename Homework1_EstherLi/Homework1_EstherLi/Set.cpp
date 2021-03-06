#include "Set.h"
#include <iostream>
using namespace std;

Set::Set() {
	m_size = 0;
}

bool Set::empty() const {
	if (m_size == 0)
		return true;
	else
		return false;
}

int Set::size() const {
	return m_size;
}

bool Set::insert(const ItemType& value) {
	if (m_size >= DEFAULT_MAX_ITEMS)
		return false;
	for (int i = 0; i < size(); i++) {
		if (value == m_items[i])
			return false;
	}
	m_items[m_size] = value;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value) {
	for (int i = 0; i < size(); i++) {
		if (value == m_items[i])
		{
			for (int j = i; j < size() - 1; j++)
				m_items[j] = m_items[j + 1];
			m_size--;
		}
	}
	return false;
}

bool Set::contains(const ItemType& value) const {
	for (int i = 0; i < size(); i++) {
		if (value == m_items[i])
			return true;
	}
	return false;
}

bool Set::get(int i, ItemType& value) const {
	if (!(i < size() && i >= 0))
		return false;

	for (int j = 0; j < size(); j++) {
		int count = 0;
		for (int k = 0; k < size(); k++) {
			if (m_items[j] > m_items[k])
				count++; //records how many elements m_items[j] is greater than
		}
		if (count == i) {
			value = m_items[j];
			return true;
		}
	}
	return false;
}

void Set::swap(Set& other) {
	int tempSize = this->m_size;
	this->m_size = other.m_size;
	other.m_size = tempSize;

	ItemType tempItem;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		tempItem = this->m_items[i];
		m_items[i] = other.m_items[i];
		other.m_items[i] = tempItem;
	}
}
