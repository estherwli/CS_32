#include "Set.h"
#include <iostream>
using namespace std;

Set::Set() {
	head = nullptr; //empty set
	m_size = 0;
}

Set::~Set() {
	Node *p = head;
	while (p != nullptr) {
		Node *n = p->next;
		delete p;
		p = n;
	}
	m_size = 0;
}

Set::Set(const Set& other) {

}

Set& Set::operator=(const Set& other) {

}

bool Set::empty() const {
	if (head == nullptr)
		return true;
	else
		return false;
}

int Set::size() const {
	return m_size;
}

bool Set::insert(const ItemType& value) {
	m_size++;
}

bool Set::erase(const ItemType& value) {
	if (head == nullptr)
		return false;
	//case 1: deleting top node
	if (head->data == value)
	
	
	m_size--;
}

bool Set::contains(const ItemType& value) const {
	if (head == nullptr)
		return false;
}

bool Set::get(int pos, ItemType& value) const {
	if (head == nullptr)
		return false;
}

void Set::swap(Set& other) {

}