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

public:
	Maze();
	bool wallChecker(int x, int y);
	void mazeUpdate(int x, int y, int type);
	void mazePrinter();

};
#endif //MAZE_H