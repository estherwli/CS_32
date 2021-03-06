#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	queue<Coord> coordQueue;		// declare a queue of Coords
	Coord start(sr, sc);
	coordQueue.push(start);
	maze[sr][sc] = 'A';				//mark start point as encountered
	while (!coordQueue.empty()) {
		Coord current = coordQueue.front();
		coordQueue.pop();
		if (current.r() == er && current.c() == ec)			//we reached the end point
			return true;
		if (current.r() < nRows - 1 && maze[current.r() + 1][current.c()] == '.') {	//if south is not a wall and has not been encountered
			Coord south(current.r() + 1, current.c());	//create new coordinate for south
			coordQueue.push(south);	//add south coordinate to queue
			maze[current.r() + 1][current.c()] = 'A'; //mark as encountered
		}
		if (current.c() > 0 && maze[current.r()][current.c() - 1] == '.') {
			Coord west(current.r(), current.c() - 1);
			coordQueue.push(west);
			maze[current.r()][current.c() - 1] = 'A';
		}
		if (current.r() > 0 && maze[current.r() - 1][current.c()] == '.') {
			Coord north(current.r() - 1, current.c());
			coordQueue.push(north);
			maze[current.r() - 1][current.c()] = 'A';
		}
		if (current.c() < nCols - 1 && maze[current.r()][current.c() + 1] == '.') {
			Coord east(current.r(), current.c() + 1);
			coordQueue.push(east);
			maze[current.r()][current.c() + 1] = 'A';
		}

	}
	return false;	//never reached end point 
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X....X...X",
		"X.XX.XX..X",
		"XXX....X.X",
		"X.XXX.XXXX",
		"X.X...X..X",
		"X...X.X..X",
		"XXXXX.X.XX",
		"X........X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 1, 1, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	if (pathExists(maze, 10, 10, 1, 1, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}


