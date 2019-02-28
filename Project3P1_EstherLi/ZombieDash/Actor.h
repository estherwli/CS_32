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
	static bool isActor(Actor* me);
	static bool blocksMovement(Actor* me);
	static bool blocksFlame(Actor* me);
	static bool isHuman(Actor* me);
	static bool isPenelope(Actor* me);
	static bool isCitizen(Actor* me);
	static bool isZombie(Actor* me);
	static bool isDumbZombie(Actor* me);
	static bool isSmartZombie(Actor* me);
	static bool isExit(Actor* me);
	static bool isPit(Actor* me);
	static bool isGoodie(Actor* me);
	static bool isVaccineGoodie(Actor* me);
	static bool isGasCanGoodie(Actor* me);
	static bool isLandmineGoodie(Actor* me);
	static bool isFlame(Actor* me);
	static bool isVomit(Actor* me);
	static bool isLandmine(Actor* me);

	//mutator functions
	void setDead();
	void setBlocksMovement();
	void setBlocksFlame();
	void setHuman();
	void setPenelope();
	void setCitizen();
	void setZombie();
	void setDumbZombie();
	void setSmartZombie();
	void setExit();
	void setPit();
	void setGoodie();
	void setVaccineGoodie();
	void setGasCanGoodie();
	void setLandmineGoodie();
	void setFlame();
	void setVomit();
	void setLandmine();

private:
	StudentWorld* m_world;
	bool m_dead;
	bool m_isActor;
	bool m_blocksMovement;
	bool m_blocksFlame;
	bool m_isHuman;
	bool m_isPenelope;
	bool m_isCitizen;
	bool m_isZombie;
	bool m_isDumbZombie;
	bool m_isSmartZombie;
	bool m_isExit;
	bool m_isPit;
	bool m_isGoodie;
	bool m_isVaccineGoodie;
	bool m_isGasCanGoodie;
	bool m_isLandmineGoodie;
	bool m_isFlame;
	bool m_isVomit;
	bool m_isLandmine;
};

class Wall : public Actor {
public:
	Wall(StudentWorld* world, int startX, int startY);
	virtual ~Wall() {} //DEFINE LATER???????????
	virtual void doSomething();
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

class Landmine : public Actor {
public:
	Landmine(StudentWorld* world, int startX, int startY);
	virtual ~Landmine() {}
	virtual void doSomething();
private:
	int m_nSafetyTicks;
	bool m_active;
};
class Goodie : public Actor {
public:
	Goodie(StudentWorld* world, int startX, int startY, int imageID);
	virtual ~Goodie() {}
	virtual void doSomething();
};

class VaccineGoodie : public Goodie {
public:
	VaccineGoodie(StudentWorld* world, int startX, int startY);
	virtual ~VaccineGoodie() {}
};

class GasCanGoodie : public Goodie {
public:
	GasCanGoodie(StudentWorld* world, int startX, int StartY);
	virtual ~GasCanGoodie() {}
};

class LandmineGoodie : public Goodie {
public:
	LandmineGoodie(StudentWorld* world, int startX, int startY);
	virtual ~LandmineGoodie() {}
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

class Human : public TimedActor {
public:
	Human::Human(int imageID, StudentWorld* world, int startX, int startY);
	virtual ~Human() {}
	virtual void doSomething() = 0;

	//accessor functions
	bool infected() const;
	int nInfected() const;

	//mutator functions
	void addInfect();
	void setInfect(bool a);
	void clearInfect();

private:
	int m_nInfected;
	bool m_infected;
};


class Penelope : public Human {
public:
	Penelope(StudentWorld* world, int startX, int startY);
	virtual ~Penelope() {} //DEFINE LATER!!!!!!!!!!!!!!!
	virtual void doSomething();

	//accessor functions
	int landmine() const;
	int flamethrower() const;
	int vaccine() const;

	//mutator functions
	void addVaccine();
	void addFlamethrower();
	void addLandmine();

private:
	int m_landmine;
	int m_flamethrower;
	int m_nVaccine;
};

class Citizen : public Human {
public: 
	Citizen(StudentWorld* world, int startX, int startY);
	virtual ~Citizen() {}
	virtual void doSomething();

	//helper function
	bool tryToMove(Actor* me, int tempDir);
	void farthestFromZombie(int& newDir, int dist_z, int x, int y);
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
	virtual void doSomething() = 0;

	//helper functions
	void checkVomit(Actor* me); //helper function to check if Zombie should vomit
	void tryToMove(Zombie* me, int deltaX, int deltaY);
	int pickDirection();
	void move(Zombie* me);

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

class SmartZombie : public Zombie {
public:
	SmartZombie(StudentWorld* world, int startX, int startY);
	virtual ~SmartZombie() {}
	virtual void doSomething();

};

#endif // ACTOR_H_
