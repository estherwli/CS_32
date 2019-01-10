#include "History.h"
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	m_nDead = 0;
}

bool History::record(int r, int c) {
	if (r > m_rows || r < 1 || c > m_cols || c < 1)
		return false;
	m_dead[m_nDead][0] = r;
	m_dead[m_nDead][1] = c;
	m_nDead++;
	return true;
}

void History::display() const {
	clearScreen();
	char grid[MAXROWS][MAXCOLS];
	char letters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
	'U', 'V', 'W', 'X', 'Y', 'Z' };

	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			grid[r][c] = '.';

	for (int i = 0; i < m_nDead; i++) 
		grid[m_dead[i][0] - 1][m_dead[i][1] - 1] = letters[i];
	
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}