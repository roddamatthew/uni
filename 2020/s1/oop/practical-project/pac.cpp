#include <iostream>
#include <string.h>
#include "pac.h"
#include "entity.h"

using namespace std;

Pac::Pac(){
	score=0;
	superMoves=0;
}

void Pac::scorePellet(){ //Increase score by 10, represents eating a pellet
	score=score+10;
}
	
void Pac::scoreGhost(){ //Increase score by 200, represents eating a ghost
	score=score+200;
}

void Pac::scoreSuper(){ //Increase score by 10, represents eating a pellet
	score=score+10;
	superMoves=30;
}

int Pac::getscore(){ //Return score variable
	return score;
}

int Pac::getSuper(){
	return superMoves;
}

void Pac::pacMovement(char direction){ //Movement specific to pacman

	movement(direction,31,28);

	if(superMoves == 0){

	}else{
		superMoves--;
	}
	std::cout << "Number of Supermoves: " << superMoves << std::endl;
}