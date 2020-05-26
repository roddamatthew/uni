#ifndef PAC_H
#define PAC_H

#include <iostream>
#include "entity.h"

using namespace std;

class Pac: public Entity //Subclass of Entity
{
private:
	int score;
	int superMoves;

public:
	Pac(); //Default Constructor
	void scorePellet(); //Increments score for a pellet
	void scoreGhost(); //Increments score for a ghost
	void scoreSuper(); //Increments score and makes Pacman invincible
	int getSuper(); //Returns the number of superMoves
	int getscore();	//Returns score
	void pacMovement(char direction); //Movement specific to pacman
};
#endif //PAC_H