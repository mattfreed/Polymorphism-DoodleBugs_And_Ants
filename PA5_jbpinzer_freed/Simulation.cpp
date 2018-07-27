/*
 * Simulation.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: jbpinzer
 */

#include "Simulation.h"

/** Construct a simulation
 * @param gridSize the length of each side of the grid
 * @param doodleBugs the count of doodle bugs to put in the simulation
 * @param ants the count of ants to put in the simulation
 * @param timeSteps the number of time steps to go through in the simulation loop
 * @param pause a number specifying how many time steps to go through before pausing and printing, 0 if it shouldn't pause
 */
Simulation::Simulation(int gridSize, int doodleBugs, int ants, int timeSteps, int pause) {
	this->grid = new Grid(doodleBugs, ants, gridSize);
	this->gridSize = gridSize;
	this->doodleBugs = doodleBugs;
	this->ants = ants;
	this->timeSteps = timeSteps;
	this->pause = pause;
	this->stepsSimulated = 0;
	this->doodleCount = 0;
	this->antCount = 0;
}

/** Deconstruct a simulation
 */
Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

/** Run a simulation
 * @return the end condition of the simulation, 0 for hitting the time step limit, 1 for all of the ants dying, 2 for all of the doodlebugs dying
 */
int Simulation::run() {
	cout << "Running simulation" << endl;

	/* Run the number of steps specified by the command arguments.
	 * only end if the number of steps hit the max, if there are no ants, or if there are no doodle bugs
	 */
	for(stepsSimulated = 0; stepsSimulated < timeSteps; stepsSimulated++) {
		resetCount(); //Reset the count to 0 because it's a new time step

		//Run DoodleBugs Step
		for(int i = 0; i < gridSize; i++) {
			for(int j = 0; j < gridSize; j++) {
				//Make sure the cell is not null, is not prey, and hasn't taken a turn
				if(grid->getCell(i,j) && !grid->getCell(i,j)->isPrey && !grid->getCell(i,j)->hasTakenTurn) {
					DoodleBug* d = dynamic_cast<DoodleBug*>(grid->getCell(i,j)); //Get the doodle bug from the cell
					int direction = moveBug(i, j, false); //Figure out where the doodle bug will move to, and store the direction
					switch(direction) {
						case 0: //Moved down
							d = dynamic_cast<DoodleBug*>(grid->getCell(i+1,j));
							d->move(i+1,j);
							break;
						case 1: //Moved up
							d = dynamic_cast<DoodleBug*>(grid->getCell(i-1,j));
							d->move(i-1,j);
							break;
						case 2: //Moved right
							d = dynamic_cast<DoodleBug*>(grid->getCell(i,j+1));
							d->move(i,j+1);
							break;
						case 3: //Moved left
							d = dynamic_cast<DoodleBug*>(grid->getCell(i,j-1));
							d->move(i,j-1);
							break;
						default: //Didn't move (-1)
							d->hasTakenTurn = true;
					}

					if(!d->isStarving()) { //Make sure the doodle bug is not starving
						if(d->breed()) { //Make see if the doodle bug can breed
							bool didBreed = breedOrganism(d->x,d->y,false);
							if(didBreed) { //if the doodle bug could breed, see if it did (if it had room to)
								d->didBreed(); //change the doodle bug's breeding eligibility
								doodleBugs++; //add one to the doodle bug count
							}
						}
					} else {
						//Know that the it's starving so kill the bug
						grid->setCell(d->x, d->y, NULL);
					}
				}
			}
		}

		//Go through the grid, and reset all of the doodle bugs
		for(int i = 0; i < gridSize; i++) {
			for(int j = 0; j < gridSize; j++) {
				//If the cell is not null, and it's not prey then reset it and add to the count of doodle bugs
				if(grid->getCell(i,j) && !grid->getCell(i,j)->isPrey) {
					grid->getCell(i,j)->resetTurn();
					doodleCount++;
				}

			}
		}

		//Run Ants Step
		for(int i = 0; i < gridSize; i++) {
			for(int j = 0; j < gridSize; j++) {
				//If the cell is not null, and it's prey (an ant) and it hasn't taken a turn yet then move it
				if(grid->getCell(i,j) && grid->getCell(i,j)->isPrey && !grid->getCell(i,j)->hasTakenTurn) {
					Ant* a = dynamic_cast<Ant*>(grid->getCell(i,j));
					int direction = moveBug(i, j, true); //Same idea for moving the doodle bug

					switch(direction) {
						case 0: //Moved down
							a = dynamic_cast<Ant*>(grid->getCell(i+1,j));
							a->move(i+1,j);
							break;
						case 1: //Moved up
							a = dynamic_cast<Ant*>(grid->getCell(i-1,j));
							a->move(i-1,j);
							break;
						case 2: //Moved right
							a = dynamic_cast<Ant*>(grid->getCell(i,j+1));
							a->move(i,j+1);
							break;
						case 3: //Moved left
							a = dynamic_cast<Ant*>(grid->getCell(i,j-1));
							a->move(i,j-1);
							break;
						default: //Didn't move (-1)
							a->hasTakenTurn = true;
					}

					if(a->breed()) { //See if the ant can breed
						bool didBreed = breedOrganism(a->x,a->y,true); //See if the ant bred
						if(didBreed) { //If the ant bred then set the ant so that it did breed and add to the total ant count
							a->didBreed();
							ants++;
						}
					}
				}
			}
		}

		//Go through the grid, and reset all of the ants
		for(int i = 0; i < gridSize; i++) {
			for(int j = 0; j < gridSize; j++) {
				//If the cell is not null, and it is prey then reset it and add to the count of ants
				if(grid->getCell(i,j) && grid->getCell(i,j)->isPrey) {
					grid->getCell(i,j)->resetTurn();
					antCount++;
				}

			}
		}

		//If pause is enabled and it isn't the first step then do the pause action
		if(pause != 0 && stepsSimulated > 0) {
			//If the step is divisible by the pause value then print the current step and the current grid.
			if(stepsSimulated%pause == 0) {
				cout << "Pausing at time step: " << stepsSimulated << endl;
				print();
				//Wait for the user to press enter to continue to the next pause step
				cout << "Press enter to continue!" << endl;
				cin.get();
			}
		}

		//If the ant count is at 0 then return an end condition
		if(antCount == 0) {
			return 1;
		}

		//If the doodle bug count is at 0 then return an end condition
		if(doodleCount == 0) {
			return 2;
		}
	}
	//Return 0 if the loop is over which means the max time steps were hit
	return 0;

}

