#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

const string FILENAME = "level01.txt";

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
	Level lev(assetPath());
	string levelFile = FILENAME;
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
				case Level::m_player:
					m_player = new Penelope(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y));
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
	m_player->doSomething();
	for (int i = 0; i < m_actors.size(); i++) {
		if (!m_actors[i]->dead()) {
			m_actors[i]->doSomething();
			if (m_player->dead())
				return GWSTATUS_PLAYER_DIED;
			//IMPLEMENT LATER: IF PENELOPE COMPLETED CURRENT LEVEL
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
	if (m_player != nullptr) //ensures consecutive calls to cleanUp won't have undefined behavior
		delete m_player;
	for (int i = m_actors.size() - 1; i >= 0; i--) {
		if (m_actors[i] != nullptr) {
			delete m_actors[i];
			m_actors.pop_back();
		}
	}
}

bool StudentWorld::blocked(int x, int y) { //parameters are coordinates of the location we're trying to move to

	//gets the dimensions of player's bounding box
	int myX = x + SPRITE_WIDTH - 1;
	int myY = y + SPRITE_HEIGHT - 1;

	vector<Actor*>::iterator it;
	it = m_actors.begin();
	while (it != m_actors.end()) {
		//gets the dimensions of actor's bounding box
		int xLowerBound = (*it)->getX(); 
		int xUpperBound = xLowerBound + SPRITE_WIDTH - 1;
		int yLowerBound = (*it)->getY();
		int yUpperBound = yLowerBound + SPRITE_HEIGHT - 1;
		if ((*it)->name() == "wall") {
			//checks if actor's bounding box will intersect with an obstacle's bounding box
			if (x <= xUpperBound && x >= xLowerBound && y <= yUpperBound && y >= yLowerBound) //checks lower left corner
				return true;
			else if (myX <= xUpperBound && myX >= xLowerBound && myY <= yUpperBound && myY >= yLowerBound) //checks upper right corner
				return true;
			else if (myX <= xUpperBound && myX >= xLowerBound && y <= yUpperBound && y >= yLowerBound) //checks lower right corner
				return true;
			else if (x <= xUpperBound && x >= xLowerBound && myY <= yUpperBound && myY >= yLowerBound) //checks upper left corner
				return true;
		}
		it++;
	}
	return false;




}

string StudentWorld::stat() {
	ostringstream score;
	score.setf(ios::fixed);
	score.fill('0'); //width is set to 6, empty spaces are filled with '0'
	score << "Score: " << setw(6) << getScore();


	ostringstream stat;
	stat.setf(ios::fixed);
	stat << "  Level: " << getLevel() << "  Lives: " << m_player->lives() << "  Vaccines: " << m_player->vaccine()
		<< "  Flames: " << m_player->flamethrower() << "  Mines: " << m_player->landmine() << "  Infected: " << m_player->nInfected();

	return score.str() + stat.str();
}






