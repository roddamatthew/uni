#include "Player.h"
#include <vector>

Player :: Player (){
	counter = 0;
}

char Player :: makeMove(){
	int length = moves.size();
	char thismove;
	
	if(counter == length){
		counter = 0;
	}

	thismove = moves[counter];

	counter++;
	return thismove;
}

int Player :: getCounter(){
	return counter;
}