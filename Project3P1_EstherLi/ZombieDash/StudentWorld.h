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
    StudentWorld(std::string assetPath);
	~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	
	//helper functions
	bool blocked(int x, int y, bool (*f)(Actor*));
	bool overlapped(int x1, int y1, int x2, int y2);
	std::string level();
	bool foundSomething(Actor* me, bool (*f)(Actor*));
	void createFlame(int x, int y, int dir);
	
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
