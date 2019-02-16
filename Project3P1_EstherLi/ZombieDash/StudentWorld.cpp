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
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				int level_x = j;
				int level_y = i;
				char ch = lev.getContentsOf(level_x, level_y);
				switch (ch) {
				case '#': actors[actors.size()] = new Wall(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y));
					break;
				case '@': player = new Penelope(this, (SPRITE_WIDTH * level_x), (SPRITE_HEIGHT * level_y));
					break;
				}
			}
		}

	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	decLives();
	return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}




