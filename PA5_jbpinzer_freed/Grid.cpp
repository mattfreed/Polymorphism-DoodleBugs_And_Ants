/*
 * Grid.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: jbpinzer
 */

#include "Grid.h"

/** Constructor for class Grid
 * @param doodleBugs is the amount of doodle bugs to initialize
 * @param ants is the amount of ants to initialize
 * @param gridSize the total grid size of the grid
 */
Grid::Grid(int doodleBugs, int ants, int gridSize) {
	this->gridSize = gridSize;//set gridsize variable to size gridsize
	this->doodleBugs = doodleBugs;// set doodleBugs to the input variable doodleBugs
	this->ants = ants;//set ants to the input variable ants
	grid.resize(gridSize);//creates a single array of length grid size
	createGrid();//each array position is then made into more arrays to create a square grid

}

/** Destructor for class Grid
 */
Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

/** Function to create the grid
 */
void Grid::createGrid() {
	//loop through the row of the grid
	for(int i = 0; i < gridSize; i++) {
		grid[i].resize(gridSize);//create column using this row position i
		for(int j = 0; j < gridSize; j++) {//loop through column j
			grid[i][j] = NULL;//set the position i,j to value NULL
		}
	}

	//loop to populate the grid with doodlebugs
	for(int d = 0; d < doodleBugs; d++) {
		int x = rand() % gridSize;//determine a random row
		int y = rand() % gridSize;//determine a random column
		if(!grid[x][y]) {//if the cell is not currently populated, populate it with a doodle bug
			grid[x][y] = new DoodleBug(x, y, 0, 0, 0);
		} else {
			d--;
		}
	}
	//loop to populate the grid with ants
	for(int a = 0; a < ants; a++) {
		int x = rand() % gridSize;//determine random row
		int y = rand() % gridSize;//determine random column
		if(!grid[x][y]) {//if the cell is not currently populated, populate it with an ant
			grid[x][y] = new Ant(x, y, 0, 0);
		} else {
			a--;
		}
	}
}

/** Setter to set the cell to contain an organism
 * @param x is the new x position of the organism
 * @param y is the new y position of the organism
 * @param o the pointer to the organism that will populate the cell
 */
void Grid::setCell(int x, int y, Organism* o) {
	grid[x][y] = o;
}

/** Getter to get the information in the cell
 * @param x is the x position of the cell
 * @param y is the y position of the cell
 * @return the organism that is currently in this cell
 */
Organism* Grid::getCell(int x, int y) {
	return grid[x][y];
}

/** Getter to get the grid
 * @return the grid being a 2D vector of pointers to Organisms
 */
vector<vector<Organism*> > Grid::getGrid(){
	return grid;
}
