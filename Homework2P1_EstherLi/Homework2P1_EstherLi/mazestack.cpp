#include <stack>
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
	stack<Coord> coordStack;		// declare a stack of Coords
	Coord start(sr, sc);		
	coordStack.push(start);
	maze[sr][sc] = 'A';				//mark start point as encountered
	while (!coordStack.empty()) {
		Coord current = coordStack.top();
		coordStack.pop();
		if (current.r() == er && current.c() == ec)			//we reached the end point
			return true;
		if (maze[current.r() + 1][current.c()] == '.') {	//if south is not a wall and has not been encountered
			Coord south(current.r() + 1, current.c());		//create new coordinate for south
			coordStack.push(south);							//add south coordinate to stack
			maze[current.r() + 1][current.c()] = 'A';		//mark as encountered
		}
		if (maze[current.r()][current.c() - 1] == '.') {
			Coord west(current.r(), current.c() - 1);
			coordStack.push(west);
			maze[current.r()][current.c() - 1] = 'A';
		}
		if (maze[current.r() - 1][current.c()] == '.') {
			Coord north(current.r() - 1, current.c());
			coordStack.push(north);
			maze[current.r() - 1][current.c()] = 'A';
		}
		if (maze[current.r()][current.c() + 1] == '.') {
			Coord east(current.r(), current.c() + 1);
			coordStack.push(east);
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

	if (pathExists(maze, 10, 10, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}