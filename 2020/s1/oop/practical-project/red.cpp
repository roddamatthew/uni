#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "red.h"

using namespace std;

Red::Red(){
}

void Red::chase(int pacRow, int pacColumn){
	// First move needs to be in lastDirection then move towards pacman:
	pathing(pacRow, pacColumn);
}

void Red::scatter(){
	// Scatters to certain tile
	pathing(0,28);
}

void Red::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,12);

	if(getrow() == 10 && getcolumn() == 12){
		ate = false;
	}
}