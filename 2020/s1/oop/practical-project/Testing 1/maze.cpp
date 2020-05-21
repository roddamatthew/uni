#include <iostream>
#include "maze.h"

using namespace std;

Maze::Maze()
{
	x_size=12;
	y_size=12;
	int i;

	maze=new int*[y_size];

	for(i=0;i<y_size;i++){
		maze[i]=new int[x_size];
	}

}

void Maze::mazePrinter()
{
	int i;
	int j;

	for(i=0;i<y_size;i++){
		for(j=0;j<x_size;j++){
			if(maze[i][j]==0){
				std::cout << ". ";

			}
		}
		std::cout << std::endl;
	}
}