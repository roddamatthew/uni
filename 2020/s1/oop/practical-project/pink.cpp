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
	switch (pacLastDirection){
		case 'w':
		if (pacRow-4>0){
			pathing(pacRow-4, pacColumn);
		} else {
			pathing(1, pacColumn);
		}
		break;

		case 'a':
		if (pacColumn-4>0){
			pathing(pacRow, pacColumn-4);
		} else {
			pathing(pacRow, 1);
		}
		break;

		case 's':
		if (pacRow+4<29){
			pathing(pacRow+4, pacColumn);
		} else {
			pathing(29, pacColumn);
		}
		break;

		case 'd':
		if (pacColumn+4<26){
			pathing(pacRow, pacColumn+4);
		} else {
			pathing(pacRow, 26);
		}
		break;
	}
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