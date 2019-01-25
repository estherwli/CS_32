#include "Set.h"
#include <iostream>
using namespace std;

//constructor
Set::Set() {
	head = nullptr; //empty set
	tail = nullptr;
	m_size = 0;
}

//destructor
Set::~Set() {
	Node *p = head;
	while (p != nullptr) {
		Node *n = p->next;
		delete p;
		p = n;
	}
	m_size = 0;
}

//copy constructor
Set::Set(const Set& other) {
	m_size = other.m_size;
	head == nullptr;
	tail == nullptr;
	for (int i = 0; i < m_size; i++) { 
		ItemType temp;
		other.get(i, temp); 
		insert(temp); //copies each node to new set
	}
}

//assignment operator
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
	//allocate new node
	Node *latest = new Node;
	latest->data = value;

	//case 1: empty set
	if (head == nullptr) {
		head = latest;
		head->last = nullptr;
		head->next = tail;
	}

	//case 2: set has >= 1 nodes
	else {
		tail->next = latest;
		latest->next = nullptr;
	}
	m_size++;
}

bool Set::erase(const ItemType& value) {
	if (head == nullptr)
		return false;

	//case 1: deleting top node
	if (head->data == value) {
		Node *killMe = head;
		head = killMe->next;
		delete killMe;
	}

	//case 2: deleting interior node or tail node
	Node *p = head;
	while (p != nullptr) {
		if (p->next == nullptr)
			return false;
		if (p->next != nullptr && p->next->data == value) {
			Node *killMe = p->next;
			p->next = killMe->next;
			delete killMe;
		}
		p = p->next;
	}
	m_size--;
	return true;
}

bool Set::contains(const ItemType& value) const {
	if (head == nullptr) //empty set
		return false;
	Node *p = head;
	while (p != nullptr) { //traverse through entire set
		if (p->data == value)
			return true;
		p = p->next;
	}
	return false;
}

bool Set::get(int pos, ItemType& value) const {
	//invalid conditions
	if (head == nullptr || pos < 0 || pos >= m_size)
		return false;
	
	Node *p = head;
	int count = 0;
	while (p != nullptr) { //traverse through entire set
		Node *temp = head;
		while (temp != nullptr) {
			if (p > temp)
				count++; //records how many values p is strictly greater than
			if (count == pos) {
				value = p->data;
				return true;
			}
			temp = temp->next;
		}
		p = p->next;
	}
	return false;
}

	void Set::swap(Set& other) {
		//swaps head
		Node *tempHead = head;
		head = other.head;
		other.head = tempHead;

		//swaps tail
		Node *tempTail = tail;
		tail = other.tail;
		other.tail = tempTail;

		//swaps size
		int tempSize = m_size;
		m_size = other.m_size;
		other.m_size = tempSize;
	}

	void unite(const Set& s1, const Set& s2, Set& result) {
		ItemType temp;

		//empties result 
		while (result.size() > 0) {
			result.get(0, temp);
			result.erase(temp);
		}

		//adds all values from s1 to result
		for (int i = 0; i < s1.size(); i++) {
			s1.get(i, temp);
			result.insert(temp);
		}

		//adds values from s2 that did not appear in s1 to result
		for (int i = 0; i < s2.size(); i++) {
			s2.get(i, temp);
			if (!result.contains(temp))
				result.insert(temp);
		}
	}

	void subtract(const Set& s1, const Set& s2, Set& result) {


	}