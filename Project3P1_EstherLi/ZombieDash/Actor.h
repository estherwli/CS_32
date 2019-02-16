#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int imageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* world, std::string name);
	virtual ~Actor() {} //DEFINE LATER??????

	//virtual functions
	virtual void doSomething() = 0;

	//accessor functions
	StudentWorld* world() const;
	bool dead() const;
	std::string name() const;

	//mutator functions
	void setDead();

private:
	StudentWorld* m_world;
	bool m_dead;
	std::string m_name;
};

class Wall : public Actor {
public:
	Wall(StudentWorld* world, int startX, int startY);
	virtual ~Wall() {} //DEFINE LATER???????????
	virtual void doSomething() {}
};

class Penelope : public Actor {
public:
	Penelope(StudentWorld* world, int startX, int startY);
	virtual ~Penelope() {}; //DEFINE LATER!!!!!!!!!!!!!!!
	virtual void doSomething() {}

private:
	int m_landmine;
	int m_flamethrower;
	int m_vaccine;
	bool m_infected; //move this to a People base class for PART2!
};


#endif // ACTOR_H_
