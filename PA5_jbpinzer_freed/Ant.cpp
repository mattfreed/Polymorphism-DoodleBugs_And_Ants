/*
 * Ant.cpp
 *
 *  Created on: Feb 20, 2018
 *      Authors: mwfreed, jbpinzer
 */

#include "Ant.h"

/** Constructor for class Ant
 * @param xVal the x coordinate of the ant
 * @param yVal the y coordinate of the ant
 * @param steps total steps taken
 * @param stepsSinceBred the steps taken since last bred
 */
Ant::Ant(int xVal, int yVal, int steps, int stepsSinceBred) {
	this->x=xVal;
	this->y=yVal;
	this->stepsTaken=steps;
	this->stepsSinceBred=stepsSinceBred;
	canBreed = false;
	hasTakenTurn = false;
	isPrey = true;

}

/** Ant object deconstructor
 */
Ant::~Ant() {
	// TODO Auto-generated destructor stub
}

/** Function to move the ant and change the x and y variables of the ant
 * @param x the x coordinate of the bug
 * @param y the y coordinate of the bug
 * @return 0 to check completion
 */
int Ant::move(int x, int y){
	 this->x = x;//set the x value of the bug to the new x location
	 this->y = y;//set the y value of the bug to the new y location
	 stepsTaken++;// increase the total steps of the ant by 1
	 stepsSinceBred++;//increase the steps since it last bred by 1
	 hasTakenTurn = true;// change the boolean of hasTakenTurn from false to true
	 return 0;

}

 /** Function to check the boolean of canBreed for ant
  * @return the value of canBreed, a boolean which determines whether an ant can breed or not
  */
bool Ant::breed(){
	 if (stepsSinceBred>=3){//check if the steps since last bred are greater than or = to 3
		 canBreed = true;//set can breed to true
	 }
	 return canBreed;//returns the canBreed variable
}

 /** Function to change the values of Ant to represent that it has just bred
  */
void Ant::didBreed(){
	canBreed=false;//change the canBreed boolean to false
	stepsSinceBred=0;//reset the stepsSinceBred to 0
}

/** Function to change the hasTakenTurn boolean to false
 */
void Ant::resetTurn() {
	hasTakenTurn = false;//reset the hasTakenTurn boolean to false
}
