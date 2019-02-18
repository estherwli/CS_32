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
					actors.push_back(new Wall(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y)));
					break;
				case Level::player:
					player = new Penelope(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y));
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
	player->doSomething();
	for (int i = 0; i < actors.size(); i++) {
		if (!actors[i]->dead()) {
			actors[i]->doSomething();
			if (player->dead())
				return GWSTATUS_PLAYER_DIED;
			//IMPLEMENT LATER: IF PENELOPE COMPLETED CURRENT LEVEL
		}
	}
	//delete and remove dead game objects
	for (int i = 0; i < actors.size(); i++) {
		if (actors[i]->dead()) {
			delete actors[i];
			actors[i] = actors[actors.size() - 1];
			actors.pop_back();
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
	if (player != nullptr) //ensures consecutive calls to cleanUp won't have undefined behavior
		delete player;
	for (int i = actors.size() - 1; i >= 0; i--) {
		if (actors[i] != nullptr) {
			delete actors[i];
			actors.pop_back();
		}
	}
}

bool StudentWorld::blocked(int x, int y, int dir) { //parameters are coordinates of the location we're trying to move to
	Level lev(assetPath());
	string levelFile = FILENAME;
	Level::LoadResult result = lev.loadLevel(levelFile);

	//each Level coordinate represents a 16x16 box (SPRITE_WIDTH x SPRITE_HEIGHT)
	//the following if-statements get the bottom-leftmost coordinate of our destination box 
	if (dir == 0) //right
		while (x % SPRITE_WIDTH != 0)
			x += 4;
	if (dir == 180) //left
		while (x % SPRITE_WIDTH != 0)
			x -= 4;
	if (dir == 90) //up
		while (y % SPRITE_HEIGHT != 0)
			y += 4;
	if (dir == 270) //down
		while (y % SPRITE_HEIGHT != 0)
			y -= 4;

	Level::MazeEntry ge = lev.getContentsOf(x / SPRITE_WIDTH, y / SPRITE_HEIGHT); //division converts 256x256 to 16x16 
	switch (ge) {
	case Level::wall:
	case Level::citizen:
	case Level::dumb_zombie:
	case Level::smart_zombie:
		return true; 	//destination is blocked if there is a wall, citizen, or zombie
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
	stat << "  Level: " << getLevel() << "  Lives: " << player->lives() << "  Vaccines: " << player->vaccine() 
		<< "  Flames: " << player->flamethrower() << "  Mines: " << player->landmine() << "  Infected: " << player->nInfected();

	return score.str() + stat.str();
}






