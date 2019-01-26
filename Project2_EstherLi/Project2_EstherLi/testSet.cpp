#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Set friends;
	
	assert(friends.size() == 0); //checks default constructor
	assert(friends.insert("rachel")); //inserts a node
	assert(friends.insert("monica")); //inserts a node
	assert(friends.insert("phoebe")); //inserts a node
	assert(friends.insert("phoebe") == false); //inserts a node that already exists
	assert(friends.size() == 3); //checks size of set after insertions
	assert(friends.contains("rachel")); //checks if node contains something we just inserted
	ItemType x;
	assert(friends.get(0, x) && x == "monica"); //pos parameter is 0
	assert(friends.get(1, x) && x == "phoebe"); //pos parameter is less than m_size
	assert(friends.get(2, x) && x == "rachel"); //pos parameter is less than m_size
	assert(friends.get(3, x) == false); //pos parameter is equal to m_size
	assert(friends.get(-1, x) == false); //pos parameter is less than 0
	assert(friends.erase("monica")); //erase an item from set
	assert(friends.erase("monica") == false); //cannot erase something that was already erased
	assert(friends.size() == 2); //checks size of set after deletions
	assert(friends.get(1, x) && x == "rachel"); //checks get function after deletions
	assert(friends.contains("monica") == false); //set should not contain something that was erased
	
	Set girls(friends); //checks copy constructor
	assert(girls.size() == 2);
	assert(girls.get(0, x) && x == "phoebe");
	assert(girls.get(1, x) && x == "rachel");
	assert(girls.insert("monica"));
	
	Set amigas = friends; //checks assignment operator
	assert(amigas.size() == 2);
	assert(amigas.get(0, x) && x == "phoebe");
	assert(amigas.get(1, x) && x == "rachel");

	Set boys; //checks swap function
	boys.insert("ross");
	boys.insert("chandler");
	girls.swap(boys);
	assert(girls.size() == 2);
	assert(girls.get(0, x) && x == "chandler");
	assert(girls.get(1, x) && x == "ross");
	assert(girls.insert("joey"));
	assert(boys.size() == 3);
	assert(boys.get(0, x) && x == "monica");
	assert(boys.get(1, x) && x == "phoebe");
	assert(boys.get(2, x) && x == "rachel");
	girls.swap(boys);

	unite(girls, girls, friends);
	assert(friends.size() == 3);
	assert(friends.get(0, x) && x == "monica");
	assert(friends.get(1, x) && x == "phoebe");
	assert(friends.get(2, x) && x == "rachel");

	unite(girls, boys, friends);
	assert(friends.size() == 6);
	assert(friends.get(0, x) && x == "chandler");
	assert(friends.get(1, x) && x == "joey");
	assert(friends.get(2, x) && x == "monica");
	assert(friends.get(3, x) && x == "phoebe");
	assert(friends.get(4, x) && x == "rachel");
	assert(friends.get(5, x) && x == "ross");

	unite(friends, girls, friends);
	assert(friends.size() == 6);
	assert(friends.get(0, x) && x == "chandler");
	assert(friends.get(1, x) && x == "joey");
	assert(friends.get(2, x) && x == "monica");
	assert(friends.get(3, x) && x == "phoebe");
	assert(friends.get(4, x) && x == "rachel");
	assert(friends.get(5, x) && x == "ross");

	subtract(girls, boys, friends);
	assert(friends.size() == 3);
	assert(friends.get(0, x) && x == "monica");
	assert(friends.get(1, x) && x == "phoebe");
	assert(friends.get(2, x) && x == "rachel");

	subtract(friends, boys, boys);
	assert(boys.size() == 3);
	assert(boys.get(0, x) && x == "monica");
	assert(boys.get(1, x) && x == "phoebe");
	assert(boys.get(2, x) && x == "rachel");




}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}