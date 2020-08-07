#include "Computer.h"
#include "Human.h"
#include "Referee.h"

#include <iostream>

Referee:: Referee(){};

char Referee:: refGame(HumanPlayer& player1, ComputerPlayer& player2){
	char move1 = player1.makeMove();
	char move2 = player2.makeMove();
	
	if(move1 == move2){
		// std::cout << "Both Players chose the same move! You drew." << std::endl;
		return 'T';
	}else if(move1 == 'R' && move2 == 'P'){
		//std::cout << "Player 1 chose rock, Player 2 chose paper. Player 1 lost." << std::endl;
		return 'L';
	}else if(move1 == 'R' && move2 == 'S'){
		//std::cout << "Player 1 chose rock, Player 2 chose scissors. Player 1 won!" << std::endl;
		return 'W';
	}else if(move1 == 'P' && move2 == 'S'){
		//std::cout << "Player 1 chose paper, Player 2 chose scissors. Player 1 lost." << std::endl;
		return 'L';
	}else if(move1 == 'P' && move2 == 'R'){
		//std::cout << "Player 1 chose paper, Player 2 chose rock. Player 1 won!" << std::endl;
		return 'W';
	}else if(move1 == 'S' && move2 == 'R'){
		//std::cout << "Player 1 chose scissors, Player 2 chose rock. Player 1 lost." << std::endl;
		return 'L';
	}else if(move1 == 'S' && move2 == 'P'){
		//std::cout << "Player 1 chose scissors, Player 2 chose paper. Player 1 won!" << std::endl;
		return 'W';
	}
}