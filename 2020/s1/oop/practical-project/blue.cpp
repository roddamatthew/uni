#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "blue.h"

using namespace std;

Blue::Blue(){
}

void Blue::chase(int pacRow, int pacColumn, char pacLastDirection, int redRow, int redColumn){
	//Turn 180 degrees on the first move
	// Then move towards a square that is the opposite of red's position centred around the position two tiles ahead of pacman

	//targetrow = redRow - 2*(redRow - pacExtendedRow);
	//targetcolumn = redColumn - 2*(redColumn - pacExtendedColumn);


}

void Blue::scatter(){
	pathing(31,28);
}

void Blue::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,13);

	if(getrow() == 10 && getcolumn() == 13){
		ate = false;
	}
}