#include "GraphObject.h"
#include "Actor.h"
#include "StudentWorld.h"
#include <string>
using namespace std;

Actor::Actor(int imageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* world)
	:GraphObject(imageID, startX, startY, startDirection, depth) {
	if (startX < 0 || startX > VIEW_WIDTH - 1 || startY < 0 || startY > VIEW_HEIGHT - 1)
		cerr << "Invalid starting position.";
	else {
		m_world = world;
		m_dead = false;
		m_isActor = true;
		m_blocksMovement = false;
		m_blocksFlame = false;
		m_isHuman = false;
		m_isPenelope = false;
		m_isDumbZombie = false;
		m_isSmartZombie = false;
		m_isExit = false;
		m_isPit = false;
		m_isGoodie = false;
		m_isVaccineGoodie = false;
		m_isGasCanGoodie = false;
		m_isLandmineGoodie = false;
		m_isFlame = false;
		m_isVomit = false;
		m_isLandmine = false;
	}
}

StudentWorld* Actor::world() const {
	return m_world;
}

bool Actor::dead() const {
	return m_dead;
}

bool Actor::isActor(Actor *me) {
	return me->isActor;
}

bool Actor::blocksMovement(Actor *me) {
	return me->m_blocksMovement;
}

bool Actor::blocksFlame(Actor *me) {
	return me->m_blocksFlame;
}

bool Actor::isHuman(Actor *me) {
	return me->m_isHuman;
}

bool Actor::isPenelope(Actor *me) {
	return me->m_isPenelope;
}

bool Actor::isDumbZombie(Actor *me) {
	return me->m_isDumbZombie;
}

bool Actor::isSmartZombie(Actor *me) {
	return me->m_isSmartZombie;
}

bool Actor::isExit(Actor *me) {
	return me->m_isExit;
}

bool Actor::isPit(Actor *me) {
	return me->m_isPit;
}

bool Actor::isGoodie(Actor *me) {
	return me->m_isGoodie;
}

bool Actor::isVaccineGoodie(Actor *me) {
	return me->m_isVaccineGoodie;
}

bool Actor::isGasCanGoodie(Actor* me) {
	return me->m_isGasCanGoodie;
}

bool Actor::isLandmineGoodie(Actor* me) {
	return me->m_isLandmineGoodie;
}

bool Actor::isFlame(Actor *me) {
	return me->m_isFlame;
}

bool Actor::isVomit(Actor *me) {
	return me->m_isVomit;
}

bool Actor::isLandmine(Actor *me) {
	return me->m_isLandmine;
}

void Actor::setDead() {
	m_dead = true;
}

void Actor::setBlocksMovement() {
	m_blocksMovement = true;
}

void Actor::setBlocksFlame() {
	m_blocksFlame = true;
}

void Actor::setPerson() {
	m_isHuman = true;
}

void Actor::setPenelope() {
	m_isPenelope = true;
}

void Actor::setDumbZombie() {
	m_isDumbZombie = true;
}

void Actor::setSmartZombie() {
	m_isSmartZombie = true;
}

void Actor::setExit() {
	m_isExit = true;
}

void Actor::setPit() {
	m_isPit = true;
}

void Actor::setGoodie() {
	m_isGoodie = true;
}

void Actor::setVaccineGoodie() {
	m_isVaccineGoodie = true;
}

void Actor::setGasCanGoodie() {
	m_isGasCanGoodie = true;
}

void Actor::setLandmineGoodie() {
	m_isLandmineGoodie = true;
}

void Actor::setFlame() {
	m_isFlame = true;
}

void Actor::setVomit() {
	m_isVomit = true;
}

void Actor::setLandmine() {
	m_isLandmine = true;
}

//******************HUMAN******************
Human::Human(int imageID, StudentWorld* world, int startX, int startY)
	:Actor(imageID, startX, startY, right, 0, world) {
	setPerson();
	m_infected = false;
	m_nInfected = 0;
}

void Human::doSomething() {
	int x = getX();
	int y = getY();
	//encountered zombie vomit
	if (world()->foundSomething(x, y, &isVomit))
		setInfect(true);

}

bool Human::infected() const {
	return m_infected;
}

