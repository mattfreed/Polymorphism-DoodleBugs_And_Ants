/*
 * Organism.h
 *
 *  Created on: Feb 19, 2018
 *      Author: jbpinzer
 */

#ifndef ORGANISM_H_
#define ORGANISM_H_
#include <iostream>
#include <cstdlib>

class Organism {
	public:
		virtual ~Organism(){}; //Deconstruct an Organism
		virtual int move(int x, int y) = 0; //Create a virtual function to be implemented by ant and doodlebug for when they move
		virtual bool breed() = 0; //Same as above, but for when they breed
		virtual void resetTurn() = 0; //Same again, but for when the hasTakenTurn value needs to be reset
		int x, y; //Make an x and y location value for the organism
		int stepsTaken; //Store how many steps the organism has taken.
		int stepsSinceBred; //Store how many steps the organism has taken since it last bred
		bool isPrey; //Is the organism prey (ant) or not prey (doodle bug)
		bool hasTakenTurn; //Has this organism taken it's turn?
		bool canBreed; //Is the organism eligible to breed?
};

#endif /* ORGANISM_H_ */
