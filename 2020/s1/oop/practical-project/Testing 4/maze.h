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

	int wall;
	int space;
	int pellet;
	int pac;
	int red;
	int blue;
	int pink;
	int orange;
	int superpellet;

public:
	Maze(int rowSize, int columnSize);
	bool isWall(int row, int column);
	void mazeUpdate(int row, int column);
	void mazePrinter();
	int pelletUpdate();

};
#endif //MAZE_H