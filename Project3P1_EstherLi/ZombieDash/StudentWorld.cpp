#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

const double OVERLAP_DISTANCE_SQUARED = 100.0;
const double CLOSE_HUMAN_DISTANCE_SQUARED = 6400.0;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
	: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld() {
	cleanUp();
}

int StudentWorld::init()
{
	m_completed = false; //level has not been completed yet
	Level lev(assetPath());
	string levelFile = level();
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found)
		return GWSTATUS_PLAYER_WON;
	else if (result == Level::load_fail_bad_format)
		return GWSTATUS_LEVEL_ERROR;
	else if (result == Level::load_success) {
		for (int i = 0; i < LEVEL_HEIGHT; i++) { //iterate through the level file 
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				int level_x = j;
				int level_y = i;
				Level::MazeEntry ge = lev.getContentsOf(level_x, level_y);
				switch (ge) { //construct appropriate Actor objects based on the level file
				case Level::wall:
					m_actors.push_back(new Wall(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::pit:
					m_actors.push_back(new Pit(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::player:
					m_player = new Penelope(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y));
					m_actors.push_back(m_player);
					break;
				case Level::exit:
					m_actors.push_back(new Exit(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::dumb_zombie:
					m_actors.push_back(new DumbZombie(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::smart_zombie:
					m_actors.push_back(new SmartZombie(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::vaccine_goodie:
					m_actors.push_back(new VaccineGoodie(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::gas_can_goodie:
					m_actors.push_back(new GasCanGoodie(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::landmine_goodie:
					m_actors.push_back(new LandmineGoodie(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::citizen:
					m_actors.push_back(new Citizen(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				default:
					break;
				}
			}
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	//give actor a chance to doSomething()
	if (m_player->dead())
		return GWSTATUS_PLAYER_DIED;
	m_player->doSomething();
	for (int i = 0; i < m_actors.size(); i++) {
		if (!m_actors[i]->dead()) {
			m_actors[i]->doSomething();
			if (m_player->dead()) { //check if Penelope died after every Actor's doSomething is called
				decLives();
				return GWSTATUS_PLAYER_DIED;
			}
			if (completed())
				return GWSTATUS_FINISHED_LEVEL;
		}
	}
	//delete and remove dead game objects
	for (int i = 0; i < m_actors.size(); i++) {
		if (m_actors[i]->dead()) {
			delete m_actors[i];
			m_actors[i] = m_actors[m_actors.size() - 1];
			m_actors.pop_back();
			i--;
		}
	}
	//update game status line
	setGameStatText(stat());

	//Penelope hasn't completed level and hasn't died
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() //removes all Actors that are dead
{
	for (int i = m_actors.size() - 1; i >= 0; i--) {
		if (m_actors[i] != nullptr) {
			delete m_actors[i];
			m_actors.pop_back();
		}
	}
}

//parameters:
//coordinates of destination 
//an actor property (ex. blocksMovement)
//the actor trying to move to said destination (to prevent self-blocking)
bool StudentWorld::hasProperty(int x, int y, bool(*f)(Actor*), Actor *me) {
	//gets the coordinates of person's bounding box 
	int x2 = x + SPRITE_WIDTH - 1;
	int y2 = y + SPRITE_HEIGHT - 1;

	vector<Actor*>::iterator it;
	it = m_actors.begin();
	while (it != m_actors.end()) {
		if (*it != me && f(*it)) {
			//gets the coordinates of obstacle's bounding box 
			int xLowerBound = (*it)->getX();
			int xUpperBound = xLowerBound + SPRITE_WIDTH - 1;
			int yLowerBound = (*it)->getY();
			int yUpperBound = yLowerBound + SPRITE_HEIGHT - 1;
			//checks if any part of our bounding box will intersect with the object of interest's bounding box
			if (x <= xUpperBound && x >= xLowerBound && y <= yUpperBound && y >= yLowerBound) //checks lower left corner
				return true;
			else if (x2 <= xUpperBound && x2 >= xLowerBound && y2 <= yUpperBound && y2 >= yLowerBound) //checks upper right corner
				return true;
			else if (x2 <= xUpperBound && x2 >= xLowerBound && y <= yUpperBound && y >= yLowerBound) //checks lower right corner
				return true;
			else if (x <= xUpperBound && x >= xLowerBound && y2 <= yUpperBound && y2 >= yLowerBound) //checks upper left corner
				return true;
		}
		it++;
	}
	return false; //our bounding box does not intersect with any object of interest's bounding box
}

bool StudentWorld::completed() const {
	return m_completed;
}

void StudentWorld::setCompleted() {
	m_completed = true;
}

string StudentWorld::stat() const {
	ostringstream score;
	score.setf(ios::fixed);
	if (getScore() >= 0) {
		score.fill('0'); //width is set to 6, empty spaces are filled with '0'
		score << "Score: " << setw(6) << getScore();
	}
	else {
		score.fill('0');
		score << "Score: -" << setw(5) << (-1 * getScore()); //when there is a negative sign, width of number is set to 5
	}
	ostringstream stat;
	stat.setf(ios::fixed);
	stat << "  Level: " << getLevel() << "  Lives: " << getLives() << "  Vaccines: " << m_player->vaccine()
		<< "  Flames: " << m_player->flamethrower() << "  Mines: " << m_player->landmine() << "  Infected: " << m_player->nInfected();

	return score.str() + stat.str();
}

string StudentWorld::level() {
	ostringstream nLevel;
	nLevel.setf(ios::fixed);
	nLevel.fill('0');
	nLevel << setw(2) << getLevel();

	ostringstream level;
	level.setf(ios::fixed);
	level << "level" << nLevel.str() << ".txt";
	return level.str();
}

bool StudentWorld::foundSomething(int x1, int y1, bool(*f)(Actor*)) {
	vector<Actor*>::iterator it;
	it = m_actors.begin();
	while (it != m_actors.end()) { //iterate through m_actors vector to find if any appropriate Actors overlap with (x1, y1)
		if (f(*it)) {
			int x2 = (*it)->getX();
			int y2 = (*it)->getY();
			if (euclideanDistanceSq(x1, y1, x2, y2) <= OVERLAP_DISTANCE_SQUARED)
				return true;
		}
		it++;
	}
	return false;
}

void StudentWorld::createValidObject(int x, int y, int dir, int amount, bool(*check)(Actor*), string projectileType) {
	int tempX = x;
	int tempY = y;
	for (int i = 1; i < amount + 1; i++) { //determines how many and where to create the new object
		if (dir == GraphObject::up)
			tempY = y + i * SPRITE_HEIGHT;
		else if (dir == GraphObject::down)
			tempY = y - i * SPRITE_HEIGHT;
		else if (dir == GraphObject::left)
			tempX = x - i * SPRITE_WIDTH;
		else if (dir == GraphObject::right)
			tempX = x + i * SPRITE_WIDTH;
		if (projectileType == "flame") {
			if (foundSomething(tempX, tempY, check)) //blocksFlame is the property we want to check
				return;
			m_actors.push_back(new Flame(this, tempX, tempY, dir));
		}
		else if (projectileType == "vomit") {
			if (foundSomething(tempX, tempY, check)) { //isHuman is the property we want to check
				m_actors.push_back(new Vomit(this, tempX, tempY, dir));
				playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
		else if (projectileType == "landmine") {
			m_actors.push_back(new Landmine(this, tempX, tempY));
			return;
		}
		else if (projectileType == "pit") {
			m_actors.push_back(new Pit(this, tempX, tempY));
			return;
		}
		else if (projectileType == "vaccine") {
			if (!foundSomething(tempX, tempY, check))
				m_actors.push_back(new VaccineGoodie(this, tempX, tempY));
			return;
		}
		else if (projectileType == "smartzombie") {
				m_actors.push_back(new SmartZombie(this, tempX, tempY));
			return;
		}
		else if (projectileType == "dumbzombie") {
				m_actors.push_back(new DumbZombie(this, tempX, tempY));
			return;
		}
	}
}

int StudentWorld::findClosestHumanOrZombie(int x1, int y1, double& distanceSq, bool(*f)(Actor*), string str) {
	double distClosest = VIEW_HEIGHT * VIEW_HEIGHT + VIEW_WIDTH * VIEW_WIDTH; //all actors must be within this distance from me
	double distCurrent = 0;
	int xCurrent, yCurrent;
	int dirClosest = -1; //returns -1 if no human or zombie is close enough
	vector<Actor*>::iterator it = m_actors.begin();
	while (it != m_actors.end()) {
		if (f(*it)) {
			distCurrent = euclideanDistanceSq(x1, y1, (*it)->getX(), (*it)->getY());
			if (distCurrent < distClosest) {  //found a closer human or zombie
				distClosest = distCurrent;
				xCurrent = (*it)->getX();
				yCurrent = (*it)->getY();
			}
		}
		it++;
	}
	if (distClosest <= CLOSE_HUMAN_DISTANCE_SQUARED) { //only returns a valid direction if human or zombie is close enough
		int num = randInt(1, 2);
		if (xCurrent == x1 && yCurrent < y1) //closest human or zombie is below me
			dirClosest = GraphObject::down;
		else if (xCurrent == x1 && yCurrent > y1) //closest human or zombie is above me
			dirClosest = GraphObject::up;
		else if (xCurrent < x1 && yCurrent == y1) //closest human or zombie is to the left of me
			dirClosest = GraphObject::left;
		else if (xCurrent > x1 && yCurrent == y1) //closest human or zombie is to the right of me
			dirClosest = GraphObject::right;
		else if (xCurrent > x1 && yCurrent > y1) { //closest human or zombie is to the upper-right of me
			if (str == "citizen")
				return RIGHT_UP;
			if (num == 1)
				dirClosest = GraphObject::up;
			else
				dirClosest = GraphObject::right;
		}
		else if (xCurrent > x1 && yCurrent < y1) { //closest human or zombie is to the lower-right of me
			if (str == "citizen")
				return RIGHT_DOWN;
			if (num == 1)
				dirClosest = GraphObject::down;
			else
				dirClosest = GraphObject::right;
		}
		else if (xCurrent < x1 && yCurrent < y1) { //closest human or zombie is to the lower-left of zombie
			if (str == "citizen")
				return LEFT_DOWN;
			if (num == 1)
				dirClosest = GraphObject::down;
			else
				dirClosest = GraphObject::left;
		}
		else if (xCurrent < x1 && yCurrent > y1) { //closest human or zombie is to the upper-left of zombie
			if (str == "citizen")
				return LEFT_UP;
			if (num == 1)
				dirClosest = GraphObject::up;
			else
				dirClosest = GraphObject::left;
		}
	}
	distanceSq = distClosest; //sets distanceSq as distance to closest actor, even if dirClosest is still -1
	return dirClosest;
}

double StudentWorld::euclideanDistanceSq(int x1, int y1, int x2, int y2) {
	//gets the coordinates of the center of an object's bounding box 
	double myCenterX = x1 + (SPRITE_WIDTH / 2.0);
	double myCenterY = y1 + (SPRITE_HEIGHT / 2.0);

	//gets the coordinates of the center of an person's bounding box 
	double otherCenterX = x2 + (SPRITE_WIDTH / 2.0);
	double otherCenterY = y2 + (SPRITE_HEIGHT / 2.0);

	//checks if the euclidean distance between the two centers is close enough to overlap
	double deltaX = otherCenterX - myCenterX;
	double deltaY = otherCenterY - myCenterY;

	return deltaX * deltaX + deltaY * deltaY;
}

bool StudentWorld::anyCitizensLeft() {
	vector<Actor*>::iterator it = m_actors.begin();
	while (it != m_actors.end()) {
		if (Actor::isCitizen(*it))
			return true; //there is at least one Citizen left
		it++;
	}
	return false;
}








