//#include "newSet.h"
//#include <iostream>
//using namespace std;
//
//Set::Set() {
//	m_size = 0;
//	m_max = DEFAULT_MAX_ITEMS;
//	m_items = new ItemType[m_max];
//}
//
//Set::Set(int value) {
//	if (value < 0)
//		value = DEFAULT_MAX_ITEMS;
//	m_size = 0;
//	m_max = value;
//	m_items = new ItemType[m_max];
//}
//
//Set::Set(const Set& other) {
//	m_size = other.m_size;
//	m_max = other.m_max;
//	m_items = new ItemType[m_max];
//	for (int i = 0; i < m_size; i++)
//		m_items[i] = other.m_items[i];
//}
//
//Set& Set::operator=(const Set& other) {
//	if (&other == this)
//		return *this;
//	delete[] m_items;
//	m_size = other.m_size;
//	m_max = other.m_max;
//	m_items = new ItemType[m_max];
//	for (int i = 0; i < m_max; i++)
//		m_items[i] = other.m_items[i];
//	return *this;
//}
//
//Set::~Set() {
//	delete[] m_items;
//}
//
//bool Set::empty() const {
//	if (m_size == 0)
//		return true;
//	else
//		return false;
//}
//
//int Set::size() const {
//	return m_size;
//}
//
//bool Set::insert(const ItemType& value) {
//	if (m_size + 1 > m_max)
//		return false;
//	for (int i = 0; i < m_size; i++) {
//		if (value == m_items[i])
//			return false;
//	}
//	m_items[m_size] = value;
//	m_size++;
//	return true;
//}
//
//bool Set::erase(const ItemType& value) {
//	for (int i = 0; i < size(); i++) {
//		if (value == m_items[i])
//		{
//			for (int j = i; j < size() - 1; j++)
//				m_items[j] = m_items[j + 1];
//		}
//		else
//			return false;
//	}
//	m_size--;
//	return true;
//}
//
//bool Set::contains(const ItemType& value) const {
//	for (int i = 0; i < size(); i++) {
//		if (value == m_items[i])
//			return true;
//	}
//	return false;
//}
//
//bool Set::get(int i, ItemType& value) const {
//	if (!(i < size() && i >= 0))
//		return false;
//
//	for (int j = 0; j < size(); j++) {
//		int count = 0;
//		for (int k = 0; k < size(); k++) {
//			if (m_items[j] > m_items[k])
//				count++; //records how many elements m_items[j] is greater than
//		}
//		if (count == i) {
//			value = m_items[j];
//			break;
//		}
//	}
//	return true;
//}
//
//void Set::swap(Set& other) {
//	int tempSize = this->m_size;
//	this->m_size = other.m_size;
//	other.m_size = tempSize;
//
//	int tempMax = this->m_max;
//	this->m_max = other.m_max;
//	other.m_max = tempMax;
//
//	ItemType* tempItem = m_items;
//	m_items = other.m_items;
//	other.m_items = tempItem;
//}