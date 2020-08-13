#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Referee.h"

#include <iostream>

Referee:: Referee(){};

char Referee:: refGame(Player& player1, Player& player2){
	char move1 = player1.makeMove();
	char move2 = player2.makeMove();
	
	if(move1 == move2){
		return 'T';
	}else if(move1 == 'R' && move2 == 'P'){
		return 'L';
	}else if(move1 == 'R' && move2 == 'S'){
		return 'W';
	}else if(move1 == 'P' && move2 == 'S'){
		return 'L';
	}else if(move1 == 'P' && move2 == 'R'){
		return 'W';
	}else if(move1 == 'S' && move2 == 'R'){
		return 'L';
	}else if(move1 == 'S' && move2 == 'P'){
		return 'W';
	}else{
		std::cout << "error has occurred in ref" << std::endl;
		return 'E';
	}
}