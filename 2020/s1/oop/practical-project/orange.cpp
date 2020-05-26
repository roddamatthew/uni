#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "orange.h"

using namespace std;

Orange::Orange(){
}

void Orange::chase(int pacRow, int pacColumn){
	//Turn 180 degrees when first called
	//Then move towards pacman if OUTSIDE a distance of 8 tiles in radius
	//If within the 8 tile radius move towards the scatter position: (31,0)
}

void Orange::scatter(){
	pathing(31,0);
}

void Orange::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,15);

	if(getrow() == 10 && getcolumn() == 15){
		ate = false;
	}
}