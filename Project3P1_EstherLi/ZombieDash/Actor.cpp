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
	m_person = false;
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

bool Actor::isPerson() const {
	return m_person;
}

void Actor::setDead() {
	m_dead = true;
}

void Actor::setBlockable() {
	m_blockable = true;
}

void Actor::setPerson() {
	m_person = true;
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
	setPerson();
}

Actor::ActorType Penelope::getType() {
	return t_penelope;
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

void Penelope::setInfect() {
	m_infected = true;
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
	//encountered an exit
	if (world()->foundSomething(this, t_exit))
		world()->setCompleted();
	//encountered a pit
	if (world()->foundSomething(this, t_pit)) {
		setDead();
		world()->playSound(SOUND_PLAYER_DIE);
		return;
	}
	//encountered a flame
	if (world()->foundSomething(this, t_flame)) {
		setDead();
		world()->playSound(SOUND_PLAYER_DIE);
		return;
	}
	//encountered zombie vomit
	if (world()->foundSomething(this, t_vomit))
		setInfect();

	double x = getX();
	double y = getY();
	int dir = getDirection();
	int ch;
	if (world()->getKey(ch)) {
		switch (ch) {
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (!world()->blocked(x - 4, y, t_wall))
				moveTo(x - 4, y);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (!world()->blocked(x + 4, y, t_wall))
				moveTo(x + 4, y);
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (!world()->blocked(x, y + 4, t_wall))
				moveTo(x, y + 4);
			break;
		case KEY_PRESS_DOWN:
			m_flamethrower = 3;
			setDirection(down);
			if (!world()->blocked(x, y - 4, t_wall))
				moveTo(x, y - 4);
			break;
		case KEY_PRESS_SPACE:
			if (flamethrower() >= 1) {
				m_flamethrower--;
				world()->playSound(SOUND_PLAYER_FIRE);
				switch (dir) {
				case up:
					createValidFlame(x, y, up);
					break;
				case down:
					createValidFlame(x, y, down);
					break;
				case left:
					createValidFlame(x, y, left);
					break;
				case right:
					createValidFlame(x, y, right);
					break;
				}
				break;
			}
		}
	}
	return;
}

void Penelope::createValidFlame(int x, int y, int dir) {
	int tempX = x;
	int tempY = y;
	for (int i = 1; i < 4; i++) {
		if (dir == up)
			tempY = y + i * SPRITE_HEIGHT;
		else if (dir == down)
			tempY = y - i * SPRITE_HEIGHT;
		else if (dir == left)
			tempX = x - i * SPRITE_WIDTH;
		else if (dir == right)
			tempX = x + i * SPRITE_WIDTH;
		if (world()->blocked(tempX, tempY, t_wall) || world()->blocked(tempX, tempY, t_exit))
			break;
		world()->createFlame(tempX, tempY, dir);
	}
}

//******************WALL******************
Wall::Wall(StudentWorld* world, int startX, int startY)
	:Actor(IID_WALL, startX, startY, GraphObject::right, 0, world) {
	setBlockable();
}

Actor::ActorType Wall::getType() {
	return t_wall;
}

void Wall::doSomething() {
	return;
}

//******************EXIT******************
Exit::Exit(StudentWorld* world, int startX, int startY)
	: Actor(IID_EXIT, startX, startY, GraphObject::right, 1, world) {
}

Actor::ActorType Exit::getType() {
	return t_exit;
}

void Exit::doSomething() {
	return;
}

//******************PIT******************
Pit::Pit(StudentWorld* world, int startX, int startY)
	: Actor(IID_PIT, startX, startY, GraphObject::right, 0, world) {
}

Actor::ActorType Pit::getType() {
	return t_pit;
}

void Pit::doSomething() {
	return;
}

//******************TIMEDACTOR******************
TimedActor::TimedActor(StudentWorld* world, int startX, int startY, int dir, int depth, int imageID)
	:Actor(imageID, startX, startY, dir, depth, world) {
	m_nTicks = 0;
}

void TimedActor::doSomething() {
	if (dead())
		return;
	else if (nTicks() == 2) {
		setDead();
		return;
	}
	addTicks();
}

int TimedActor::nTicks() {
	return m_nTicks;
}

void TimedActor::addTicks() {
	m_nTicks++;
}

//******************FLAME******************
Flame::Flame(StudentWorld* world, int startX, int startY, int dir)
	: TimedActor(world, startX, startY, dir, 0, IID_FLAME) {
}

Actor::ActorType Flame::getType() {
	return t_flame;
}

//******************VOMIT******************
Vomit::Vomit(StudentWorld* world, int startX, int startY, int dir)
	: TimedActor(world, startX, startY, dir, 0, IID_VOMIT) {
}

Actor::ActorType Vomit::getType() {
	return t_vomit;
}

//******************ZOMBIE******************
Zombie::Zombie(StudentWorld* world, int startX, int startY) 
: TimedActor(world, startX, startY, right, 0, IID_ZOMBIE) {
	m_movementPlan = 0;
}

void Zombie::doSomething() {
	if (dead())
		return;

}







