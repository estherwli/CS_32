#include <iostream>
#include <string>
using namespace std;

/*
If the start location is equal to the ending location, then we've
		solved the maze, so return true.
	Mark the start location as visited.
	For each of the four directions,
		If the location one step in that direction (from the start
		location) is unvisited,
			then call pathExists starting from that location (and
				ending at the same ending location as in the
				current call).
			 If that returned true,
				 then return true.
	Return false.
*/

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec) //solved maze
		return true;
	maze[sr][sc] = '#'; //mark this location as discovered
	if (sr < nRows - 1 && maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) //south
			return true;
	if (sr >= 1 && maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) //north
			return true;
	if (sc < nCols - 1 && maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) //east
			return true;
	if (sc >= 1 && maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) //west
			return true;
	return false;
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