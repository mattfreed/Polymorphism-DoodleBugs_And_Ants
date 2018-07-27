/*
 * Ant.h
 *
 *  Created on: Feb 20, 2018
 *      Author: mwfreed
 */

#ifndef ANT_H_
#define ANT_H_
#include <cstdlib>
#include "Organism.h"

class Ant: public Organism {
public:
	Ant(int xVal, int yVal, int steps, int stepsSinceBred);
	virtual ~Ant();

	virtual int move(int x, int y);
	virtual bool breed();
	virtual void resetTurn();

	void didBreed();
};

#endif /* ANT_H_ */
