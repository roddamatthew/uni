#ifndef MAZE_H
#define MAZE_H

#include <iostream>

using namespace std;

class Maze
{
private:
	int columns;
	int rows;
	int pelletsNumber;
	int** maze;

	int wall; //Placeholder integers to represent whats occupying positions of array
	int space;
	int pellet;
	int pac;
	int red;
	int blue;
	int pink;
	int orange;
	int superpellet;

public:
	Maze(); //Constructor for the maze
	void mazeUpdate(int row, int column, char character); //Updates elements within the maze
	void mazePrinter();	//Prints the maze out to user
	int getPosition(int row, int column); //Returns the integer at a input position in the array
	void setPosition(int row, int column, int value); //Changes a position within the array to an inputted value

};
#endif //MAZE_H