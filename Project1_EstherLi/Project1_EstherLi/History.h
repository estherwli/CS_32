#ifndef HISTORY_H
#define HISTORY_H
#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	int m_rows;
	int m_cols;
	int m_dead[MAXZOMBIES][2]; //2D array to store dead zombies' coordinates
	int m_nDead;
};

#endif //HISTORY_H