/** Function to move the bug
 * @param x the x coordinate of the bug
 * @param y the y coordinate of the bug
 * @param isPrey whether or not the bug is prey
 * @return the direction that the organism will move in, 0 for down, 1 for up, 2 for left, 3 for right, or -1 if it can't move
 */
int Simulation::moveBug(int x, int y, bool isPrey) {
	int direction = -1;
	int possDirections[4] = {0};
	int numDirections = 0;
	int newX = x, newY = y;

	//Check if it's a doodle bug and figure out what direction an ant is in.
	if(!isPrey) {
		//checks to see if it can eat a ant below
		if((x + 1 < gridSize) && (grid->getCell(x+1,y)) && (grid->getCell(x+1,y)->isPrey)){
			numDirections++;
			possDirections[0] = 1;
		}
		//checks to see if it can eat a ant above
		if((x - 1 >= 0) && (grid->getCell(x-1,y)) && (grid->getCell(x-1,y)->isPrey)){
			numDirections++;
			possDirections[1] = 1;
		}
		//checks to see if it can eat a ant to the right
		if((y + 1 < gridSize) && (grid->getCell(x,y+1)) && (grid->getCell(x,y+1)->isPrey)){
			numDirections++;
			possDirections[2] = 1;
		}
		//checks to see if it can eat a ant to the left
		if((y - 1 >= 0) && (grid->getCell(x,y-1)) && (grid->getCell(x,y-1)->isPrey)){
			numDirections++;
			possDirections[3] = 1;
		}

		//If there are ants around the doodle bug
		if(numDirections != 0) {
			//While the direction is still -1 meaning don't move, try to get a new random direction from the array of potential directions 
			while(direction == -1) {
				int temp = rand()%4;
				if(possDirections[temp] == 1) {
					direction = temp;
				}
			}
			if(direction == 0) {
				newX++;
			} else if(direction == 1) {
				newX--;
			} else if(direction == 2) {
				newY++;
			} else if(direction == 3) {
				newY--;
			}

			if(grid->getCell(newX,newY)->isPrey) {
				grid->setCell(newX,newY,grid->getCell(x,y)); //Set the new coordinates to the current doodle bug
				grid->setCell(x, y, NULL); //Set the previous cell to NULL
				dynamic_cast<DoodleBug*>(grid->getCell(newX,newY))->stepsSinceMeal = 0; //Doodle Bug just ate so reset the steps
				return direction;
			}
		} else {
			//If there was no ants around the doodle bug then just do the normal random pick
			return moveBug(x, y, true);
		}
	} else {
		//Figures out what directions the organism can randomly move to

		//Checks to see if it can move down
		if((x + 1 < gridSize) && (grid->getCell(x+1,y) == NULL)){
			numDirections++;
			possDirections[0] = 1;
		}
		//Checks to see if it can move up
		if((x - 1 >= 0) && (grid->getCell(x-1,y) == NULL)){
			numDirections++;
			possDirections[1] = 1;
		}
		//Checks to see if it can move right
		if((y + 1 < gridSize) && (grid->getCell(x,y+1) == NULL)){
			numDirections++;
			possDirections[2] = 1;
		}
		//Checks to see if it can move left
		if((y - 1 >= 0) && (grid->getCell(x,y-1) == NULL)){
			numDirections++;
			possDirections[3] = 1;
		}

		//If there are directions it can go in
		if(numDirections != 0) {
			while(direction == -1) { //try to find a random direction
				int temp = rand()%4;
				if(possDirections[temp] == 1) {
					direction = temp; //if the random number selected was a valid movement then choose it for the direction
				}
			}

			if(direction == 0) {
				newX++;
			} else if(direction == 1) {
				newX--;
			} else if(direction == 2) {
				newY++;
			} else if(direction == 3) {
				newY--;
			}

			grid->setCell(newX,newY,grid->getCell(x,y)); //Set the new cell to what was in the old one
			grid->setCell(x, y, NULL); //Set the old cell to NULL
			return direction;
		}
	}

	//If this return statement is hit, it will return -1 meaning it couldn't move anywhere.
	return direction;
}

