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
	int turnCounter = 0;
	
	Maze* map;
	Pac* pacman;
	Entity* collision;
	Red* red;
	Blue* blue;
	Pink* pink;
	Orange* orange;

	// Creating a new maze object called map for storing the positions of ghosts and pacman.
	map = new Maze();
	
	//Creating a new pacman object and setting the start position to (22,13)
	pacman = new Pac();
	pacman -> setrow(22);
	pacman -> setcolumn(13);

	//Initiliazing an Entity for testing collision with later
	collision = new Entity();

	//Creating the 4 ghosts
	red = new Red();
	blue = new Blue();
	pink = new Pink();
	orange = new Orange();

	red -> setrow(13);
	red -> setcolumn(12);

	blue -> setrow(13);
	blue -> setcolumn(13);

	pink -> setrow(13);
	pink -> setcolumn(14);

	orange -> setrow(13);
	orange -> setcolumn(15);


	while(gameover == false && win == false){
		std::cout << "Score: "<< pacman -> getscore() << std::endl; //Display Score
		std::cout << "row: " << pacman -> getrow() << " column: " << pacman -> getcolumn() << std::endl; //Display pacman position (for debugging) DELETE FOR FINAL PRES

		//Update positions of all the ghosts and pacman in the maze for printing
		map -> mazeUpdate(pacman -> getrow(), pacman->getcolumn(), 'm'); //Update maze position of pacman
		map -> mazeUpdate(red -> getrow(), red -> getcolumn(), 'r'); //Update maze position of red ghost
		map -> mazeUpdate(blue -> getrow(), blue -> getcolumn(), 'b'); //Update maze position of blue ghost
		map -> mazeUpdate(pink -> getrow(), pink -> getcolumn(), 'p'); //Update maze position of pink ghost
		map -> mazeUpdate(orange -> getrow(), orange -> getcolumn(), 'o'); //Update maze position of orange ghost
		
		//Print the map to the terminal
		map -> mazePrinter();


		//PACMAN MOVEMENT:

		std::cout << "Enter the direction you would like pacman to move (WASD): ";
		std::cin >> input; //Get an input direction from user
		
		//Set the collision entity to the pacman position and check if the movement would be into a wall
		collision -> setrow(pacman -> getrow());
		collision -> setcolumn(pacman -> getcolumn());
		collision -> movement(input, rows, columns);

		if(map -> getPosition(collision -> getrow(), collision -> getcolumn()) != 0){ //If collision doesnt collide:
			pacman -> pacMovement(input); //Move pacman
		}

		if(map -> getPosition(pacman -> getrow(), pacman -> getcolumn()) == 8){			//If pacman eats a superpellet call scoreSuper()
			pacman -> scoreSuper();
		}else if(map -> getPosition(pacman -> getrow(), pacman -> getcolumn()) == 1){	 //If pacmans new position has a pellet, increase the score
			pacman -> scorePellet();
		}

		//If pacman and ghost are in the same tile, eat the ghost if pacman has supermoves, or lose if pacman does not have supermoves
		if(pacman -> getSuper() == 0){
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
			}else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
			}else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
			}else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;			
			}
		}else{
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				pacman -> scoreGhost();
				red -> setAte();
			}else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
				pacman -> scoreGhost();
				blue -> setAte();
			}else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
				pacman -> scoreGhost();
				pink -> setAte();
			}else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
				pacman -> scoreGhost();
				orange -> setAte();		
			}
		}

		//GHOST MOVEMENT:

			//Red:
			if(turnCounter == 5){					//Spawns at turn 5
					red -> setrow(10); 				//spawns in at (10,12)
					red -> setcolumn(12);
			}else if(turnCounter > 5){ 				//After spawning
				if(red -> getAte() == true){		//If eaten by pacman
					red -> eaten();					//call eaten function
				}else if(pacman -> getSuper() > 0){	//If pacman has supermoves
					red -> scared();				//call scared function
				}else if(turncounter % 27 > 0 && turncounter % 27 < 8){	//Every 27 turn cycle, first 7 moves are scatter
					red -> scatter();				//call scatter fucntion
				}else{
					red -> chase();					//moves 8 - 27 are chase pacman
				}
			}

			//Blue:
			if(turnCounter == 15){ //Spawns at turn 15
					blue -> setrow(10); //spawns in at (10,13)
					blue -> setcolumn(13);
			}else if(turnCounter > 15){
				if(blue -> getAte() == true){
					blue -> eaten();
				}else if(pacman -> getSuper() > 0){
					blue -> scared();
				}else if(turncounter % 27 > 0 && turncounter % 27 < 8){
					blue -> scatter();
				}else{
					blue -> chase();
				}
			}

			//Pink:
			if(turnCounter == 25){ //Spawns at turn 25
					pink -> setrow(10); //spawns in at (10,14)
					pink -> setcolumn(14);
			}else if(turnCounter > 25){
				if(pink -> getAte() == true){
					pink -> eaten();
				}else if(pacman -> getSuper() > 0){
					pink -> scared();
				}else if(turncounter % 27 > 0 && turncounter % 27 < 8){
					pink -> scatter();
				}else{
					pink -> chase();
				}
			}

			//Orange:
			if(turnCounter == 35){ //Spawns at turn 35
					orange -> setrow(10); //spawns in at (10,15)
					orange -> setcolumn(15);
			}else if(turnCounter > 35){
				if(orange -> getAte() == true){
					orange -> eaten();
				}else if(orange -> getSuper() > 0){
					orange -> scared();
				}else if(turncounter % 27 > 0 && turncounter % 27 < 8){
					orange -> scatter();
				}else{
					orange -> chase();
				}
			}


		//Repeated from above: If pacman and ghost are in the same tile, eat the ghost if pacman has supermoves, or lose if pacman does not have supermoves
		if(pacman -> getSuper() == 0){
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
			}else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
			}else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;
			}else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
				gameover = true;
				std::cout << "Gamover! You Lost!" << std::endl;			
			}
		}else{
			if(pacman -> getrow() == red -> getrow() && pacman -> getcolumn() == red -> getcolumn()){
				pacman -> scoreGhost();
				red -> setAte();
			}else if(pacman -> getrow() == blue -> getrow() && pacman -> getcolumn() == blue -> getcolumn()){
				pacman -> scoreGhost();
				blue -> setAte();
			}else if(pacman -> getrow() == pink -> getrow() && pacman -> getcolumn() == pink -> getcolumn()){
				pacman -> scoreGhost();
				pink -> setAte();
			}else if(pacman -> getrow() == orange -> getrow() && pacman -> getcolumn() == orange -> getcolumn()){
				pacman -> scoreGhost();
				orange -> setAte();		
			}
		}

		//Finding how many pellets are left within the array
		
		nPellets = 0;
		
		for(i = 0; i < 31; i++){
			for(j = 0; j < 28; j++){
				if(map -> getPosition(i,j) == 1){
					nPellets++;

				}
			}
		}

		//If the number of pellets left in the array is 0, then pacman wins
		if(nPellets == 0){
			win = true;
			std::cout << "You win" << std::endl;
		}

		turnCounter++;
	}

	pacman -> ~Pac();
	collision -> ~Entity();

	return 0;
}