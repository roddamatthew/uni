#include "Human.h"
#include <string>
#include <iostream>

using namespace std;

Human:: Human(string Name){
	name = Name;
	move = '0';
}

char Human:: makeMove(){
	std::cout << "Please enter your move: ";
	std::cin >> move ;
	return move;
}

string Human:: getName(){
	return name;
}