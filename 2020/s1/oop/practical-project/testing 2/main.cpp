#include <iostream>
#include "maze.h"
#include "pac.h"

using namespace std;

int main(){
	int i,j;

	int size=12;
	char input;
	bool gameover=false;
	
	Maze* pacmap;
	// Pac* pacman;

	pacmap = new Maze();
	// pacman = new Pac(size/2,size/2);

	// while(gameover==false){
	pacmap->mazePrinter();
	// 	std::cout << pacmap->wallChecker(0,0) << std::endl;

	// 	std::cin >> input;
	// 	pacman->movement(input);

	// 	pacmap->mazeUpdate(pacman->getx_pos(), pacman->gety_pos(), 3);
	// }

	return 0;
}