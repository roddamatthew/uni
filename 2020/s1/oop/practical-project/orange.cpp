#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "orange.h"
#include <cmath>

using namespace std;

Orange::Orange(){
}

void Orange::chase(int pacRow, int pacColumn){
	//Turn 180 degrees when first called
	int current_row=row;
	int current_col=column;

	int distRows=pow((pacRow-current_row),2);
	int distCols=pow((pacColumn-current_col),2)-1;

	int totalDist = ceil(pow(distRows+distCols, 0.5));

	std::cout << "Distance: " << totalDist <<std::endl;

	if (totalDist>8){
		pathing(pacRow, pacColumn);
	} else {
		pathing(31,0);
	}

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