#include <iostream>
#include "entity.h"

using namespace std;

Entity::Entity(){}

//Constructor that sets row and column equal to parameters
Entity::Entity(int rowstart, int columnstart){ 
	row = rowstart;
	column = columnstart;
}

void Entity::movement(char direction, int rows, int columns)
{
	switch(direction){
		
		case 'W':
		case 'w':
		if(row>=1){ //If not moving outside top of array
			row--; //Move up
		}else{
			row=rows-1; //Move to the bottom of the array
		}
		break;

		case 'A':
		case 'a':
		if(column>=1){ //If not moving outside the left of array
			column--; //Move left
		}else{
			column=columns-1; //Move to right boundary of array
		}
		break;

		case 'S':
		case 's':
		if(row<rows-1){ //If not moving outside bottom of array
			row++;	//Move down
		}else{
			row=0; //Move to top boundary of array
		}
		break;

		case 'D':
		case 'd':
		if(column<columns-1){ //If not moving outside right of array
			column++; //Move right
		}else{
			column=0; //Move to left boundary of array
		}
		break;
	}
}

//Returns the row of an entity
int Entity::getrow(){
	return row;
}

//Returns the column of an entity
int Entity::getcolumn(){
	return column;
}

//Sets the row of an entity to an input parameter
void Entity::setrow(int rowinput){
	row = rowinput;
}

//Sets the column of an entity to an input parameter
void Entity::setcolumn(int columninput){
	column = columninput;
}

//Defualt Destructor
Entity::~Entity(){
	std::cout << "Deleted an entity at " << row << "," << column << std::endl;
}