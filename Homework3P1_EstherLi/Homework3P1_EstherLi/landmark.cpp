#include <iostream>
#include <string>
using namespace std;

class Landmark {
public:
	Landmark(string name) //compilation error if Landmark object is created bc icon is pure virtual
		:m_name(name) {}
	virtual ~Landmark() {}
	string name() const {
		return m_name;
	}
	virtual string color() const { //non-pure virtual
		return "yellow";
	}
	virtual string icon() const = 0; //pure virtual

private:
	string m_name;
};

class Hotel : public Landmark {
public:
	Hotel(string name)
		: Landmark(name) {
	}
	virtual ~Hotel() {
		cout << "Destroying the hotel " << Landmark::name() << "." << endl;
	}
	virtual string icon() const {
		return "bed";
	}
};

class Restaurant : public Landmark {
public:
	Restaurant(string name, int capacity)
		: Landmark(name) {
		m_capacity = capacity;
	}
	virtual ~Restaurant() {
		cout << "Destroying the restaurant " << Landmark::name() << "." << endl;
	}
	virtual string icon() const {
		if (m_capacity < 40)
			return "small knife/fork";
		else
			return "large knife/fork";
	}
private:
	int m_capacity;
};

class Hospital : public Landmark {
public:
	Hospital(string name)
		: Landmark(name) {
	}
	virtual ~Hospital() {
		cout << "Destroying the hospital " << Landmark::name() << "." << endl;
	}
	virtual string icon() const {
		return "H";
	}
	virtual string color() const {
		return "blue";
	}
};




void display(const Landmark* lm)
{
	cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
		<< lm->name() << "." << endl;
}

void test1()
{
	Landmark* landmarks[4];
	landmarks[0] = new Hotel("Westwood Rest Good");
	// Restaurants have a name and seating capacity.  Restaurants with a
	// capacity under 40 have a small knife/fork icon; those with a capacity
	// 40 or over have a large knife/fork icon.
	landmarks[1] = new Restaurant("Bruin Bite", 30);
	landmarks[2] = new Restaurant("La Morsure de l'Ours", 100);
	landmarks[3] = new Hospital("UCLA Medical Center");

	cout << "Here are the landmarks." << endl;
	for (int k = 0; k < 4; k++)
		display(landmarks[k]);

	// Clean up the landmarks before exiting
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete landmarks[k];
}

/*
Here are the landmarks.
Display a yellow bed icon for Westwood Rest Good.
Display a yellow small knife/fork icon for Bruin Bite.
Display a yellow large knife/fork icon for La Morsure de l'Ours.
Display a blue H icon for UCLA Medical Center.
Cleaning up.
Destroying the hotel Westwood Rest Good.
Destroying the restaurant Bruin Bite.
Destroying the restaurant La Morsure de l'Ours.
Destroying the hospital UCLA Medical Center.
*/



int main() {
	test1();
}