#include <iostream>
#include "maze.h"

using namespace std;

Maze::Maze()
{
	wall=0;
	space=2;
	pellet=1;
	pac=3;

	columns=26;
	rows=29;

	int i,j;

	int maze1[29][26]=
	{
		{1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1},
		{1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1},
		{1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
		{1,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,1},
		{1,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,1},
		{1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1},
		{1,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1},
		{1,1,1,1,1,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,1,1,1,1,1},
		{2,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1},
		{2,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,1},
		{2,2,2,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,2,2,2},
		{0,0,2,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,2,0,0},
		{0,0,2,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,2,0,0},
		{2,2,2,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,2,2,2},
		{2,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,2},
		{2,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,2},
		{1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
		{1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
		{1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for(i=0;i<29;i++){
		for(j=0;j<26;j++){
			maze[i][j]=maze1[i][j];
		}
	}

}

void Maze::mazePrinter()
{
	int i;
	int j;

	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			if(maze[i][j]==pellet){
				std::cout << ". ";
			}else if(maze[i][j]==wall){
				std::cout << "▒ ";
			}else if(maze[i][j]==space){
				std::cout << "  ";
			}else if(maze[i][j]==pellet){
				std::cout << ". ";
			}
		}
		std::cout << std::endl;
	}
}

void Maze::mazeUpdate(int row, int column, int type)
{
	// maze[y][x]=3;
}

bool Maze::wallChecker(int row,int column){
	if(maze[row][column]==0){
		return true;
	}else{
		return false;
	}
}