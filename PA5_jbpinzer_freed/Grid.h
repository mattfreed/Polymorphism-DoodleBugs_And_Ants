/*
 * Grid.h
 *
 *  Created on: Feb 19, 2018
 *      Author: jbpinzer
 */

#ifndef GRID_H_
#define GRID_H_
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Organism.h"
#include "DoodleBug.h"
#include "Ant.h"


using namespace std;

class Grid {
	public:
		Grid(int doodleBugs, int ants, int gridSize);
		virtual ~Grid();

		void createGrid();
		Organism* getCell(int x, int y);
		void setCell(int x, int y, Organism* o);

		vector<vector<Organism*> > getGrid();

	private:
		int doodleBugs, ants, gridSize;
		vector<vector<Organism*> > grid;//The grid
};

#endif /* GRID_H_ */
