#include <iostream>
#include <string.h>
#include "pac.h"

using namespace std;

Pac::Pac(int x, int y)
{
	x_pos=x;
	y_pos=y;
}

void Pac::movement(char direction)
{
	switch(direction){
		case 'W':
		case 'w':
		y_pos--;
		break;

		case 'A':
		case 'a':
		x_pos--;
		break;

		case 'S':
		case 's':
		y_pos++;
		break;

		case 'D':
		case 'd':
		x_pos++;
		break;
	}
}

int Pac::getx_pos()
{
	return x_pos;
}

int Pac::gety_pos()
{
	return y_pos;
}