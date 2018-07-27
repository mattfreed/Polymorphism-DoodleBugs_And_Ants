/*
 * DoodleBug.h
 *
 *  Created on: Feb 20, 2018
 *      Author: mwfreed
 */

#ifndef DOODLEBUG_H_
#define DOODLEBUG_H_
#include "Organism.h"

class DoodleBug: public Organism{
public:
	DoodleBug(int xPos, int yPos, int stepsTaken, int stepsSinceMeal, int stepsSinceBred);
	virtual ~DoodleBug();

	virtual int move(int x, int y);
	virtual bool breed();
	virtual void resetTurn();

	void didBreed();
	bool isStarving();
	int stepsSinceMeal;
};

#endif /* DOODLEBUG_H_ */
