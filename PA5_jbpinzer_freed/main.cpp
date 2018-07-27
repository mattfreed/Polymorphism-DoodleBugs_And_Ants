/*
 * main.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: jbpinzer
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Simulation.h"

using namespace std;

/** Constructor for class Main
 * @param argc The count of arguments including the command name
 * @param argv The array of arguments where index 0 is the program call
 * @return 0 to signal completion
 */
int main(int argc, char** argv) {

	int gridSize = 20, doodleBugs = 5, ants = 100, time_steps = 1000, seed = 1, pause = 0;// initialize variables to default values

	switch (argc) { //No breaks because if there are 7 command arguments we want to get the ones before it too
		case 7: pause = atoi(argv[6]);
		case 6: seed = atoi(argv[5]);
		case 5: time_steps = atoi(argv[4]);
		case 4: ants = atoi(argv[3]);
		case 3: doodleBugs = atoi(argv[2]);
		case 2: gridSize = atoi(argv[1]);
		default: break;

	}

	if(pause < 0) {
		cout << "Pause cannot be negative!" << endl;
		return -1;
	}

	//If seed is 0 then seed the random generator with the current time, otherwise use the seed given.
	if(seed == 0) {
		srand(time(NULL));
	} else {
		srand(seed);
	}


	//Make new simulation to run using the parameters passed into the command line, or default values
	Simulation* simulation = new Simulation(gridSize, doodleBugs, ants, time_steps, pause);
	int terminationCondition = simulation->run();//runs the simulation
	int stepsSimulated = simulation->stepsSimulated;//gets the total number of steps simulated when the program has run

	int antsLeft = simulation->antCount, doodleBugsLeft = simulation->doodleCount;//keeps track of the ants and doodle bugs left on the board

	cout << "Simulation over! Project Summary:" << endl;
	if(argc < 2) {
		cout << "No command line arguments were given! " << endl << "Used default values of: ";
	} else {
		cout << "Used Arguments: ";
	}
	cout << "gridSize = " <<  gridSize << ", doodleBugs = " << doodleBugs << ", ants = " << ants
			<< ", time_steps = " << time_steps << ", seed = " << seed << ", pause = " << pause << endl;

	//print out the final values of the simulation:
	cout << "Simulated " << stepsSimulated << " steps." << endl;
	cout << "Started with " << ants << " ants, and " << doodleBugs << " doodle bugs." << endl;
	ants = simulation->ants;
	doodleBugs = simulation->doodleBugs;
	cout << "Total number of ants: " << ants << ", with only " << antsLeft << " ants left." << endl;
	cout << "Total number of doodle bugs: " << doodleBugs << ", with only " << doodleBugsLeft << " doodle bugs left." << endl;

	//print out why the simulation was terminated
	switch(terminationCondition) {
		case 0: //Reached max time step
			cout << "Simulation terminated by reaching time step " << time_steps << "." << endl;
			break;
		case 1: //All ants are dead
			cout << "Simulation terminated because all of the Ants died." << endl;
			break;
		case 2: //All doodle bugs are dead
			cout << "Simulation terminated because all of the Doodle Bugs died." << endl;

	}
	simulation->print();//print the final simulation board
	return 0;
}


