#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <algorithm>

template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie();
	void reset();
	void insert(const std::string& key, const ValueType& value);
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;

private:
	struct Pair {
		Pair(char label, Node* child) {
			m_label = label;
			m_child = child;
		}
		~Pair() {} //DO I NEED TO IMPLEMENT THIS LATER?

		//accessor functions
		char label() { return m_label; }
		Node* child() { return m_child; }

		//private data members for Pair
		char m_label;
		Node* m_child;
	};
	struct Node {
		Node() {}
		Node(ValueType value) { m_values.push_back(value); }
		Node(Pair child) { m_children.push_back(child); }
		~Node() {
			for (int i = m_values.end(); i >= 0; i--) //destructs the m_values vector 
				m_values.pop_back();
			Pair* p = &m_children.front(); //destructs the m_children list
			while (p != nullptr) {
				Node *n = p->next;
				delete p;
				p = n;
			}
		}

		//private data members for Node 
		vector<ValueType> m_values;
		list<Pair> m_children;
	};

	//private functions for Trie
	void freeTree(Node* current);

	//private data member for Trie 
	Node* m_root;
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
	freeTree(current->left);
	freeTree(current->right);
	delete current;
}

template<typename ValueType>
void Trie<ValueType>::reset() {
	freeTree(m_root);
	m_root = new Node();
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
	int i = 0;
	Pair* j = m_root->m_children.front();
	Node* prev;
	while (i < key.size() && j != nullptr) {
		if (j->label() == key[i]) { //found a Node with the right label, so move on to the next character 
			i++;
			if (i == key.size()) {//found the last character of key
				j->child()->m_values.push_back(value); //push value to the m_values vector of the last character's Node
				return;
			}
			prev = j;
			if (j->child() != nullptr)
				j = j->child()->m_children.front(); //traverse down deeper to the next Node
			else
				break;
		}
		else if (j->next != nullptr)
			j = j->next; //traverse across other children of our current Node
		else  //previously found a Node with the right label, but now the sequence is interrupted
			break;
	}
	while (i < key.size() - 1) {
		j = Pair(key[i], new Node());
		j = j->child();
		i++;
	}
	j = Pair(key[i], new Node(value));
	return;

	//int k = key.size() - 1;
	//Node lastNode(Pair(key[k], Node(value)));
	//while (k > i) {
	//	k--;
	//	Node newNode(Pair(key[k], lastNode);
	//	lastNode = newNode;
	//}
	//prev->m_children.push_back(key[i], newNode));

}



#endif // TRIE_INCLUDED
