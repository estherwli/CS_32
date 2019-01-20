#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	m_nDead = 0;
}


bool History::record(int r, int c) {
	if (r > m_rows || r < 1 || c > m_cols || c < 1) //checks if coordinate is in bound
		return false;
	m_dead[m_nDead][0] = r; //records row of dead zombie in 2D array
	m_dead[m_nDead][1] = c; //records column of dead zombie in 2D array
	m_nDead++; 
	return true;
}

void History::display() const {
	char grid[MAXROWS][MAXCOLS];

	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			grid[r][c] = '.';

	for (int i = 0; i < m_nDead; i++) {
		int row = m_dead[i][0] - 1;
		int col = m_dead[i][1] - 1;
		if (grid[row][col] == '.') //if this is the first zombie to die here
			grid[row][col] = 'A';
		else if (grid[row][col] == 'Z') //if this is the 26th or more zombie to die here
			grid[row][col] = 'Z';
		else
			grid[row][col] += 1; //if this is the 2nd-25th zombie to die here
	}

	//Draw the grid
	clearScreen();
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}