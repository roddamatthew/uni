#include <iostream>
#include <stdlib.h>
#include "maze.h"

using namespace std;

Maze::Maze()
{
	int i,j;
	wall=0;
	space=2;
	pellet=1;
	pac=3;
	red=4;
	blue=5;
	pink=6;
	orange=7;
	superpellet=8;

	rows = 31;
	columns = 28;

	int mazeTemplate[31][28]=
	{
		{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0},
		{0,1,1,1,1,8,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,8,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
		{0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0},
		{0,1,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,1,0},
		{0,1,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,1,0},
		{0,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,0,2,0,2,2,2,2,2,2,0,2,0,0,1,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,0,2,0,2,4,5,6,7,2,0,2,0,0,1,0,0,0,0,1,0},
		{0,1,1,1,1,1,1,0,0,2,0,2,2,2,2,2,2,0,2,0,0,1,1,1,1,1,1,0},
		{0,2,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1,0},
		{0,2,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,1,0},
		{2,2,2,2,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,2,2,2,2},
		{0,0,0,2,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,2,0,0,0},
		{0,0,0,2,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,2,0,0,0},
		{2,2,2,2,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,2,2,2,2},
		{0,2,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0},
		{0,2,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,2,0},
		{0,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,0},
		{0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0},
		{0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0},
		{0,1,0,0,1,8,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,8,1,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0}
	};

	maze= new int*[rows];
	for(i=0;i<rows;i++){
		maze[i]= new int[columns];
	}
	
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			maze[i][j]=mazeTemplate[i][j];
			// std::cout << maze[i][j] << " ";
		}
	}
}

void Maze::mazePrinter()
{
	int i;
	int j;

	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			switch(maze[i][j]){
				case 1: //Pellet
				std::cout << ". ";
				break;

				case 0: //Wall
				std::cout << "▒ ";
				break;

				case 2: //Empty Space
				std::cout << "  ";
				break;

				case 3: //Pacman
				std::cout << "C ";
				break;

				case 4: //Red ghost
				std::cout << "R ";
				break;

				case 5: //Blue Ghost
				std::cout << "B ";
				break;

				case 6: //Pink Ghost
				std::cout << "P ";
				break;

				case 7: //Orange Ghost
				std::cout << "O ";
				break;

				case 8:
				std::cout << "§ ";
			}
		}
		std::cout << std::endl;
	}
}

void Maze::mazeUpdate(int row, int column, char character)
{
	int i,j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			if(maze[i][j] == pac && (character == 'm' || character == 'M')){
				maze[i][j]=2;
			}else if(maze[i][j] == red && (character == 'r' || character == 'R')){
				maze[i][j]=2;
			}
		}
	}
	
	switch(character){
		case 'm':
		case 'M':
		maze[row][column]=pac;
		break;

		case 'p':
		case 'P':
		maze[row][column]=pink;
		break;

		case 'b':
		case 'B':
		maze[row][column]=blue;
		break;

		case 'r':
		case 'R':
		maze[row][column]=red;
		break;

		case 'o':
		case 'O':
		maze[row][column]=orange;
		break;
	}
}

//Returns the integer representing what is within a chosen tile of the maze
int Maze::getPosition(int row, int column){
	return maze[row][column];
}

//Changes a position within the array to an inputted value
void Maze::setPosition(int row, int column, int value){

	if(value >= 0 && value <= 8){
		maze[row][column] = value;
	}else{
		std::cout << "Error has occured in Maze::setPosition" << std::endl;
	}

}