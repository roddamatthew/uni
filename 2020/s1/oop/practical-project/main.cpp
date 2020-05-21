#include <iostream>
#include "maze.h"
#include "pac.h"
#include "entity.h"
#include "ghost.h"

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
	Entity* collision;
	Ghost* red;

	pacmap = new Maze();
	
	pacman = new Pac();
	pacman -> setrow(22);
	pacman -> setcolumn(13);

	collision = new Entity();

	red = new Ghost();

	red -> setrow(10);
	red -> setcolumn(13);

	while(gameover == false){
		std::cout << "Score: "<< pacman -> getscore() << std::endl; //Display Score
		std::cout << "row: " << pacman -> getrow() << " column: " << pacman -> getcolumn() << std::endl; //Display pacman position (for debugging)

		//Print the map for the user
		pacmap -> mazeUpdate(pacman->getrow(), pacman->getcolumn(), 'm'); //Update maze position of pacman
		pacmap -> mazeUpdate(red->getrow(), red->getcolumn(), 'r'); //Update maze position of red ghost
		// pacmap -> mazeUpdate(blue->getrow(), blue->getcolumn(), blue); //Update maze position of blue ghost
		// pacmap -> mazeUpdate(pink->getrow(), pink->getcolumn(), pink); //Update maze position of pink ghost
		// pacmap -> mazeUpdate(orange->getrow(), orange->getcolumn(), orange); //Update maze position of orange ghost
		
		pacmap->mazePrinter(); //Print the map to the terminal

		std::cin >> input; //Get an input direction from user
		
		collision -> setrow(pacman->getrow()); //set a collision entities position to the pacman position + movement and check if that collides with wall
		collision -> setcolumn(pacman->getcolumn());
		collision -> movement(input,rows,columns);

		if(pacmap -> wallCheck(collision -> getrow(), collision -> getcolumn()) == false){ //If collision doesnt collide:
			pacman -> movement(input, rows, columns); //Move pacman
		}

		red -> scared(pacman -> getrow(), pacman -> getcolumn());

		if(pacmap -> pelletCheck(pacman -> getrow(), pacman -> getcolumn()) == true){
			pacman -> scorepellet();
		}
	}

	pacman -> ~Pac();
	collision -> ~Entity();

	return 0;
}