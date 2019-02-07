#include <iostream>
#include <string>
using namespace std;

Your declarations and implementations would go here

void display(const Landmark* lm)
{
	cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
		<< lm->name() << "." << endl;
}

int main()
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