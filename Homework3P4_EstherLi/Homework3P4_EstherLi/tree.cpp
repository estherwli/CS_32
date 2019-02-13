#include <iostream>
#include<cassert>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
	  // in the n1 element array a1 in the same order (though not
	  // necessarily consecutively).  The empty sequence appears in a
	  // sequence of length n1 in 1 way, even if n1 is 0.
	  // For example, if a1 is the 7 element array
	  //	10 50 40 20 50 40 30
	  // then for this value of a2     the function must return
	  //	10 20 40					1
	  //	10 40 30					2
	  //	20 10 40					0
	  //	50 40 30					3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) //treat negative values as 0; an empty sequence appears in 1 way in a1
		return 1;
	if (n1 < n2) //impossible for a1 to contain a2 if n1 < n2 
		return 0;
	if (a1[0] == a2[0]) //found first matching value; now checks that the rest of a2 is in a1 & finds all other ways a2 appears in a1
		return countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1) + countIncludes(a1 + 1, n1 - 1, a2, n2);
	else
		return countIncludes(a1 + 1, n1 - 1, a2, n2); //tries to find first matching value
}

// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > divider
//   * for firstNotGreater <= i < firstLess, a[i] == divider
//   * for firstLess <= i < n, a[i] < divider
// All the elements > divider end up in no particular order.
// All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > divider
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == divider
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < divider

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < divider)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > divider)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 1)
		return;
	int firstNotGreater, firstLess;
	divide(a, n, a[n / 2], firstNotGreater, firstLess);
	order(a, firstNotGreater);
	order(a + firstLess, n - firstLess);
}






void test1() {
	double a1[] = { 1, 2, 3, 4, 5 };
	double a2[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	double a3[] = { 2.0, 4.0 };
	double a4[] = { 2, 4, 4, 2, 4};
	double a5[] = { 3, 3, 3 };
	double a6[] = { 3 };
	assert(countIncludes(a1, 5, a2, 5) == 1);
	assert(countIncludes(a1, 5, a2, 4) == 1);
	assert(countIncludes(a1, 0, a2, 0) == 1);
	assert(countIncludes(a1, -1, a2, -2) == 1);
	assert(countIncludes(a1, -2, a2, -1) == 1);
	assert(countIncludes(a1, 0, a2, 5) == 0);
	assert(countIncludes(a1, 4, a2, 5) == 0);
	assert(countIncludes(a1, 5, a3, 2) == 1);
	assert(countIncludes(a4, 5, a3, 2) == 4);
	assert(countIncludes(a5, 3, a6, 1) == 3);
	assert(countIncludes(a1, 5, a5, 3) == 0);
}

void test2() {
	double a1[] = { 2, 3, 4, 5, 6, 7, -1 };
	double a2[] = { 2, 2, 2, 3 };
	double a3[] = { 0, 0, 0 }; 
	double a4[] = { 6, 2, 6, 3, 2, 1, 4, 5};

	order(a1, 7);
	for (int i = 0; i < 7; i++)
		cout << a1[i] << " ";
	cout << endl;

	order(a2, 4);
	for (int i = 0; i < 4; i++)
		cout << a2[i] << " ";
	cout << endl;

	order(a3, 3);
	for (int i = 0; i < 3; i++)
		cout << a3[i] << " ";
	cout << endl;

	order(a4, 8);
	for (int i = 0; i < 8; i++)
		cout << a4[i] << " ";
	cout << endl;

}
void test_tree()
{
	double a1[] = { 10, 50, 40, 20, 50, 40, 30 };
	double a2[] = { 10, 20, 40 };
	double a3[] = { 10, 40, 30 };
	double a4[] = { 20, 10, 40 };
	double a5[] = { 50, 40, 30 };
	//	10 50 40 20 50 40 30
	// then for this value of a2     the function must return
	//	10 20 40			1
	//	10 40 30			2
	//	20 10 40			0
	//	50 40 30			3

	int n1 = 7;
	int n2 = 3;

	assert(countIncludes(a1, n1, a2, n2) == 1);
	assert(countIncludes(a1, n1, a3, n2) == 2);
	assert(countIncludes(a1, n1, a4, n2) == 0);
	assert(countIncludes(a1, n1, a5, n2) == 3);
	assert(countIncludes(a5, n2, a1, n1) == 0);

	double c8[] = { 1,1,1,1,1,1,1,1,1,1,1 }; // 11
	double c9[] = { 1,1 }; // 2

	int count = countIncludes(c8, 11, c8, 2);
	assert(count == 55);

	count = countIncludes(c8, 11, c8, 1);
	assert(count == 11);

	n1 = 9;
	double b1[] = { 10, 10, 10, 3, 5, 2, 4, 7, 0 };

	order(b1, n1);
	for (int i = 0; i < n1 - 1; i++)
		assert(b1[i] >= b1[i + 1]);

	n1 = 9;
	double b2[] = { 10, 10, 10, 3, 3, 4, 3, 3, 3 };

	order(b2, n1);
	for (int i = 0; i < n1 - 1; i++)
		assert(b2[i] >= b2[i + 1]);

	n1 = 17;
	double d1[] = { 5.0,  6.0, -70.0, 20.0, 50.0,  1.0,  3.0, -70.0, 90.0,
				   78.0, 21.0,   2.0, 30.0, 40.0, 80.0, 99.0,  93.0 };  // 17
	order(d1, n1);
	for (int i = 0; i < n1 - 1; i++)
		assert(d1[i] >= d1[i + 1]);

	double d8[99];

	for (int i = 0; i < 50; i++) 	d8[i] = i;
	for (int i = 50; i < 99; i++) 	d8[i] = -10000 + i;
	order(d8, 99);
	for (int i = 0; i < 98; i++)
		assert(d8[i] >= d8[i + 1]);

	cout << endl << "pass all the tests in  = test_tree()" << endl;
}


int main() {
	test1();
	test2();
	test_tree();
	cout << "Passed all tests.";
}