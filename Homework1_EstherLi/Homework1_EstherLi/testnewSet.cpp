//#include "newSet.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//	Set uls;
//	assert(uls.insert(20));
//	assert(uls.insert(10));
//	assert(uls.size() == 2);
//	assert(uls.contains(10));
//	ItemType x = 30;
//	assert(uls.get(0, x) && x == 10);
//	assert(uls.get(1, x) && x == 20);
//
//	Set uls2;
//	uls2.insert(50);
//	uls2.insert(80);
//	uls = uls2;
//	assert(uls2.get(1, x) && x == 80);
//}
//
//int main()
//{
//	test();
//	cout << "Passed all tests" << endl;
//}
//
//
//
//
////#include "newSet.h"
////#include <iostream>
////#include <cassert>
////#include <string>
////using namespace std;
////
////int main() {
////
////	Set a(1000);   // a can hold at most 1000 distinct items
////	Set b(5);      // b can hold at most 5 distinct items
////	Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
////	ItemType v[6] = { "rachel", "monica", "phoebe", "joey", "chandler", "ross" };
////
////	// No failures inserting 5 distinct items into b
////	for (int k = 0; k < 5; k++)
////		assert(b.insert(v[k]));
////
////	// Failure if we try to insert a sixth distinct item into b
////	assert(!b.insert(v[5]));
////
////	// When two Sets' contents are swapped, their capacities are swapped
////	// as well:
////	a.swap(b);
////	assert(!a.insert(v[5]) && b.insert(v[5]));
////	cout << "All tests passed.";
////
////}