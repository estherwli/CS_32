#include "GraphObject.h"
#include "Actor.h"
#include "StudentWorld.h"
#include <string>
using namespace std;

Actor::Actor(int imageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* world)
	:GraphObject(imageID, startX, startY, startDirection, depth) {
	m_world = world;
	m_dead = false;
	m_blockable = false;
	m_exitable = false;
}

StudentWorld* Actor::world() const {
	return m_world;
}

bool Actor::dead() const {
	return m_dead;
}


bool Actor::blockable() const {
	return m_blockable;
}

bool Actor::exitable() const {
	return m_exitable;
}

void Actor::setDead() {
	m_dead = true;
}

void Actor::setBlockable() {
	m_blockable = true;
}

void Actor::setExitable() {
	m_exitable = true;
}

//******************PENELOPE******************
Penelope::Penelope(StudentWorld* world, int startX, int startY)
	: Actor(IID_PLAYER, startX, startY, GraphObject::right, 0, world) {
	m_lives = 3;
	m_landmine = 0;
	m_flamethrower = 0;
	m_vaccine = 0;
	m_infected = false;
	m_nInfected = 0;
}

bool Penelope::infected() const {
	return m_infected;
}

int Penelope::nInfected() const {
	return m_nInfected;
}

int Penelope::lives() const {
	return m_lives;
}

int Penelope::landmine() const {
	return m_landmine;
}

int Penelope::flamethrower() const {
	return m_flamethrower;
}
int Penelope::vaccine() const {
	return m_vaccine;
}

void Penelope::addInfect() {
	m_nInfected++;
}

void Penelope::doSomething() {
	if (dead())
		return;
	if (infected()) {
		if (nInfected() == 500) {
			setDead();
			world()->playSound(SOUND_PLAYER_DIE);
			return;
		}
		else
			addInfect();
	}
	if (world()->foundExit(this)) 
		world()->setCompleted(true);
	int x = getX();
	int y = getY();
	int ch;
	if (world()->getKey(ch)) {
		switch (ch) {
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (!world()->blocked(x - 4, y))
				moveTo(x - 4, y);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (!world()->blocked(x + 4, y))
				moveTo(x + 4, y);
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (!world()->blocked(x, y + 4))
				moveTo(x, y + 4);
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			if (!world()->blocked(x, y - 4))
				moveTo(x, y - 4);
			break;
		}
	}
	return;
}

//******************WALL******************
Wall::Wall(StudentWorld* world, int startX, int startY)
	:Actor(IID_WALL, startX, startY, GraphObject::right, 0, world) {
	setBlockable();
}

void Wall::doSomething() {
	return;
}

//******************EXIT******************
Exit::Exit(StudentWorld* world, int startX, int startY)
	: Actor(IID_EXIT, startX, startY, GraphObject::right, 1, world) {
	setExitable();
}

void Exit::doSomething() {
	return;
}




