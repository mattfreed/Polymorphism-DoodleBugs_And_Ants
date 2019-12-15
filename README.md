# Assignment 5: Polymorphism
##By Julian Pinzer and Matt Freed

### Summary
This program takes an input for a simulation of Doodle Bugs and Ants and runs through it.

### How to run
##### Command line arguments
`./PA5 gridSize #doodlebugs #ants #time_steps seed pause`
##### Eclipse
Import the project to eclipse, and then build the project. Then run the project as a C/C++ application. You can specify command arguments in the run configurations.
##### Terminal
You can build the code by running this command in the working directiory: `make`

You can run the code by running this command in the working directiory: `./PA5 gridSize #doodlebugs #ants #time_steps seed pause`

### Classes and Methods:
#### Simulation.cpp
This is the class that handles the brute work of doing the simulation. It handles all the moving, breeding, and killing of organisms. It also calls the grid to be created and prints the grid.
#### Grid.cpp
This is the class that manages the 2D Vector of type: `Organism*`
There are methods for getting and setting a cell/element of the 2D Vector.
#### Organism.h
This is the header file that contains everything needed for an Organism such as an Ant or DoodleBug.
#### Doodlebug.h
This is the header file for the doodle bug object. It has the ability to move, breed, and starve.
#### Ant.h
This is the header file for the ant object. It has the ability to move and breed.

### Results and Conclusion:
We discovered that at least with the default values, the simulation will terminate after the time steps hit the max allowed. There are times in the simulation where ants cover almost every spot without a doodle bug on the board, but then the doodle bugs eat a large portion of the ants and get to breed because of it, but eventually the ants make a resurgence again.
By lowering the ant count to something around the 10-15 range, the doodle bugs end up starving and then it terminates due to all of the doodle bugs having died.


### Problems We Had:
The only issues we ran into during the development of this assignment was from the move and breed functions and trying to figure out how to find an available spot and move them to the new cell.

### Loop invariants:
##### Time Step Loop:
This loop goes through every step given and runs through the grid for doodle bugs then runs through the grid again for the ants.
##### Get Cell Loops:
There are 4 loops that go through the entire grid to get each cell. The first one gets and moves all the doodle bugs, the second one gets all the doodle bugs and resets them so they can move again, the third gets and moves all the ants, and finally the fourth resets all the ants so they can move again.
##### Get Valid Direction Loop:
The default direction is -1, but because this while loop isn't hit unless we know there is at least one valid direction we can randomly get a value 0-3 to see if the array at that random index is a value of one, then the random direction chosen will be that index which correlates to a direction.
##### Print Loop:
Loop through all of the cells to see if the cell contains a Doodle Bug, Ant or nothing. It prints an `x`, `o`, or `-` respectively
##### Create Grid Loops:
We have 3 loops in the `createGrid()` function of `Grid.cpp`.
The first loop goes through the grid and makes every cell a `NULL` value.
The second loop goes through and picks random cells that are of type `NULL` and creates and places a new `DoodleBug` in that cell. Stopping once it hits the maximum doodle bugs specified.
The third loop does the same as the previous one but for `Ant`.
