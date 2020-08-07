#include "Human.h"
#include <string>
#include <iostream>

using namespace std;

HumanPlayer:: HumanPlayer(){
	string input;
	int length;
	char currentmove;

	std::cout << "Please enter your strategy: ";
	std::cin >> input ;

	length = input.at(0) - 48;
	for(int i=0; i<length; i++){
		std::cin >> currentmove;
		moves.push_back(currentmove);
		std::cout << moves[i] << " ";
	}

}

char HumanPlayer:: makeMove(){
	char thismove = moves[0];
	moves.erase(moves.begin());
	moves.push_back(thismove);
	return thismove;
}