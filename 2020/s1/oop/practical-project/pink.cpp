#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "pink.h"

using namespace std;

Pink::Pink(){
}

void Pink::chase(int pacRow, int pacColumn, char pacLastDirection){
	// turn 180 degress
	// then moves towards the tile 4 moves infront of the pacman position in the direction pacman is moving
	// will need to add a new function and variable to pacman to store the last direction
}

void Pink::scatter(){
	pathing(0,0);
}

void Pink::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,14);

	if(getrow() == 10 && getcolumn() == 14){
		ate = false;
	}
}