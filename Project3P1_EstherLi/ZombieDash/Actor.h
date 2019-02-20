#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
class StudentWorld;


class Actor : public GraphObject {
public:

	Actor(int imageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* world);
	virtual ~Actor() {} //DEFINE LATER??????

	enum ActorType {
		t_penelope, t_dumbZombie, t_smartZombie, t_citizen, t_landmine, 
		t_pit, t_flame, t_vomit, t_vaccineGoodie, t_gasGoodie, t_landmineGoodie, t_wall, t_exit
	};

	//virtual functions
	virtual void doSomething() = 0;
	virtual ActorType getType() = 0;

	//accessor functions
	StudentWorld* world() const;
	bool dead() const;
	bool blockable() const;
	bool isPerson() const;

	//mutator functions
	void setDead();
	void setBlockable();
	void setPerson();

private:
	StudentWorld* m_world;
	bool m_dead;
	bool m_blockable;
	bool m_person;
};

class Wall : public Actor {
public:
	Wall(StudentWorld* world, int startX, int startY);
	virtual ~Wall() {} //DEFINE LATER???????????
	virtual void doSomething();
	virtual ActorType getType();
};

class Penelope : public Actor {
public:
	Penelope(StudentWorld* world, int startX, int startY);
	virtual ~Penelope() {}; //DEFINE LATER!!!!!!!!!!!!!!!
	virtual void doSomething();
	virtual ActorType getType();
	void createValidFlame(int x, int y, int dir);

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
	virtual ActorType getType();
};

class Pit : public Actor {
public:
	Pit(StudentWorld* world, int startX, int startY);
	virtual ~Pit() {}
	virtual void doSomething();
	virtual ActorType getType();
};

class TimedActor : public Actor {
public:
	TimedActor(StudentWorld* world, int startX, int startY, int dir, int depth, int imageID);
	virtual ~Projectile() {}
	virtual void doSomething();
	virtual ActorType getType() = 0;

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
	virtual ActorType getType();
};

class Vomit : public TimedActor {
public:
	Vomit(StudentWorld* world, int startX, int startY, int dir);
	virtual ~Vomit() {}
	virtual ActorType getType();
};

class Zombie : public TimedActor {
public:
	Zombie(StudentWorld* world, int startX, int startY);
	virtual ~Zombie() {}
	virtual void doSomething();
	virtual ActorType getType() = 0;

private:
	int m_movementPlan;
	int m_
};

#endif // ACTOR_H_
