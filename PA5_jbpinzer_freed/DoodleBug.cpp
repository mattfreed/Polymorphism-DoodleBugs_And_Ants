/*
 * DoodleBug.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: mwfreed
 */

#include "DoodleBug.h"

/** Constructor for class DoodleBug
 * @param xVal the x coordinate of the DoodleBug
 * @param yVal the y coordinate of the DoodleBug
 * @param steps total steps taken
 * @param stepsSinceMeal steps since a doodle bug had last eaten an ant
 * @param stepsSinceBred the steps taken since last bred
 */
DoodleBug::DoodleBug(int xPos, int yPos, int stepsTaken, int stepsSinceMeal, int stepsSinceBred) {
	this->x = xPos;
	this->y = yPos;
	this->stepsTaken = stepsTaken;
	this->stepsSinceMeal = stepsSinceMeal;
	this->stepsSinceBred = stepsSinceBred;
	hasTakenTurn = false;
	isPrey = false;
	canBreed = false;

}

/** Doodle Bug object deconstructor
 */
DoodleBug::~DoodleBug() {
	// TODO Auto-generated destructor stub
}

/** Function to change the x and y variables of the DoodleBug
 * @param x the x coordinate of the bug
 * @param y the y coordinate of the bug
 * @return 0 to check completion
 */
int DoodleBug::move(int x, int y){
	this->x = x;//set the x value of the bug to the new x location
	this->y = y;//set the y value of the bug to the new y location
	stepsTaken++;// increase the total steps of the ant by 1
	stepsSinceBred++;//increase the steps since it last bred by 1
	stepsSinceMeal++;//increase the stepsStinceMeal
	hasTakenTurn = true;// change the boolean of hasTakenTurn from false to true
	return 0;
}

/** Function to set and check the boolean of canBreed for this DoodleBug
 * @return the value of canBreed, a boolean which determines whether the doodle bug can breed or not
 */
bool DoodleBug::breed() {
	if(stepsSinceBred >= 8 && !isStarving()) {//check if the steps since last bred are greater than or = to 8 and it is not starving
		canBreed = true;//set can breed to true
	}
	return canBreed;//returns the canBreed variable
}

/** Function to change the hasTakenTurn boolean to false
 */
void DoodleBug::resetTurn() {
	hasTakenTurn = false;// changes the hasTakenTurn boolean from true to false
}

/** Function to change the values of DoodleBug to represent that it has just bred
 */
void DoodleBug::didBreed() {
	canBreed = false;//change the canBreed boolean to false
	stepsSinceBred = 0;//reset the stepsSinceBred to 0
}

/** Function to check whether the doodlebug is starving or not
 * @return boolean that indicates the bug is either starving or not
 */
bool DoodleBug::isStarving() {
	if(stepsSinceMeal >= 3) {//checks to see whether the doodle bug has eaten within the past 3 steps
		return true;
	}
	return false;
}
