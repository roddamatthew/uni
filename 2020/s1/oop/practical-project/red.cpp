#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "red.h"

using namespace std;

Red::Red(){
}

void Red::chase(){

}

void Red::scatter(){

}

void Red::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,12);

	if(getrow() == 10 && getcolumn() == 12){
		ate = false;
	}
}