#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "pink.h"

using namespace std;

Pink::Pink(){
}

void Pink::chase(){

}

void Pink::scatter(){

}

void Pink::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,14);

	if(getrow() == 10 && getcolumn() == 14){
		ate = false;
	}
}