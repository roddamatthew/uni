#include "ComputerPlayer.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

ComputerPlayer:: ComputerPlayer(string Name){
	name = Name;
	move = '0';
}

char ComputerPlayer:: makeMove(){
	std::cout << "Computer is deciding its move..." << std::endl;
	srand (time(NULL));
	int random = rand() % 4;
	
	if(random <= 1){
		move = 'R';
	}else if(random <= 2){
		move = 'S';
	}else{
		move = 'P';
	}
	return move;
}

string ComputerPlayer:: getName(){
	return name;
}