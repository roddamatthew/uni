#include "Player.h"
#include "Human.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

HumanPlayer:: HumanPlayer(){
	counter = 0;
	string input;
	int length;
	char currentmove;

	std::cin >> input;

	length = input.at(0) - 48;

	for(int i=0; i<length; i++){
		std::cin >> currentmove;
		moves.push_back(currentmove);
	}

	std::cout << "Human Player's moves are: ";
	for(int i=0; i<length; i++){
		std::cout << moves[i] << " ";
	}
	std::cout << std::endl;
}