int Human::nInfected() const {
	return m_nInfected;
}

void Human::addInfect() {
	m_nInfected++;
}

void Human::setInfect(bool a) {
	m_infected = a;
}

void Human::clearInfect() {
	m_nInfected = 0;
}

//******************PENELOPE******************
Penelope::Penelope(StudentWorld* world, int startX, int startY)
	: Human(IID_PLAYER, world, startX, startY) {
	m_lives = 3;
	m_landmine = 0;
	m_flamethrower = 0;
	m_nVaccine = 0;
	setPerson();
	setPenelope();
	setBlocksMovement();
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
	return m_nVaccine;
}

void Penelope::addVaccine() {
	m_nVaccine++;
}

void Penelope::addFlamethrower() {
	m_flamethrower += 5;
}

void Penelope::addLandmine() {
	m_landmine += 2;
}

void Penelope::doSomething() {
	if (dead())
		return;
	Human::doSomething();
	if (infected()) {
		if (nInfected() == 500) {
			setDead();
			world()->playSound(SOUND_PLAYER_DIE);
			return;
		}
		else
			addInfect();
	}
	double x = getX();
	double y = getY();
	int dir = getDirection();

	//encountered an exit
	if (world()->foundSomething(x, y, &isExit))
		world()->setCompleted();
	//encountered a pit
	if (world()->foundSomething(x, y, &isPit)) {
		setDead();
		world()->playSound(SOUND_PLAYER_DIE);
		return;
	}
	//encountered a flame
	if (world()->foundSomething(x, y, &isFlame)) {
		setDead();
		world()->playSound(SOUND_PLAYER_DIE);
		return;
	}
	//encountered a vaccine goodie
	if (world()->foundSomething(x, y, &isVaccineGoodie))
		addVaccine();

	//encountered a gas can goodie
	if (world()->foundSomething(x, y, &isGasCanGoodie))
		addFlamethrower();

	//encountered a landmine goodie
	if (world()->foundSomething(x, y, &isLandmineGoodie))
		addLandmine();

	int ch;
	if (world()->getKey(ch)) {
		switch (ch) {
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (!world()->hasProperty(x - 4, y, &blocksMovement, this))
				moveTo(x - 4, y);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (!world()->hasProperty(x + 4, y, &blocksMovement, this))
				moveTo(x + 4, y);
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (!world()->hasProperty(x, y + 4, &blocksMovement, this))
				moveTo(x, y + 4);
			break;
		case KEY_PRESS_DOWN:
			m_flamethrower = 3;
			setDirection(down);
			if (!world()->hasProperty(x, y - 4, &blocksMovement, this))
				moveTo(x, y - 4);
			break;
		case KEY_PRESS_TAB:
			if (landmine() >= 1) {
				world()->createValidObject(x - SPRITE_WIDTH, y, right, 1, &blocksMovement, "landmine");
			}
		case KEY_PRESS_ENTER:
			if (vaccine() >= 1) {
				setInfect(false);
				clearInfect();
				m_nVaccine--;
			}
			break;
		case KEY_PRESS_SPACE:
			if (flamethrower() >= 1) {
				m_flamethrower--;
				world()->playSound(SOUND_PLAYER_FIRE);
				switch (dir) {
				case up:
					world()->createValidObject(x, y, up, 3, &blocksFlame, "flame");
					break;
				case down:
					world()->createValidObject(x, y, down, 3, &blocksFlame, "flame");
					break;
				case left:
					world()->createValidObject(x, y, left, 3, &blocksFlame, "flame");
					break;
				case right:
					world()->createValidObject(x, y, right, 3, &blocksFlame, "flame");
					break;
				}
			}
			break;
		}
	}
	return;
}

//******************WALL******************
Wall::Wall(StudentWorld* world, int startX, int startY)
	:Actor(IID_WALL, startX, startY, GraphObject::right, 0, world) {
	setBlocksMovement();
	setBlocksFlame();
}

void Wall::doSomething() {
	return;
}

//******************EXIT******************
Exit::Exit(StudentWorld* world, int startX, int startY)
	: Actor(IID_EXIT, startX, startY, GraphObject::right, 1, world) {
	setExit();
	setBlocksFlame();
}

