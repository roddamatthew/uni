#ifndef PAC_H
#define PAC_H

#include <iostream>
#include "entity.h"

using namespace std;

class Pac: public Entity //Subclass of Entity
{
private:
	int score;

public:
	Pac(); //Default Constructor
	void scorepellet(); //Increments score for a pellet
	void scoreghost(); //Increments score for a ghost
	int getscore();	//Returns score
};
#endif //PAC_H