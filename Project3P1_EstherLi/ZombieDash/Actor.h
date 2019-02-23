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
	static bool blocksMovement(Actor* me);
	static bool blocksFlame(Actor* me);
	static bool isPerson(Actor* me);
	static bool isDumbZombie(Actor* me);
	static bool isSmartZombie(Actor* me);
	static bool isExit(Actor* me);
	static bool isPit(Actor* me);
	static bool isFlame(Actor* me);
	static bool isVomit(Actor* me);

	//mutator functions
	void setDead();
	void setBlocksMovement();
	void setBlocksFlame();
	void setPerson();
	void setDumbZombie();
	void setSmartZombie();
	void setExit();
	void setPit();
	void setFlame();
	void setVomit();

private:
	StudentWorld* m_world;
	bool m_dead;
	bool m_blocksMovement;
	bool m_blocksFlame;
	bool m_isPerson;
	bool m_isDumbZombie;
	bool m_isSmartZombie;
	bool m_isExit;
	bool m_isPit;
	bool m_isFlame;
	bool m_isVomit;
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
	void setInfect();

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

class Pit : public Actor {
public:
	Pit(StudentWorld* world, int startX, int startY);
	virtual ~Pit() {}
	virtual void doSomething();
};

class TimedActor : public Actor {
public:
	TimedActor(StudentWorld* world, int startX, int startY, int dir, int depth, int imageID);
	virtual ~TimedActor() {}
	virtual void doSomething();

	//accessor function
	int nTicks();

	//mutator function
	void addTicks();

private:
	int m_nTicks;
};

class Flame : public TimedActor {
public:
	Flame(StudentWorld* world, int startX, int startY, int dir);
	virtual ~Flame() {}
};

class Vomit : public TimedActor {
public:
	Vomit(StudentWorld* world, int startX, int startY, int dir);
	virtual ~Vomit() {}
};

class Zombie : public TimedActor {
public:
	Zombie(StudentWorld* world, int startX, int startY);
	virtual ~Zombie() {}
	virtual void doSomething();

	//helper functions
	void checkVomit(Actor* me); //helper function to check if Zombie should vomit
	void tryToMove(Zombie* me, int deltaX, int deltaY);

	//mutator functions
	void setMovementPlan(int i);
	void decreaseMovementPlan();

	//accessor functions
	int movementPlan();

private:
	int m_movementPlan;
};

class DumbZombie : public Zombie {
public:
	DumbZombie(StudentWorld* world, int startX, int startY);
	virtual ~DumbZombie() {}
	virtual void doSomething();
private:
	bool m_hasVaccine;
};

#endif // ACTOR_H_
