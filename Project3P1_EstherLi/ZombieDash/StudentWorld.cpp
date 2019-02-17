#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
	: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
	Level lev(assetPath());
	string levelFile = "level01.txt";
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
			actors[i] = actors[actors.size()];
			actors.pop_back();
			i--;
		}
	}
	//update game status line


	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

bool StudentWorld::blocked(int x, int y, int dir) { //parameters are coordinates of the location we're trying to move to
	Level lev(assetPath());
	string levelFile = "level01.txt";
	Level::LoadResult result = lev.loadLevel(levelFile);

	if (dir == 0) //right
		while (x % SPRITE_WIDTH != 0)
			x+=4;
	if (dir == 180) //left
		while (x % SPRITE_WIDTH != 0)
			x-=4;
	if (dir == 90) //up
		while (y % SPRITE_HEIGHT != 0)
			y+=4;
	if (dir == 270) //down
		while (y % SPRITE_HEIGHT != 0)
			y-=4;

	//if we're trying to move to a location with a wall, citizen, or zombie
	Level::MazeEntry ge = lev.getContentsOf(x / SPRITE_WIDTH, y / SPRITE_HEIGHT);
	switch (ge) {
	case Level::wall:
	case Level::citizen:
	case Level::dumb_zombie:
	case Level::smart_zombie:
		return true;
	}
	Level::MazeEntry ga = lev.getContentsOf(x, y);
	switch (ga) {
	case Level::wall:
	case Level::citizen:
	case Level::dumb_zombie:
	case Level::smart_zombie:
		return true;
	}
	return false;
}






