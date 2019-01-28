#ifndef SET_INCLUDED
#define SET_INCLUDED
#include <string>
using ItemType = std::string;

class Set {
public:
	Set(); //default constructor
	~Set(); //destructor
	Set(const Set& other); //copy constructor
	Set& operator=(const Set& other); //assignment operator
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
	void dump();

private:
	//declaration for Node
	class Node {
	public:
		ItemType data;
		Node *next;
		Node *last;
	};

	int m_size;
	Node *head;
	Node *tail;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);


#endif 