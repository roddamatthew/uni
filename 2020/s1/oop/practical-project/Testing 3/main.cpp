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
	Pac* pacman;
	Pac* collision;

	pacmap = new Maze();
	pacman = new Pac(21,12);

	while(gameover==false){
		//Print the map for the user
		pacmap->mazeUpdate(pacman->getrow(), pacman->getcolumn() );
		pacmap->mazePrinter();

		std::cin >> input;
		
		collision = new Pac(pacman->getrow(), pacman->getcolumn());
		collision -> movement(input);

		if(pacmap -> isWall(collision->getrow(), collision->getcolumn()) == false){
			pacman->movement(input);
		}
	}

	return 0;
}