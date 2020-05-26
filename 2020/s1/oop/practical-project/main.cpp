#include <iostream>
#include "maze.h"
#include "pac.h"
#include "entity.h"
#include "ghost.h"
#include "red.h"
#include "blue.h"
#include "pink.h"
#include "orange.h"


using namespace std;

int main(){
	int i,j;

	int size = 12;
	int rows = 31;
	int columns = 28;
	char input;
	bool gameover = false;
	bool win = false;
	int nPellets;
	
	Maze* pacmap;
	Pac* pacman;
	Entity* collision;
	Red* red;

	pacmap = new Maze();
	
	pacman = new Pac();
	pacman -> setrow(22);
	pacman -> setcolumn(13);

	collision = new Entity();

	red = new Red();

	red -> setrow(10);
	red -> setcolumn(13);

	while(gameover == false && win == false){
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

		if(pacmap -> getPosition(collision -> getrow(), collision -> getcolumn()) != 0){ //If collision doesnt collide:
			pacman -> pacMovement(input); //Move pacman
		}

		if(pacmap -> getPosition(pacman -> getrow(), pacman -> getcolumn()) == 8){
			pacman -> scoreSuper();
		}

		if(pacman -> getSuper() == 0){
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
		}// else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;			
		// }
		}else{
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				pacman -> scoreGhost();
				red -> eaten();
		}// else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;			
		// }
		}

		if(red -> getAte() == false){
			red -> scared(pacman -> getrow(), pacman -> getcolumn());
		}else if (red -> getAte() == true){
			red -> eaten();
		}

		if(pacmap -> getPosition(pacman -> getrow(), pacman -> getcolumn()) == 1){
			pacman -> scorePellet();
		}

		nPellets = 0;

		for(i = 0; i < 31; i++){
			for(j = 0; j < 28; j++){
				if(pacmap -> getPosition(i,j) == 1){
					nPellets++;

				}
			}
		}

		if(nPellets == 0){
			win = true;
			std::cout << "You win" << std::endl;
		}

		if(pacman -> getSuper() == 0){
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
		}// else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;			
		// }
		}else{
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				pacman -> scoreGhost();
				red -> eaten();
		}// else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;
		// }else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
		// 	gameover = true;
		//  std::cout << "Gamover! You Lost!" << std::endl;			
		// }
		}
	}

	pacman -> ~Pac();
	collision -> ~Entity();

	return 0;
}