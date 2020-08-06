#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
	HumanPlayer* Matt;
	ComputerPlayer* Computer;
	Referee* Ref;

	Matt = new HumanPlayer("Matt");
	Computer = new ComputerPlayer("Computer");
	Ref = new Referee();

	std::cout << Matt -> getName() << std::endl;
	std::cout << Computer -> getName() << std::endl;

	Ref -> refGame(Matt,Computer);

	return 0;
}