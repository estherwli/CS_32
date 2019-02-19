#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
class Actor;
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
	bool blocked(int x, int y);
	bool overlapped(int x1, int y1, int x2, int y2);
	bool foundExit(Actor* me);
	
	//mutator functions
	void setCompleted(bool input);

	//accessor functions
	std::string stat() const;
	bool completed() const;

private:
	std::vector<Actor*> m_actors;
	Penelope* m_player;
	bool m_completed;
};

#endif // STUDENTWORLD_H_
