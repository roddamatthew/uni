#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"

using namespace std;

Ghost::Ghost(){
	lastDirection=0;
}

void Ghost::pathing(int rowtarget, int columntarget){
	int rowdistance = rowtarget - row;			//Stores the y distance between current position and target
	int columndistance = columntarget - column;	//Stores the x distance between current position and target

	int distance = abs(rowdistance) + abs(columndistance); //Stores the total distance between current and target positions

	Maze* mazeTemplate;
	mazeTemplate = new Maze(); //Creating a maze copy to check for collision with walls

	//Setting "portal" positions in the maze to walls for the ghost so that it cannot trap itself
	mazeTemplate -> setPosition(17,0,0);
	mazeTemplate -> setPosition(20,0,0);
	mazeTemplate -> setPosition(17,27,0);
	mazeTemplate -> setPosition(20,27,0);
	mazeTemplate -> setPosition(0,9,0);
	mazeTemplate -> setPosition(0,18,0);
	mazeTemplate -> setPosition(30,18,0);
	mazeTemplate -> setPosition(30,9,0);


	if(abs(rowdistance) >= abs(columndistance)){ //If further away in the y direction, favour moving in the y direction
		if(distance >= abs(rowdistance + 1) + abs(columndistance) && lastDirection != 's' && mazeTemplate -> getPosition(row - 1, column) != 0){  
			movement('w',35,35);
			lastDirection = 'w';
		}else if(lastDirection != 'w' && mazeTemplate -> getPosition(row + 1, column) != 0){
			movement('s',35,35);
			lastDirection = 's';
		}else if(distance >= abs(rowdistance) + abs(columndistance + 1) && lastDirection != 'd' && mazeTemplate -> getPosition(row, column - 1) != 0){
			movement('a',35,35);
			lastDirection = 'a';
		}else if(lastDirection != 'a' && mazeTemplate -> getPosition(row, column + 1) != 0){ //Move in a direction that doesn't backtrack or hit a wall
			movement('d',35,35);
			lastDirection = 'd';
		}else if(lastDirection != 's' && mazeTemplate -> getPosition(row - 1, column) != 0){ //Move in a direction that doesn't backtrack or hit a wall
			movement('w',35,35);
			lastDirection = 'w';
		}else if(lastDirection != 'd' && mazeTemplate -> getPosition(row, column - 1) != 0){ //Move in a direction that doesn't backtrack or hit a wall
			movement('a',35,35);
			lastDirection = 'a';
		}
	}else{ //Must be further in the x direction, so favour moving in the x direction
		if(distance >= abs(rowdistance) + abs(columndistance + 1) && lastDirection != 'd' && mazeTemplate -> getPosition(row, column - 1) != 0){
			movement('a',35,35);
			lastDirection = 'a';
		}else if(lastDirection != 'a' && mazeTemplate -> getPosition(row, column + 1) != 0){
			movement('d',35,35);
			lastDirection = 'd';
		}else if(distance >= abs(rowdistance + 1) + abs(columndistance) && lastDirection != 's' && mazeTemplate -> getPosition(row - 1, column) != 0){
			movement('w',35,35);
			lastDirection = 'w';
		}else if(lastDirection != 'w' && mazeTemplate -> getPosition(row + 1, column) != 0){
			movement('s',35,35);
			lastDirection = 's';
		}else if(lastDirection != 'd' && mazeTemplate -> getPosition(row, column - 1) != 0){
			movement('a',35,35);
			lastDirection = 'a';
		}else if(lastDirection != 's' && mazeTemplate -> getPosition(row - 1, column) != 0){
			movement('w',35,35);
			lastDirection = 'w';
		}
	}
}

void Ghost::scared(int rowtarget, int columntarget){
	pathing(rowtarget,columntarget);
}

void Ghost::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,12);

	if(getrow() == 10 && getcolumn() == 12){
		ate = false;
	}
}

void Ghost::setAte(){
	ate = true;
	std::cout << "Ate is: " << ate << std::endl;
}

bool Ghost::getAte(){
	std::cout << "Ate is: " << ate << std::endl;
	return ate;
}