bool Simulation::breedOrganism(int x, int y, bool isPrey) {
	int direction = -1;
	int possDirections[4] = {0};
	int numDirections = 0;
	int newX = x, newY = y;

	//checks to see if it can move down
	if((x + 1 < gridSize) && (grid->getCell(x+1,y) == NULL)){
		numDirections++;
		possDirections[0] = 1;
	}
	//checks to see if it can move up
	if((x - 1 >= 0) && (grid->getCell(x-1,y) == NULL)){
		numDirections++;
		possDirections[1] = 1;
	}
	//checks to see if it can move right
	if((y + 1 < gridSize) && (grid->getCell(x,y+1) == NULL)){
		numDirections++;
		possDirections[2] = 1;
	}
	//checks to see if it can move left
	if((y - 1 >= 0) && (grid->getCell(x,y-1) == NULL)){
		numDirections++;
		possDirections[3] = 1;
	}

	//If there is a direction that the organism can breed in
	if(numDirections != 0) {
		while(direction == -1) {
			int temp = rand()%4;
			if(possDirections[temp] == 1) {
				direction = temp;
			}
		}
		if(direction == 0) {
			newX++;
		} else if(direction == 1) {
			newX--;
		} else if(direction == 2) {
			newY++;
		} else if(direction == 3) {
			newY--;
		}

		if(isPrey) { //Breed a new ant
			grid->setCell(newX, newY, new Ant(newX, newY, 0, 0));
		} else { //Breed a new Doodle Bug
			grid->setCell(newX, newY, new DoodleBug(newX, newY, 0, 0, 0));
		}
		//Did breed somewhere
		return true;
	}
	//No where to breed
	return false;
}

/** Print the simulation grid/board.
 */
void Simulation::print() {
	for(int i = 0; i < gridSize; i++) {
		for(int j = 0; j < gridSize; j++) {
			if(grid->getCell(i,j)) {
				if(!grid->getCell(i,j)->isPrey) { //If a doodle bug then print x
					cout << "x";
				} else if (grid->getCell(i,j)->isPrey) { //If an ant then print o
					cout << "o";
				}
			} else { //If not an organism just print a dash
				cout << "-";
			}
		}
		cout << endl;
	}
}

/** Reset the organism counts to be called at the end of every time step.
 */
void Simulation::resetCount() {
	doodleCount = 0;
	antCount = 0;
}