void Exit::doSomething() {
	return;
}

//******************PIT******************
Pit::Pit(StudentWorld* world, int startX, int startY)
	: Actor(IID_PIT, startX, startY, GraphObject::right, 0, world) {
	setPit();
}

void Pit::doSomething() {
	return;
}


//******************LANDMINE******************
Landmine::Landmine(StudentWorld* world, int startX, int startY)
	:Actor(IID_LANDMINE, startX, startY, right, 1, world) {
	setLandmine();
	m_active = false;
	m_nSafetyTicks = 30;
}

void Landmine::doSomething() {
	if (dead())
		return;
	int x = getX();
	int y = getY();
	if (world()->foundSomething(x, y, &isFlame))
		m_active = true;
	if (!m_active) {
		if (m_nSafetyTicks != 0)
			m_nSafetyTicks--;
		if (m_nSafetyTicks == 0) {
			m_active = true;
			return;
		}
	}
	if (m_active) {
		setDead();
		world()->playSound(SOUND_LANDMINE_EXPLODE);
		int xLeft = getX() - SPRITE_WIDTH;
		int xRight = getX() + SPRITE_WIDTH;
		int yUp = getY();
		int yMid = getY() - SPRITE_HEIGHT;
		int yBottom = getY() - 2 * SPRITE_HEIGHT;
		world()->createValidObject(x, yUp, up, 1, &blocksFlame, "flame");
		world()->createValidObject(x, yMid, up, 1, &blocksFlame, "flame");
		world()->createValidObject(x, yBottom, up, 1, &blocksFlame, "flame");
		world()->createValidObject(xLeft, yUp, up, 1, &blocksFlame, "flame");
		world()->createValidObject(xLeft, yMid, up, 1, &blocksFlame, "flame");
		world()->createValidObject(xLeft, yBottom, up, 1, &blocksFlame, "flame");
		world()->createValidObject(xRight, yUp, up, 1, &blocksFlame, "flame");
		world()->createValidObject(xRight, yMid, up, 1, &blocksFlame, "flame");
		world()->createValidObject(xRight, yBottom, up, 1, &blocksFlame, "flame");
		world()->createValidObject(x, yMid, up, 1, &blocksFlame, "pit");
	}
}

