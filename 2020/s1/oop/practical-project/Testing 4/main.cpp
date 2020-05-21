#include <iostream>
#include "maze.h"
#include "pac.h"
#include "score.h"

using namespace std;

int main(){
	int i,j;

	int size = 12;
	int rows = 31;
	int columns = 28;
	char input;
	bool gameover = false;
	
	Maze* pacmap;
	Pac* pacman;
	Pac* collision;
	Score* score;

	pacmap = new Maze(rows,columns);
	pacmap -> mazePrinter();
	pacman = new Pac(22,13);
	score = new Score();

	int pellets = pacmap -> pelletUpdate();

	while(gameover == false){
		score -> printScore();

		//Print the map for the user
		pacmap->mazeUpdate(pacman->getrow(), pacman->getcolumn() );
		
		if(pellets > pacmap->pelletUpdate() ){
			pellets = pacmap->pelletUpdate();
			score -> pellet();
		}
		
		pacmap->mazePrinter();

		std::cin >> input;
		
		collision = new Pac(pacman->getrow(), pacman->getcolumn());
		collision -> movement(input,rows,columns);

		if(pacmap -> isWall(collision -> getrow(), collision -> getcolumn()) == false){
			pacman -> movement(input, rows, columns);
		}
	}

	return 0;
}