#ifndef MAZE_H
#define MAZE_H

#include <iostream>

using namespace std;

class Maze
{
private:
	int columns;
	int rows;
	int maze[29][26];

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
	Maze();
	bool isWall(int row, int column);
	void mazeUpdate(int row, int column);
	void mazePrinter();

};
#endif //MAZE_H