//******************TIMEDACTOR******************
TimedActor::TimedActor(StudentWorld* world, int startX, int startY, int dir, int depth, int imageID)
	: Actor(imageID, startX, startY, dir, depth, world) {
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

//******************GOODIE******************
Goodie::Goodie(StudentWorld* world, int startX, int startY, int imageID)
	:Actor(imageID, startX, startY, right, 1, world) {
	setGoodie();
}

void Goodie::doSomething() {
	if (dead())
		return;
	if (world()->foundSomething(getX(), getY(), &isPenelope)) {
		world()->increaseScore(50);
		setDead();
		world()->playSound(SOUND_GOT_GOODIE);
	}
	if (world()->foundSomething(getX(), getY(), &isFlame))
		setDead();
}

//******************VACCINEGOODIE******************
VaccineGoodie::VaccineGoodie(StudentWorld* world, int startX, int startY)
	: Goodie(world, startX, startY, IID_VACCINE_GOODIE) {
	setVaccineGoodie();
}

//******************GASCANGOODIE******************
GasCanGoodie::GasCanGoodie(StudentWorld* world, int startX, int startY)
	: Goodie(world, startX, startY, IID_GAS_CAN_GOODIE) {
	setGasCanGoodie();
}

//******************LANDMINEGOODIE******************
LandmineGoodie::LandmineGoodie(StudentWorld* world, int startX, int startY)
	: Goodie(world, startX, startY, IID_LANDMINE_GOODIE) {
	setLandmineGoodie();
}

//******************FLAME******************
Flame::Flame(StudentWorld* world, int startX, int startY, int dir)
	: TimedActor(world, startX, startY, dir, 0, IID_FLAME) {
	setFlame();
}

//******************VOMIT******************
Vomit::Vomit(StudentWorld* world, int startX, int startY, int dir)
	: TimedActor(world, startX, startY, dir, 0, IID_VOMIT) {
	setVomit();
}

//******************ZOMBIE******************
Zombie::Zombie(StudentWorld* world, int startX, int startY)
	: TimedActor(world, startX, startY, right, 0, IID_ZOMBIE) {
	m_movementPlan = 0;
	setBlocksMovement();
}

int Zombie::movementPlan() {
	return m_movementPlan;
}

void Zombie::setMovementPlan(int i) {
	m_movementPlan = i;
}

void Zombie::decreaseMovementPlan() {
	m_movementPlan--;
}

void Zombie::doSomething() {
	addTicks();
	if (nTicks() % 2 == 0) //do nothing every other tick
		return;
	int x = getX();
	int y = getY();
	//encountered a pit or a flame
	if (world()->foundSomething(x, y, &isPit) || world()->foundSomething(x, y, &isFlame)) {
		setDead();
		world()->playSound(SOUND_ZOMBIE_DIE);
		world()->increaseScore(1000);
		return;
	}

	move(this);

	//if zombie is not dead or idle during this tick
	checkVomit(this);
}

void Zombie::move(Zombie* me) {
	int dir = getDirection();
	switch (dir) {
	case up:
		tryToMove(this, 0, 1);
		break;
	case down:
		tryToMove(this, 0, -1);
		break;
	case left:
		tryToMove(this, -1, 0);
		break;
	case right:
		tryToMove(this, 1, 0);
		break;
	}
}

int Zombie::pickDirection() {
	int randomDir = randInt(1, 4);
	switch (randomDir) {
	case 1:
		return up;
		break;
	case 2:
		return down;
		break;
	case 3:
		return left;
	case 4:
		return right;
	}
}

void Zombie::tryToMove(Zombie* me, int deltaX, int deltaY) {
	int x = me->getX();
	int y = me->getY();
	if (!world()->hasProperty(x + deltaX, y + deltaY, &blocksMovement, me)) {
		me->moveTo(x + deltaX, y + deltaY);
		me->decreaseMovementPlan();
	}
	else
		me->setMovementPlan(0);
}

void Zombie::checkVomit(Actor* me) {
	int dir = me->getDirection();
	int tempX = me->getX();
	int tempY = me->getY();
	switch (dir) { //computes potential coordinates for vomit
	case up:
		tempY += SPRITE_HEIGHT;
		break;
	case down:
		tempY -= SPRITE_HEIGHT;
		break;
	case left:
		tempX -= SPRITE_WIDTH;
		break;
	case right:
		tempX += SPRITE_WIDTH;
		break;
	}
	if (world()->foundSomething(tempX, tempY, &isHuman)) { //if vomit will be close enough to a person
		int num = randInt(1, 3);
		if (num == 1) { //zombie will vomit 1/3 of the time
			world()->createValidObject(getX(), getY(), dir, 1, &isHuman, "vomit");
			return;
		}
	}
}

//******************DUMBZOMBIE******************
DumbZombie::DumbZombie(StudentWorld* world, int startX, int startY)
	: Zombie(world, startX, startY) {
	setDumbZombie();
	m_hasVaccine = true;
	int num = (randInt(1, 10));
	if (num == 1)
		m_hasVaccine = true; //1 out of 10 zombies carry a vaccine
}

DumbZombie::~DumbZombie() {
	if (m_hasVaccine) {
		int y = getY();
		int x = getX();
		int dir = pickDirection();
		world()->createValidObject(x, y, dir, 1, &isActor, "vaccine");
	}
}

void DumbZombie::doSomething() {
	if (dead())
		return;
	if (movementPlan() == 0) {
		setMovementPlan(randInt(3, 10));
		setDirection(pickDirection());
	}
	Zombie::doSomething();
}

//******************SMARTZOMBIE******************
SmartZombie::SmartZombie(StudentWorld* world, int startX, int startY)
	:Zombie(world, startX, startY) {
	setSmartZombie();
}

void SmartZombie::doSomething() {
	if (dead())
		return;
	int x = getX();
	int y = getY();
	if (movementPlan() == 0) {
		setMovementPlan(randInt(3, 10));
		if (world()->findClosestHuman(x, y) == -1)
			setDirection(pickDirection());
		else
			setDirection(world()->findClosestHuman(x, y));
	}
	Zombie::doSomething();
}









