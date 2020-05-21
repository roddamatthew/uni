#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

using namespace std;

class Entity
{
protected:
	int row; //Y position in array
	int column; //X position in array

public:
	Entity(); //Default Constructor
	Entity(int rowstart, int columnstart); //Constructor that sets row and column equal to parameters
	void movement(char direction, int rows, int columns); //Changes row/column one position based on input direction
	int getrow(); //Returns row
	int getcolumn(); //Returns column
	void setrow(int rowinput); //Sets row
	void setcolumn(int columninput); //Sets column
	~Entity();	//Default Destructor
};
#endif //ENTITY_H