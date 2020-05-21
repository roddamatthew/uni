#include <iostream>
#include "maze.h"

using namespace std;

int main(){
	
	Maze* pacmap;

	pacmap = new Maze();

	pacmap->mazePrinter();

	return 0;
}