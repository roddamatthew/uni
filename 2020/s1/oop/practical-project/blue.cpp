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
	
	int pacExtendedRow, pacExtendedColumn;

	switch (pacLastDirection){
		case 'w':
		if (pacRow-2>0){
			pacExtendedRow = pacRow-2;
			pacExtendedColumn = pacColumn;
		} else {
			pacExtendedRow = 1;
			pacExtendedColumn = pacColumn;
		}
		break;

		case 'a':
		if (pacColumn-2>0){
			pacExtendedRow = pacRow;
			pacExtendedColumn = pacColumn-2;
		} else {
			pacExtendedRow = pacRow;
			pacExtendedColumn = 1;
		}
		break;

		case 's':
		if (pacRow+2<29){
			pacExtendedRow = pacRow+2;
			pacExtendedColumn = pacColumn;
		} else {
			pacExtendedRow = 29;
			pacExtendedColumn = pacColumn;
		}
		break;

		case 'd':
		if (pacColumn+2<26){
			pacExtendedRow = pacRow;
			pacExtendedColumn = pacColumn+2;
		} else {
			pacExtendedRow = pacRow;
			pacExtendedColumn = 26;
		}
		break;
	}
	
	int targetrow = redRow - 2*(redRow - pacExtendedRow);
	int targetcolumn = redColumn - 2*(redColumn - pacExtendedColumn);

	pathing(targetrow, targetcolumn);
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