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

Penelope::Penelope(StudentWorld* world, int startX, int startY)
	: Actor(IID_PLAYER, startX, startY, GraphObject::right, 0, world, "penelope") {
	m_landmine = 0;
	m_flamethrower = 0;
	m_vaccine = 0;
	m_infected = false;
}



