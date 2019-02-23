#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

const double OVERLAP_DISTANCE = 100.0;

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
		cerr << "Cannot find " << levelFile << " data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
	else if (result == Level::load_success) {
		cerr << "Successfully loaded level" << endl;
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				int level_x = j;
				int level_y = i;
				Level::MazeEntry ge = lev.getContentsOf(level_x, level_y);
				switch (ge) {
				case Level::wall:
					m_actors.push_back(new Wall(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::player:
					m_player = new Penelope(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y));
					m_actors.push_back(m_player);
					break;
				case Level::exit:
					m_actors.push_back(new Exit(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::pit:
					m_actors.push_back(new Pit(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::dumb_zombie:
					m_actors.push_back(new DumbZombie(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				}
			}
		}

	}
	return GWSTATUS_PLAYER_DIED;
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
			if (m_player->dead())
				return GWSTATUS_PLAYER_DIED;
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

void StudentWorld::cleanUp()
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
//the actor trying to move to said destination 
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

bool StudentWorld::overlapped(int x1, int y1, int x2, int y2) {
	//gets the coordinates of the center of an object's bounding box 
	double myCenterX = x1 + (SPRITE_WIDTH / 2.0);
	double myCenterY = y1 + (SPRITE_HEIGHT / 2.0);

	//gets the coordinates of the center of an person's bounding box 
	double otherCenterX = x2 + SPRITE_WIDTH / 2.0;
	double otherCenterY = y2 + SPRITE_HEIGHT / 2.0;

	//checks if the euclidean distance between the two centers is close enough to overlap
	double deltaX = otherCenterX - myCenterX;
	double deltaY = otherCenterY - myCenterY;
	if (deltaX * deltaX + deltaY * deltaY <= OVERLAP_DISTANCE)
		return true;
	else
		return false;
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
	score.fill('0'); //width is set to 6, empty spaces are filled with '0'
	score << "Score: " << setw(6) << getScore();

	ostringstream stat;
	stat.setf(ios::fixed);
	stat << "  Level: " << getLevel() << "  Lives: " << m_player->lives() << "  Vacc: " << m_player->vaccine()
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
	if (x1 < 0 || x1 > VIEW_WIDTH || y1 < 0 || y1 > VIEW_HEIGHT)
		return false;
	vector<Actor*>::iterator it;
	it = m_actors.begin();
	while (it != m_actors.end()) {
		if (f(*it)) {
			int x2 = (*it)->getX();
			int y2 = (*it)->getY();
			if (overlapped(x1, y1, x2, y2))
				return true;
		}
		it++;
	}
	return false;
}

void StudentWorld::createValidProjectile(int x, int y, int dir, int amount, bool(*check)(Actor*), string projectileType) {
	int tempX = x;
	int tempY = y;
	for (int i = 1; i < amount + 1; i++) {
		if (dir == GraphObject::up)
			tempY = y + i * SPRITE_HEIGHT;
		else if (dir == GraphObject::down)
			tempY = y - i * SPRITE_HEIGHT;
		else if (dir == GraphObject::left)
			tempX = x - i * SPRITE_WIDTH;
		else if (dir == GraphObject::right)
			tempX = x + i * SPRITE_WIDTH;
		if (projectileType == "flame") {
			if (hasProperty(tempX, tempY, check)) //blocksFlame is the property
				return;
			m_actors.push_back(new Flame(this, tempX, tempY, dir));
		}
		else if (projectileType == "vomit") {
			if (hasProperty(tempX, tempY, check)) { //isPerson is the property
				m_actors.push_back(new Vomit(this, tempX, tempY, dir));
				playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}
}








