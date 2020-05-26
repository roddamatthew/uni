#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "orange.h"

using namespace std;

Orange::Orange(){
}

void Orange::chase(){

}

void Orange::scatter(){

}

void Orange::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,15);

	if(getrow() == 10 && getcolumn() == 15){
		ate = false;
	}
}