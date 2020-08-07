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
}

char HumanPlayer:: makeMove(){
	int length = moves.size();
	char thismove;
	
	if(counter == length){
		counter = 0;
	}

	thismove = moves[counter];

	counter++;
	return thismove;
}

int HumanPlayer:: getCounter(){
	return counter;
}