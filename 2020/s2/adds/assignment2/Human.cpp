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

	std::cout << "Please enter your strategy: ";
	std::cin >> input ;

	length = input.at(0) - 48;
	std::cout << "Length of the player moves is: "<< length << std::endl;

	for(int i=0; i<length; i++){
		std::cin >> currentmove;
		moves.push_back(currentmove);
		std::cout << moves[i] << " ";
	}
	std::cout << std::endl;
}

char HumanPlayer:: makeMove(){
	int length = moves.size();
	char thismove;

	std::cout << "Counter value is: " << counter << std::endl;
	std::cout << "Length of moves is " << length << std::endl;
	
	if(counter == length -1){
		counter = 0;
	}

	thismove = moves[counter];
	std::cout << "makemove is going to return the move: " << thismove << std::endl;

	counter++;
	std::cout << "Counter value is: " << counter << std::endl;
	return thismove;
}

int HumanPlayer:: getCounter(){
	return counter;
}