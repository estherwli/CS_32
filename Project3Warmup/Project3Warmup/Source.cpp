#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOddsList(list<int>& li)
{
	list<int>::iterator it;
	list<int> temp;
	it = li.begin();
	while (it != li.end()) {
		if ((*it) % 2 == 0) {
			temp.push_back(*it);
		}
		it++;
	}
	li = temp;
}

void testList()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	list<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOddsList(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end());  // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOddsVector(vector<int>& v)
{
	vector<int>::iterator it;
	vector<int> temp;
	for (it = v.begin(); it != v.end(); it++) {
		if ((*it) % 2 == 0)
			temp.push_back(*it);
	}
	v = temp;
}

void testVector()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOddsVector(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}

vector<int> destroyedOnes;

class Movie
{
public:
	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in li with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBadList(list<Movie*>& li)
{
	list<Movie*>::iterator it;
	int count = 0;
	while (count < li.size()) {
		for (it = li.begin(); it != li.end(); it++) {
			if ((*it)->rating() < 50) {
				delete (*it);
				li.erase(it);
				break;
			}
		}
		count++;
	}
}

void testbad1()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	list<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBadList(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	{
		Movie* mp = *p;
		v.push_back(mp->rating());
	}
	// Aside:  In C++11, the above loop could be
	//     for (auto p = x.begin(); p != x.end(); p++)
	//     {
	//         Movie* mp = *p;
	//         v.push_back(mp->rating());
	//     }
	// or    
	//     for (auto p = x.begin(); p != x.end(); p++)
	//     {
	//         auto mp = *p;
	//         v.push_back(mp->rating());
	//     }
	// or    
	//     for (Movie* mp : x)
	//         v.push_back(mp->rating());
	// or    
	//     for (auto mp : x)
	//         v.push_back(mp->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
		delete *p;
}

vector<int> destroyedOnes;

class Movie
{
public:
	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in v with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original vector.
void removeBadVector(vector<Movie*>& v)
{
}

void testbad2()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	vector<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBadVector(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (int k = 0; k < 4; k++)
		v.push_back(x[k]->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
	for (vector<Movie*>::iterator p = x.begin(); p != x.end(); p++)
		delete *p;
}


int main()
{
	testList();
	testVector();
	testbad1();
	testbad2();
	cout << "Passed" << endl;
}