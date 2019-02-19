#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int imageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* world);
	virtual ~Actor() {} //DEFINE LATER??????

	//virtual functions
	virtual void doSomething() = 0;

	//accessor functions
	StudentWorld* world() const;
	bool dead() const;
	bool blockable() const;
	bool exitable() const;

	//mutator functions
	void setDead();
	void setBlockable();
	void setExitable();

private:
	StudentWorld* m_world;
	bool m_dead;
	bool m_blockable;
	bool m_exitable;
};

class Wall : public Actor {
public:
	Wall(StudentWorld* world, int startX, int startY);
	virtual ~Wall() {} //DEFINE LATER???????????
	virtual void doSomething();
};

class Penelope : public Actor {
public:
	Penelope(StudentWorld* world, int startX, int startY);
	virtual ~Penelope() {}; //DEFINE LATER!!!!!!!!!!!!!!!
	virtual void doSomething();

	//accessor functions
	bool infected() const;
	int nInfected() const;
	int lives() const;
	int landmine() const;
	int flamethrower() const;
	int vaccine() const;

	//mutator functions
	void addInfect();

private:
	int m_lives;
	int m_landmine;
	int m_flamethrower;
	int m_vaccine;
	int m_nInfected; 
	bool m_infected;
};

class Exit : public Actor {
public:
	Exit(StudentWorld* world, int startX, int startY);
	virtual ~Exit() {} //define later?
	virtual void doSomething();
};

#endif // ACTOR_H_
