#include <iostream>
#include <string.h>
#include "pac.h"
#include "entity.h"

using namespace std;

Pac::Pac(){
	score=0;
}

void Pac::scorepellet(){ //Increase score by 10, represents eating a pellet
	score=score+10;
}
	
void Pac::scoreghost(){ //Increase score by 200, represents eating a ghost
	score=score+200;
}

int Pac::getscore(){ //Return score variable
	return score;
}



