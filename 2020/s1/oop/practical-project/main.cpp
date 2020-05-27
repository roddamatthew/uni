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
		map -> mazeUpdate(pacman -> getrow(), pacman->getcolumn(), 'm', 0,0); //Update maze position of pacman
		map -> mazeUpdate(red -> getrow(), red -> getcolumn(), 'r', red -> getPellet(), red -> getState()); //Update maze position of red ghost
		map -> mazeUpdate(blue -> getrow(), blue -> getcolumn(), 'b', blue -> getPellet(), blue -> getState()); //Update maze position of blue ghost
		map -> mazeUpdate(pink -> getrow(), pink -> getcolumn(), 'p', pink -> getPellet(), pink -> getState()); //Update maze position of pink ghost
		map -> mazeUpdate(orange -> getrow(), orange -> getcolumn(), 'o', orange -> getPellet(), orange -> getState()); //Update maze position of orange ghost
		
		//Print the map to the terminal
		map -> mazePrinter(red -> getState(), blue -> getState(), pink -> getState(), orange -> getState());


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

		if(map -> getPosition(pacman -> getrow(), pacman -> getcolumn()) == 8){			//If pacman eats a superpellet call scoreSuper
			pacman -> scoreSuper();
		}else if(map -> getPosition(pacman -> getrow(), pacman -> getcolumn()) == 1){	 //If pacmans new position has a pellet, increase the score
			pacman -> scorePellet();
		}

		//PACMAN COLLIDES WITH GHOST

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
					red -> setState(0);
					map -> setPosition(13,12,2);	//Removing the old ghost position
			}else if(turnCounter > 5){ 				//After spawning
				if(red -> getAte() == true){		//If eaten by pacman
					red -> eaten();					//call eaten function
					red -> setState('e');
				}else if(pacman -> getSuper() > 0){	//If pacman has supermoves
					red -> scared();	
					red -> setState('f');			//call scared function
				}else if(turnCounter % 27 > 0 && turnCounter % 27 < 8){	//Every 27 turn cycle, first 7 moves are scatter
					red -> scatter();				//call scatter fucntion
					red -> setState(0);
				}else{
					red -> chase(pacman -> getrow(), pacman -> getcolumn());					//moves 8 - 27 are chase pacman
					red -> setState(0);
				}
			}

			//Blue:
			if(turnCounter == 15){ //Spawns at turn 15
					blue -> setrow(10); //spawns in at (10,13)
					blue -> setcolumn(13);
					blue -> setState(0);
					map -> setPosition(13,13,2);
			}else if(turnCounter > 15){
				if(blue -> getAte() == true){
					blue -> eaten();
					blue -> setState('e');
				}else if(pacman -> getSuper() > 0){
					blue -> scared();
					blue -> setState('f');
				}else if(turnCounter % 27 > 0 && turnCounter % 27 < 8){
					blue -> scatter();
					blue -> setState(0);
				}else{
					blue -> chase(pacman -> getrow(), pacman -> getcolumn(), pacman -> getLastDirection(), red -> getrow(), red -> getcolumn());
					blue -> setState(0);
				}
			}

			//Pink:
			if(turnCounter == 25){ //Spawns at turn 25
					pink -> setrow(10); //spawns in at (10,14)
					pink -> setcolumn(14);
					pink -> setState(0);
					map -> setPosition(13,14,2);
			}else if(turnCounter > 25){
				if(pink -> getAte() == true){
					pink -> eaten();
					pink -> setState('e');
				}else if(pacman -> getSuper() > 0){
					pink -> scared();
					pink -> setState('f');
				}else if(turnCounter % 27 > 0 && turnCounter % 27 < 8){
					pink -> scatter();
					pink -> setState(0);
				}else{
					pink -> chase(pacman -> getrow(), pacman -> getcolumn(), pacman -> getLastDirection());
					pink -> setState(0);
				}
			}

			//Orange:
			if(turnCounter == 35){ //Spawns at turn 35
					orange -> setrow(10); //spawns in at (10,15)
					orange -> setcolumn(15);
					orange -> setState(0);
					map -> setPosition(13,15,2);
			}else if(turnCounter > 35){
				if(orange -> getAte() == true){
					orange -> eaten();
					orange -> setState('e');
				}else if(pacman -> getSuper() > 0){
					orange -> scared();
					orange -> setState('f');
				}else if(turnCounter % 27 > 0 && turnCounter % 27 < 8){
					orange -> scatter();
					orange -> setState(0);
				}else{
					orange -> chase(pacman -> getrow(), pacman -> getcolumn());
					orange -> setState(0);
				}
			}

			//Setting ghosts onPellet variable to the type of tile they now occupy in the map so it can be replaced after their next move.

			red -> setPellet(map -> getPosition(red -> getrow(), red -> getcolumn()));
			blue -> setPellet(map -> getPosition(blue -> getrow(), blue -> getcolumn()));
			pink -> setPellet(map -> getPosition(pink -> getrow(), pink -> getcolumn()));
			orange -> setPellet(map -> getPosition(orange -> getrow(), orange -> getcolumn()));

		//PACMAN COLLIDES WITH GHOST AFTER GHOSTS MOVE:

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
	red -> ~Red();
	blue -> ~Blue();
	pink -> ~Pink();
	orange -> ~Orange();

	return 0;
}