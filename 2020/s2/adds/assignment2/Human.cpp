#include "Human.h"
#include <string>
#include <iostream>

using namespace std;

HumanPlayer:: HumanPlayer(string Name){
	name = Name;
	move = '0';
}

char HumanPlayer:: makeMove(){
	std::cout << "Please enter your move: ";
	std::cin >> move ;
	return move;
}

string HumanPlayer:: getName(){
	return name;
}