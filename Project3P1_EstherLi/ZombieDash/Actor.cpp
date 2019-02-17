#include "GraphObject.h"
#include "Actor.h"
#include "StudentWorld.h"
#include <string>
using namespace std;

Actor::Actor(int imageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* world, string name)
	:GraphObject(imageID, startX, startY, startDirection, depth) {
	m_dead = false;
	m_world = world;
	m_name = name;
}


StudentWorld* Actor::world() const {
	return m_world;
}

bool Actor::dead() const {
	return m_dead;
}

string Actor::name() const {
	return m_name;
}

void Actor::setDead() {
	m_dead = true;
}


Wall::Wall(StudentWorld* world, int startX, int startY)
	:Actor(IID_WALL, startX, startY, GraphObject::right, 0, world, "wall") {}

void Wall::doSomething() {
	return;
}

Penelope::Penelope(StudentWorld* world, int startX, int startY)
	: Actor(IID_PLAYER, startX, startY, GraphObject::right, 0, world, "penelope") {
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
	int ch;
	if (world()->getKey(ch)) {
		int x = getX();
		int y = getY();
		int dir = getDirection();
		switch (ch) {
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (!world()->blocked(x - 4, y, left))
				moveTo(x - 4, y);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (!world()->blocked(x + 4, y, right))
				moveTo(x + 4, y);
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (!world()->blocked(x, y + 4, up))
				moveTo(x, y + 4);
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			if (!world()->blocked(x, y - 4, down))
				moveTo(x, y - 4);
			break;
		}
	}
	return;
}



