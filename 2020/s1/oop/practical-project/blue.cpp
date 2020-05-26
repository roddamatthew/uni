#include <iostream>
#include <cstdlib>
#include "ghost.h"
#include "entity.h"
#include "maze.h"
#include "blue.h"

using namespace std;

Blue::Blue(){
}

void Blue::chase(){

}

void Blue::scatter(){

}

void Blue::eaten(){
	if(ate == false){
		lastDirection = 0;
		setAte();
	}
	
	pathing(10,13);

	if(getrow() == 10 && getcolumn() == 13){
		ate = false;
	}
}