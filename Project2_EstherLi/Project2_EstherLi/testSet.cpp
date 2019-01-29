#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test1()
{
	Set friends;

	assert(friends.size() == 0); //tests default constructor
	assert(friends.insert("rachel")); //inserts a node
	assert(friends.insert("monica")); //inserts a node
	assert(friends.insert("phoebe")); //inserts a node
	assert(friends.insert("phoebe") == false); //inserts a node that already exists
	assert(friends.size() == 3); //tests size of set after insertions
	assert(friends.contains("rachel")); //tests if node contains something we just inserted
	ItemType x;
	assert(friends.get(0, x) && x == "monica"); //pos parameter is 0
	assert(friends.get(1, x) && x == "phoebe"); //pos parameter is less than m_size
	assert(friends.get(2, x) && x == "rachel"); //pos parameter is less than m_size
	assert(friends.get(3, x) == false); //pos parameter is equal to m_size
	assert(friends.get(-1, x) == false); //pos parameter is less than 0
	assert(friends.erase("monica")); //erase an item from set
	assert(friends.erase("monica") == false); //cannot erase something that was already erased
	assert(friends.contains("monica") == false); //set should not contain something that was erased
	assert(friends.size() == 2); //tests size of set after erasing an item
	assert(friends.get(1, x) && x == "rachel"); //tests get function after erasing an item

	//tests insert and erase with a set containing only 1 node
	Set office;
	assert(office.insert("jim"));
	assert(office.erase("jim"));
	assert(office.size() == 0);

	//tests copy constructor: when parameter is not an empty set
	Set girls(friends);
	assert(girls.size() == 2);
	assert(girls.get(0, x) && x == "phoebe");
	assert(girls.get(1, x) && x == "rachel");
	assert(girls.insert("monica"));

	//tests copy construtor: when parameter is an empty set
	Set h1;
	Set h2(h1);
	assert(h2.size() == 0);

	//tests copy constructor: when parameter has exactly one node
	h1.insert("ho");
	ItemType a;
	Set h3(h1);
	assert(h3.get(0, a) && a == "ho");

	//tests assignment operator when this and other are not empty
	Set amigas;
	amigas.insert("trash");
	amigas = friends;
	assert(amigas.size() == 2);
	assert(amigas.get(0, x) && x == "phoebe");
	assert(amigas.get(1, x) && x == "rachel");

	//tests assignment operator when this is empty, other is not empty
	Set people;
	people = friends;
	assert(people.size() == 2);
	assert(people.get(0, x) && x == "phoebe");
	assert(people.get(1, x) && x == "rachel");

	//tests assignment operator when this is not empty, other is empty
	Set pengyou;
	friends = pengyou;
	assert(friends.size() == 0);
	friends.insert("phoebe");
	friends.insert("monica");

	//tests swap function: when this and other have different sizes
	Set boys;
	boys.insert("ross");
	boys.insert("chandler");
	girls.swap(boys);
	assert(girls.size() == 2);
	assert(girls.get(0, x) && x == "chandler");
	assert(girls.get(1, x) && x == "ross");
	assert(boys.size() == 3);
	assert(boys.get(0, x) && x == "monica");
	assert(boys.get(1, x) && x == "phoebe");
	assert(boys.get(2, x) && x == "rachel");


	//tests swap function: when this and other have the same size
	assert(girls.insert("joey"));
	girls.swap(boys);
	assert(girls.get(0, x) && x == "monica");
	assert(girls.get(1, x) && x == "phoebe");
	assert(girls.get(2, x) && x == "rachel");
	assert(boys.get(0, x) && x == "chandler");
	assert(boys.get(1, x) && x == "joey");
	assert(boys.get(2, x) && x == "ross");

	//tests swap function: when this is empty
	Set a1;
	Set a2;
	a2.insert("yo");
	a1.swap(a2);
	assert(a1.size() == 1 && a2.size() == 0);

	//tests swap function: when other is empty
	a1.swap(a2);
	assert(a1.size() == 0 && a2.size() == 1);

	//tests unite function when s1 is empty
	Set m1;
	unite(m1, girls, friends);
	assert(friends.size() == 3);
	assert(friends.get(0, x) && x == "monica");
	assert(friends.get(1, x) && x == "phoebe");
	assert(friends.get(2, x) && x == "rachel");

	//tests unite function when s2 is empty
	unite(girls, m1, friends);
	assert(friends.size() == 3);
	assert(friends.get(0, x) && x == "monica");
	assert(friends.get(1, x) && x == "phoebe");
	assert(friends.get(2, x) && x == "rachel");

	//tests unite function when s1 and s2 are the same 
	unite(girls, girls, friends);
	assert(friends.size() == 3);
	assert(friends.get(0, x) && x == "monica");
	assert(friends.get(1, x) && x == "phoebe");
	assert(friends.get(2, x) && x == "rachel");

	//tests unite function when s1, s2, and result are all different
	unite(girls, boys, friends);
	assert(friends.size() == 6);
	assert(friends.get(0, x) && x == "chandler");
	assert(friends.get(1, x) && x == "joey");
	assert(friends.get(2, x) && x == "monica");
	assert(friends.get(3, x) && x == "phoebe");
	assert(friends.get(4, x) && x == "rachel");
	assert(friends.get(5, x) && x == "ross");

	//tests unite function when s1 and result are the same
	unite(friends, girls, friends);
	assert(friends.size() == 6);
	assert(friends.get(0, x) && x == "chandler");
	assert(friends.get(1, x) && x == "joey");
	assert(friends.get(2, x) && x == "monica");
	assert(friends.get(3, x) && x == "phoebe");
	assert(friends.get(4, x) && x == "rachel");
	assert(friends.get(5, x) && x == "ross");

	//tests subtract funtion when s1, s2 and result are all different
	subtract(girls, boys, friends);
	assert(friends.size() == 3);
	assert(friends.get(0, x) && x == "monica");
	assert(friends.get(1, x) && x == "phoebe");
	assert(friends.get(2, x) && x == "rachel");

	//tests subtract function when s1 and result are the same
	subtract(boys, friends, boys);
	assert(boys.size() == 3);
	assert(boys.get(0, x) && x == "chandler");
	assert(boys.get(1, x) && x == "joey");
	assert(boys.get(2, x) && x == "ross");

	//tests subtract function when s2 and result are the same
	subtract(friends, boys, boys);
	assert(boys.get(0, x) && x == "monica");
	assert(boys.get(1, x) && x == "phoebe");
	assert(boys.get(2, x) && x == "rachel");

	//tests subtract function when s1, s2 and result are the same
	subtract(friends, friends, friends);
	assert(friends.size() == 0);

	//tests subtract function when s1 is empty
	Set k1;
	subtract(k1, boys, boys);
	assert(boys.size() == 0);

	//tests subtract function when s2 is empty
	boys.insert("ben");
	subtract(boys, k1, boys);
	assert(boys.size() == 1);
}

void test2() {
	Set colors;
	colors.insert("red");
	colors.insert("orange");
	colors.insert("yellow");
	Set warm(colors);
}

void test3() {
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "laobing";
	assert(ss.get(0, x) && x == "pita");
	assert(ss.get(1, x) && x == "roti");
}

//void test4() {
//	Set uls;
//	assert(uls.insert(10));
//	assert(uls.insert(20));
//	assert(uls.size() == 2);
//	assert(uls.contains(20));
//	ItemType x = 30;
//	assert(uls.get(0, x) && x == 10);
//	assert(uls.get(1, x) && x == 20);
//}



int main()
{
	test1();
	test2();
	test3();
	cout << "Passed all tests" << endl;
}