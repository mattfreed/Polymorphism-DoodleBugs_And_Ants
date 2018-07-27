/*
 * Simulation.h
 *
 *  Created on: Feb 19, 2018
 *      Author: jbpinzer
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include "Organism.h"
#include "Grid.h"

using namespace std;

class Simulation {
	public:
		Simulation(int gridSize, int doodleBugs, int ants, int timeSteps, int pause);
		virtual ~Simulation();

		int run();

		void print();
		int moveBug(int x, int y, bool isPrey);

		bool breedOrganism(int x, int y, bool isPrey);

		void resetCount();

		int doodleCount, antCount, doodleBugs, ants, stepsSimulated;

	private:
		Grid* grid;
		int gridSize, pause, timeSteps;
};

#endif /* SIMULATION_H_ */
