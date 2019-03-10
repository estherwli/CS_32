#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>


template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie();
	void reset();
	void insert(const std::string& key, const ValueType& value);
	//std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;


	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;

private:
	struct Node;
	struct Pair {
		Pair(char label, Node* child) {
			m_label = label;
			m_child = child;
		}
		~Pair() {} //DO I NEED TO IMPLEMENT THIS LATER?



		//accessor functions
		char label() { return m_label; }
		Node* child() { return m_child; }

		//data members for Pair
		char m_label;
		Node* m_child;
	};

	struct Node {
		Node() {}
		Node(const ValueType& value) { m_values.push_back(value); }
		Node(Pair* child) { m_children.push_back(child); }
		~Node() {
			for (int i = m_values.size() - 1; i >= 0; i--) {
				m_values.pop_back();
			}
			for (int i = m_children.size() - 1; i >= 0; i--) {
				if (m_children[i] != nullptr) {
					delete m_children[i];
					m_children.pop_back();
				}
			}
		}

		//data members for Node 
		std::vector<ValueType> m_values;
		std::vector<Pair*> m_children;
	};

	//private functions for Trie
	void freeTree(Node* current);

	//private data member for Trie 
	Node* m_root;

public:
	//************************************
	void printMe(Node* current, std::string path);
	void print();
	//	//************************************
};

template<typename ValueType>
Trie<ValueType>::Trie() {
	m_root = new Node();
}

template<typename ValueType>
Trie<ValueType>::~Trie() {
	freeTree(m_root);
}

template<typename ValueType>
void Trie<ValueType>::freeTree(Node* current) {
	if (current == nullptr)
		return;
	if (current->m_children.size() != 0) {
		typename std::vector<Pair*>::iterator it = current->m_children.begin();
		while (it != current->m_children.end()) {
			freeTree((*it)->child());
			it++;
		}
	}
	delete current;
}

template<typename ValueType>
void Trie<ValueType>::reset() {
	freeTree(m_root);
	m_root = new Node();
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
	Node* curNode = m_root;
	for (int i = 0; i < key.size(); i++) {
		bool next = false;
		for (int j = 0; j < curNode->m_children.size(); j++) {
			if (curNode->m_children[j]->label() == key[i]) { //found a child with the same label as a char in key
				if (i == key.size() - 1) {
					curNode->m_children[j]->child()->m_values.push_back(value); //found the last char in key
					return;
				}
				curNode = curNode->m_children[j]->child(); //traverse deeper into the trie
				next = true; //note that we traversed to the next level already
				break;
			}
		}
		if (i == key.size() - 1) {
			curNode->m_children.push_back(new Pair(key[i], new Node(value))); //add last char of key
			return;
		}
		if (next)
			continue; //traversed deeper, so no need to add a new child yet
		Node* newChild = new Node();
		curNode->m_children.push_back(new Pair(key[i], newChild)); //add a non-last char of key
		curNode = newChild;
	}
}

template<typename ValueType>
void Trie<ValueType>::printMe(Node* current, std::string path) {
	if (current == nullptr || current->m_children.empty())
		return;
	typename std::vector<Pair*>::iterator it = current->m_children.begin();
	while (it != current->m_children.end()) {
		std::cout << path << (*it)->label() << std::endl;
		printMe((*it)->child(), path + (*it)->label() + "/");
		it++;
	}
}

template<typename ValueType>
void Trie<ValueType>::print() {
	printMe(m_root, "");
}

#endif // TRIE_INCLUDED
