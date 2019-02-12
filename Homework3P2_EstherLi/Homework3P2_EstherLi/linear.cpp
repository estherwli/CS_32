#include <iostream>
#include <cassert>
using namespace std;

bool somePredicate(double value) {
	if (value > 0)
		return true;
	else
		return false;
}

// Return true if the somePredicate function returns true for at
	  // least one of the array elements, false otherwise.
bool anyTrue(const double a[], int n)
{
	if (n <= 0)
		return false;
	if (n == 1)
		return somePredicate(a[0]);
	int first = anyTrue(a, n / 2); //divide and conquer
	int last = anyTrue(a + n / 2, n - n / 2);
	return (first || last); //either half of the array contains a true value
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
	if (n <= 0)
		return 0;
	if (n == 1) {
		if (somePredicate(a[0]))
			return 1; //found a true value
		else
			return 0;
	}
	int first = countTrue(a, n / 2); //divide and conquer
	int last = countTrue(a + n / 2, n - n / 2);
	return first + last; //adds number of true values in both halves of the array
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
	if (n <= 0)
		return -1;
	else if (somePredicate(a[0]))
		return 0;
	else {
		if (firstTrue(a + 1, n - 1) == -1) //true value was not found in rest of array
			return -1;
		else
			return 1 + firstTrue(a + 1, n - 1); //true value was found somewhere after the 0th element in the array
	}
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no 
// elements, return -1.
int positionOfMin(const double a[], int n)
{
	if (n <= 0)
		return -1;
	if (n == 1)
		return 0;
	if (a[0] <= a[1 + positionOfMin(a + 1, n - 1)]) //first element is smaller than the minimum of the rest of array
		return 0;
	else
		return 1 + positionOfMin(a + 1, n - 1); //first element is greater than the minimum of the rest of array
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) //treat negative n2 values as 0
		return true;
	if (n2 > n1)
		return false;
	if (a1[0] == a2[0]) //found first matching value
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1); //continues to find contiguous subsequence 
	else
		return includes(a1 + 1, n1 - 1, a2, n2); //tries to find first matching value
}

int main() {
	double a1[] = { -0.1, 0.2, -1.0, -2.3 };
	double a2[] = { -5.2, 0, -3.2 };
	double a3[] = { 1 };
	assert(anyTrue(a1, 4) == true);
	assert(anyTrue(a2, 3) == false);
	assert(anyTrue(a3, 1) == true);
	assert(anyTrue(a3, 0) == false);
	assert(anyTrue(a3, -2) == false);

	double b1[] = { -2, 1, 2, 3, 4, -5 };
	double b2[] = { 0, 0, 0 };
	double b3[] = { -0.2, 0.2, -3, -10 };
	assert(countTrue(b1, 6) == 4);
	assert(countTrue(b1, 3) == 2);
	assert(countTrue(b1, 2) == 1);
	assert(countTrue(b2, 3) == 0);
	assert(countTrue(b3, 4) == 1);
	assert(countTrue(b3, -2) == 0);
	assert(countTrue(b3, 0) == 0);

	double c1[] = { 1, 1, 1 };
	assert(firstTrue(b1, 6) == 1);
	assert(firstTrue(b2, 3) == -1);
	assert(firstTrue(a3, 1) == 0);
	assert(firstTrue(c1, 3) == 0);
	assert(firstTrue(c1, 0) == -1);
	assert(firstTrue(c1, -1) == -1);

	assert(positionOfMin(b1, 6) == 5);
	assert(positionOfMin(b2, 3) == 0);
	assert(positionOfMin(b3, 4) == 3);
	assert(positionOfMin(b3, 0) == -1);
	assert(positionOfMin(b3, -1) == -1);

	double d1[] = { 2, 3, 4 };
	double d2[] = { 1, 2, 3, 4, 5 };
	double d3[] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	double d4[] = { 5, 4, 3, 2, 1 };
	double d5[] = { 2, 3, 2, 4 };
	assert(includes(d2, 5, d1, 3));
	assert(includes(d3, 10, d1, 3));
	assert(includes(d4, 5, d1, 3) == false);
	assert(includes(d5, 4, d1, 3));
	assert(includes(d5, 3, d1, 2));
	assert(includes(d1, 3, d1, 3));
	assert(includes(d2, 0, d1, 3) == false);
	assert(includes(d2, 0, d1, 0));
	assert(includes(d2, 2, d1, 0));
	assert(includes(d2, 0, d1, 2) == false);
	assert(includes(d2, -1, d1, -1));
	assert(includes(d2, -3, d1, -2));
	assert(includes(d2, -2, d1, -3));
	assert(includes(d2, -2, d1, 3) == false);

	cout << "Passed all tests." << endl;
}