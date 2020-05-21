#include <iostream>
#include <string.h>
#include "pac.h"

using namespace std;

Pac::Pac(int rowstart, int columnstart)
{
	row=rowstart;
	column=columnstart;
}

void Pac::movement(char direction)
{
	switch(direction){
		case 'W':
		case 'w':
		row--;
		break;

		case 'A':
		case 'a':
		column--;
		break;

		case 'S':
		case 's':
		row++;
		break;

		case 'D':
		case 'd':
		column++;
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