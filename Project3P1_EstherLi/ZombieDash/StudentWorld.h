#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>
class Penelope;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	//these constants are used for findClosestHumanOrZombie, specifically when a Citizen tries to get closer to Penelope
	static const int LEFT_DOWN = 111;
	static const int LEFT_UP = 222;
	static const int RIGHT_DOWN = 333;
	static const int RIGHT_UP = 444;

    StudentWorld(std::string assetPath);
	~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	
	//helper functions
	std::string level(); //returns the correctly formatted file name for the current level
	bool hasProperty(int x, int y, bool (*f)(Actor*), Actor* me = nullptr); //checks if (x,y) has an Actor with property f
	bool foundSomething(int x1, int y1, bool (*f)(Actor*)); //checks if (x1,y1) overlaps with an Actor with property f
	void createValidObject(int x, int y, int dir, int amount, bool(*check)(Actor*), std::string projectileType); //creates new Actor(s), if possible
	int findClosestHumanOrZombie(int x1, int y1, double& distanceSq, bool(*f)(Actor*), std::string str = ""); //returns direction to closest, -1 if not close enough
	double euclideanDistanceSq(int x1, int y1, int x2, int y2); //calculates the eulidean distance between the centers of 2 Actors
	bool anyCitizensLeft(); //returns true if there are still Citizens left in the level

	//mutator functions
	void setCompleted();

	//accessor functions
	std::string stat() const;
	bool completed() const;

private:
	std::vector<Actor*> m_actors;
	Penelope* m_player;
	bool m_completed;
};

#endif // STUDENTWORLD_H_
