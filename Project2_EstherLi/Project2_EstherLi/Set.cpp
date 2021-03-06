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
}

//copy constructor
Set::Set(const Set& other) {
	m_size = 0; //first construct an empty list
	head = nullptr;
	tail = nullptr;
	Node *p = other.head;
	while (p != nullptr) {
		insert(p->data); //copies each node to new set and updates m_size
		p = p->next;
	}
}

//assignment operator
Set& Set::operator=(const Set& other) {
	if (&other == this) //assigning the same set to itself
		return *this;
	Node *p = head;
	while (p != nullptr) { //free memory in this set
		Node *n = p->next;
		delete p;
		p = n;
	}
	head = nullptr; //treat this set as empty
	tail = nullptr;
	m_size = 0;

	Node *q = other.head;
	while (q != nullptr) {
		insert(q->data); //add nodes from other set to this set
		q = q->next;
	}
	return *this;
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
	if (contains(value)) //checks if set already has the value
		return false;

	//allocate new node
	Node *latest = new Node;
	latest->data = value;
	m_size++; //increase the size of set

	//case 1: empty set
	if (head == nullptr) {
		latest->next = nullptr;
		latest->last = nullptr;
		head = tail = latest; //link head and tail nodes to the new node
	}

	//case 2: set has >= 1 nodes
	else {
		tail->next = latest;
		latest->last = tail;
		latest->next = nullptr;
		tail = latest; //link tail node to new tail
	}
	return true;
}

bool Set::erase(const ItemType& value) {
	if (head == nullptr) //empty set
		return false;

	//case 1: deleting top node
	if (head->data == value) {
		Node *killMe = head;  
		head = killMe->next; //update current head to point to the second node
		delete killMe; 
		m_size--;
		return true;
	}

	//case 2: deleting interior node or tail node
	Node *p = head;
	while (p != nullptr) {
		if (p->next != nullptr && p->next->data == value) {
			Node *killMe = p->next;
			p->next = killMe->next; 
			delete killMe;
			m_size--;
			return true;
		}
		p = p->next;
	}
	return false; //traversed entire set and no value could be deleted
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
	return false; //traversed entire set and value was not found
}

bool Set::get(int pos, ItemType& value) const {
	if (head == nullptr || pos < 0 || pos >= m_size) //invalid conditions
		return false;

	Node *p = head;
	while (p != nullptr) { //traverse through entire set (past last node)
		int count = 0;
		Node *temp = head;
		while (temp != nullptr) {
			if (p->data > temp->data)
				count++; //records how many values p is strictly greater than
			temp = temp->next;
		}
		if (count == pos) { //we found the value in set
			value = p->data;
			return true;
		}
		p = p->next;
	}
	return false; //traversed through entire set and did not find value
}

void Set::swap(Set& other) {
	if ((head == nullptr && other.head == nullptr) || this == &other)
		return;

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
	Set tempSet; //in case of aliasing

	//assign all values from s1 to result
	tempSet = s1;

	//adds values from s2 that did not appear in s1 to result
	for (int i = 0; i < s2.size(); i++) {
		s2.get(i, temp);
		if (!tempSet.contains(temp))
			tempSet.insert(temp);
	}
	result = tempSet; //assigns tempSet to result
}

void subtract(const Set& s1, const Set& s2, Set& result) {
	ItemType temp;
	Set tempSet;

	//assign all values from s1 to result
	tempSet = s1;

	//deletes values that appeared in both s1 and s2
	for (int i = 0; i < s2.size(); i++) {
		s2.get(i, temp);
		if (tempSet.contains(temp))
			tempSet.erase(temp);
	}
	result = tempSet; //assigns tempSet to result in case of aliasing
}

void Set::dump() {
	for (Node *t = head; t != nullptr; t = t->next)
		cerr << t->data << endl;
}