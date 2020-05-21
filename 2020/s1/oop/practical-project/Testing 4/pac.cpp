#include <iostream>
#include <string.h>
#include "pac.h"

using namespace std;

Pac::Pac(int rowstart, int columnstart)
{
	row=rowstart;
	column=columnstart;
}

void Pac::movement(char direction, int rows, int columns)
{
	switch(direction){
		case 'W':
		case 'w':
		if(row>=1){
			row--;
		}else{
			row=rows-1;
		}
		
		break;

		case 'A':
		case 'a':
		if(column>=1){
			column--;
		}else{
			column=columns-1;
		}
		break;

		case 'S':
		case 's':
		if(row<rows-1){
			row++;
		}else{
			row=0;
		}
		break;

		case 'D':
		case 'd':
		if(column<columns-1){
			column++;
		}else{
			column=0;
		}
		break;
	}
}

int Pac::getrow()
{
	return row;
}

int Pac::getcolumn()
{
	return column;
}