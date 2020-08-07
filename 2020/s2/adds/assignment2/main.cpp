#include "Computer.h"
#include "Human.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
	HumanPlayer Matt;
	ComputerPlayer Comp;
	Referee Ref;
	int numberofgames=4;

	for(int i=0; i< numberofgames; i++){
		std::cout << Ref.refGame(Matt,Comp) << std::endl;
		std::cout << Matt.getCounter() << std::endl;
	}

	return 0;
}