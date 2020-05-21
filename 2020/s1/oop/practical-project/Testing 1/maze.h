#ifndef MAZE_H
#define MAZE_H

#include <iostream>

using namespace std;

class Maze
{
private:
	int x_size;
	int y_size;
	int ** maze;

public:
	Maze();
	void mazePrinter();

};
#endif //MAZE_H