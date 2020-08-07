#include "Computer.h"
#include "Human.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
	HumanPlayer Matt = HumanPlayer();
	ComputerPlayer Comp = ComputerPlayer();
	Referee* Ref;
	int numberofgames=4;

	Ref = new Referee();

	for(int i=0; i< numberofgames; i++){
		std::cout << Ref -> refGame(Matt,Comp) << std::endl;
	}

	return 0;
}