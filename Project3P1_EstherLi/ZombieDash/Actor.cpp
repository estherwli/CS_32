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
		m_isCitizen = false;
		m_isZombie = false;
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

bool Actor::isCitizen(Actor *me) {
	return me->m_isCitizen;
}

bool Actor::isZombie(Actor *me) {
	return me->m_isZombie;
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

void Actor::setHuman() {
	m_isHuman = true;
}

void Actor::setPenelope() {
	m_isPenelope = true;
}

void Actor::setCitizen() {
	m_isCitizen = true;
}

void Actor::setZombie() {
	m_isZombie = true;
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
	:TimedActor(world, startX, startY, right, 0, imageID) {
	setHuman();
	setBlocksMovement();
	m_infected = false;
	m_nInfected = 0;
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
	m_landmine = 0;
	m_flamethrower = 0;
	m_nVaccine = 0;
	setPenelope();
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
	if (world()->foundSomething(getX(), getY(), &isVomit)) 
		setInfect(true);
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

	//encountered an exit and no citizens left 
	if (world()->foundSomething(x, y, &isExit) && !world()->anyCitizensLeft()) {
		world()->playSound(SOUND_LEVEL_FINISHED);
		world()->setCompleted();
	}
	//encountered a pit or a flame
	if (world()->foundSomething(x, y, &isPit) || world()->foundSomething(x, y, &isFlame)) {
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
		case KEY_PRESS_LEFT: //if possible, move 4 pixels left
			setDirection(left);
			if (!world()->hasProperty(x - 4, y, &blocksMovement, this))
				moveTo(x - 4, y);
			break;
		case KEY_PRESS_RIGHT: //if possible, move 4 pixels right
			setDirection(right);
			if (!world()->hasProperty(x + 4, y, &blocksMovement, this))
				moveTo(x + 4, y);
			break;
		case KEY_PRESS_UP: //if possible, move 4 pixels up
			setDirection(up);
			if (!world()->hasProperty(x, y + 4, &blocksMovement, this))
				moveTo(x, y + 4);
			break;
		case KEY_PRESS_DOWN: //if possible, move 4 pixels down
			setDirection(down);
			if (!world()->hasProperty(x, y - 4, &blocksMovement, this))
				moveTo(x, y - 4);
			break;
		case KEY_PRESS_TAB: //if i have at least 1 landmine, create a landmine exactly where i am
			if (landmine() >= 1)
				world()->createValidObject(x - SPRITE_WIDTH, y, right, 1, &blocksMovement, "landmine");
			break;
		case KEY_PRESS_ENTER: //if i have at least 1 vaccine, clear my infection
			if (vaccine() >= 1) {
				setInfect(false);
				clearInfect();
				m_nVaccine--;
			}
			break;
		case KEY_PRESS_SPACE: //if i have at least 1 flamethrower, create 3 flames (if possible) in my current direction
			if (flamethrower() >= 1) {
				m_flamethrower--;
				world()->playSound(SOUND_PLAYER_FIRE);
				world()->createValidObject(x, y, dir, 3, &blocksFlame, "flame");
			}
			break;
		}
	}
	return;
}

//******************CITIZEN******************
Citizen::Citizen(StudentWorld *world, int startX, int startY)
	:Human(IID_CITIZEN, world, startX, startY) {
	setCitizen();
}

void Citizen::doSomething() {
	if (dead())
		return;
	int x = getX();
	int y = getY();
	if (infected()) {
		if (nInfected() == 500) { //turns into a Zombie
			setDead();
			world()->playSound(SOUND_ZOMBIE_BORN);
			world()->increaseScore(-1000);
			int randZombie = randInt(1, 10);
			if (randZombie <= 3) //30% chance that former citizen turned into smart zombie, 70% for dumb zombie
				world()->createValidObject(x - SPRITE_WIDTH, y, right, 1, &blocksMovement, "smartzombie");
			else
				world()->createValidObject(x - SPRITE_WIDTH, y, right, 1, &blocksMovement, "dumbzombie");
			return;
		}
		else
			addInfect(); //infected but not yet a Zombie
	}
	if (world()->foundSomething(x, y, &isVomit)) {
		world()->playSound(SOUND_CITIZEN_INFECTED);
		setInfect(true);
	}
	//encountered an exit
	if (world()->foundSomething(x, y, &isExit)) {
		world()->increaseScore(500);
		setDead();
		world()->playSound(SOUND_CITIZEN_SAVED);
		return;
	}
	//encountered a pit or a flame
	if (world()->foundSomething(x, y, &isPit) || world()->foundSomething(x, y, &isFlame)) {
		setDead();
		world()->playSound(SOUND_CITIZEN_DIE);
		world()->increaseScore(-1000);
		return;
	}

	addTicks();
	if (nTicks() % 2 == 0) //do nothing every other tick
		return;

	int tryDir, otherDir;
	double dist_p, dist_z;
	int direction_p = world()->findClosestHumanOrZombie(x, y, dist_p, &isPenelope, "citizen"); //gets direction to move closer to Penelope
	int direction_z = world()->findClosestHumanOrZombie(x, y, dist_z, &isZombie); //gets direction for closest Zombie
	if (direction_p != -1 && dist_p < dist_z) { //if Penelope is <= 80 pixels away and closer than the closest Zombie
		int num = randInt(1, 2);
		switch (direction_p) {
		case (StudentWorld::RIGHT_UP): //Penelope is to my upper right
			if (num == 1) {
				tryDir = right;
				otherDir = up;
			}
			else {
				tryDir = up;
				otherDir = right;
			}
			break;
		case (StudentWorld::RIGHT_DOWN): //Penelope is to my lower right
			if (num == 1) {
				tryDir = right;
				otherDir = down;
			}
			else {
				tryDir = down;
				otherDir = right;
			}
			break;
		case (StudentWorld::LEFT_UP): //Penelope is to my upper left
			if (num == 1) {
				tryDir = left;
				otherDir = up;
			}
			else {
				tryDir = up;
				otherDir = left;
			}
			break;
		case (StudentWorld::LEFT_DOWN): //Penelope is to my lower left
			if (num == 1) {
				tryDir = left;
				otherDir = down;
			}
			else {
				tryDir = down;
				otherDir = left;
			}
			break;
		case up:
			tryDir = otherDir = up;
			break;
		case down:
			tryDir = otherDir = down;
			break;
		case left:
			tryDir = otherDir = left;
			break;
		case right:
			tryDir = otherDir = right;
			break;
		}
		if (tryToMove(this, tryDir)) //if i'm not on the same row or column as Penelope, first try the randomly chosen direction
			return;
		else if (tryToMove(this, otherDir)) //if randomly chosen direction is blocked, try the other direction 
			return;
	}
	if (direction_z != -1) { //if there is a Zombie within 80 pixels from me
		int newDir = -1;
		farthestFromZombie(newDir, dist_z, x, y); //try to find a direction to get farther away from all Zombies
		if (newDir != -1)
			tryToMove(this, newDir);
	}
	return;
}

bool Citizen::tryToMove(Actor* me, int tempDir) {
	int x = me->getX();
	int y = me->getY();
	switch (tempDir) {
	case right:
		if (!world()->hasProperty(x + 2, y, &blocksMovement, this)) {
			setDirection(tempDir);
			moveTo(x + 2, y);
			return true;
		}
		break;
	case left:
		if (!world()->hasProperty(x - 2, y, &blocksMovement, this)) {
			setDirection(tempDir);
			moveTo(x - 2, y);
			return true;
		}
		break;
	case up:
		if (!world()->hasProperty(x, y + 2, &blocksMovement, this)) {
			setDirection(tempDir);
			moveTo(x, y + 2);
			return true;
		}
		break;
	case down:
		if (!world()->hasProperty(x, y - 2, &blocksMovement, this)) {
			setDirection(tempDir);
			moveTo(x, y - 2);
			return true;
		}
		break;
	}
	return false;
}

void Citizen::farthestFromZombie(int& newDir, int dist_z, int x, int y) {
	double farthest = dist_z;
	double tryLeft, tryRight, tryUp, tryDown;
	if (!world()->hasProperty(x + 2, y, &blocksMovement, this)) {
		world()->findClosestHumanOrZombie(x + 2, y, tryRight, &isZombie);
		if (tryRight > farthest) {
			farthest = tryRight;
			newDir = right;
		}
	}
	if (!world()->hasProperty(x - 2, y, &blocksMovement, this)) {
		world()->findClosestHumanOrZombie(x - 2, y, tryLeft, &isZombie);
		if (tryLeft > farthest) {
			farthest = tryLeft;
			newDir = left;
		}
	}
	if (!world()->hasProperty(x, y + 2, &blocksMovement, this)) {
		world()->findClosestHumanOrZombie(x, y + 2, tryUp, &isZombie);
		if (tryUp > farthest) {
			farthest = tryUp;
			newDir = up;
		}
	}
	if (!world()->hasProperty(x, y - 2, &blocksMovement, this)) {
		world()->findClosestHumanOrZombie(x, y - 2, tryDown, &isZombie);
		if (tryDown > farthest) {
			farthest = tryDown;
			newDir = down;
		}
	}
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
	if (!m_active) {
		if (m_nSafetyTicks != 0)
			m_nSafetyTicks--;
		if (m_nSafetyTicks == 0) {
			m_active = true;
			return;
		}
	}
	if (m_active && (world()->foundSomething(x, y, &isHuman) || world()->foundSomething(x, y, &isZombie) ||
		world()->foundSomething(x, y, &isFlame))) {
		setDead();
		world()->playSound(SOUND_LANDMINE_EXPLODE);
		int xLeft = getX() - SPRITE_WIDTH;
		int xRight = getX() + SPRITE_WIDTH;
		int yUp = getY();
		int yMid = getY() - SPRITE_HEIGHT;
		int yBottom = getY() - 2 * SPRITE_HEIGHT;
		world()->createValidObject(x, yMid, up, 1, &blocksFlame, "flame"); //flame in same location as landmine
		world()->createValidObject(x, yUp, up, 1, &blocksFlame, "flame"); //north
		world()->createValidObject(xRight, yUp, up, 1, &blocksFlame, "flame"); //northeast
		world()->createValidObject(xRight, yMid, up, 1, &blocksFlame, "flame"); //east
		world()->createValidObject(xRight, yBottom, up, 1, &blocksFlame, "flame"); //southeast
		world()->createValidObject(x, yBottom, up, 1, &blocksFlame, "flame"); //south
		world()->createValidObject(xLeft, yBottom, up, 1, &blocksFlame, "flame"); //southwest
		world()->createValidObject(xLeft, yMid, up, 1, &blocksFlame, "flame"); //west
		world()->createValidObject(xLeft, yUp, up, 1, &blocksFlame, "flame"); //northwest
		world()->createValidObject(x, yMid, up, 1, &blocksFlame, "pit"); //pit in same location as landmine
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
	setZombie();
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
	case 2:
		return down;
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
	m_hasVaccine = false;
	int num = (randInt(1, 10));
	if (num == 1)
		m_hasVaccine = true; //1 out of 10 zombies carry a vaccine
}

void DumbZombie::doSomething() {
	if (dead())
		return;
	//encountered a pit or a flame
	if (world()->foundSomething(getX(), getY(), &isPit) || world()->foundSomething(getX(), getY(), &isFlame)) {
		setDead();
		world()->playSound(SOUND_ZOMBIE_DIE);
		world()->increaseScore(1000);
		if (m_hasVaccine) {
			int dir = pickDirection();
			world()->createValidObject(getX(), getY(), dir, 1, &isActor, "vaccine");
		}
		return;
	}
	addTicks();
	if (nTicks() % 2 == 0) //do nothing every other tick
		return;
	checkVomit(this);
	if (movementPlan() == 0) {
		setMovementPlan(randInt(3, 10));
		setDirection(pickDirection());
	}
	move(this);
}

//******************SMARTZOMBIE******************
SmartZombie::SmartZombie(StudentWorld* world, int startX, int startY)
	:Zombie(world, startX, startY) {
	setSmartZombie();
}

void SmartZombie::doSomething() {
	if (dead())
		return;
	//encountered a pit or a flame
	if (world()->foundSomething(getX(), getY(), &isPit) || world()->foundSomething(getX(), getY(), &isFlame)) {
		setDead();
		world()->playSound(SOUND_ZOMBIE_DIE);
		world()->increaseScore(2000);
		return;
	}
	addTicks();
	if (nTicks() % 2 == 0) //do nothing every other tick
		return;
	checkVomit(this);
	double dummy;
	if (movementPlan() == 0) {
		setMovementPlan(randInt(3, 10));
		if (world()->findClosestHumanOrZombie(getX(), getY(), dummy, &isHuman) == -1)
			setDirection(pickDirection());
		else
			setDirection(world()->findClosestHumanOrZombie(getX(), getY(), dummy, &isHuman));
	}
	move(this);
}









