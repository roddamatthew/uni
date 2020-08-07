#include "Computer.h"
#include "Human.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
	Human* Matt;
	Computer* Computer;
	Referee* Ref;

	Matt = new Human("Matt");
	Computer = new Computer("Computer");
	Ref = new Referee();

	std::cout << Matt -> getName() << std::endl;
	std::cout << Computer -> getName() << std::endl;

	Ref -> refGame(Matt,Computer);

	return 0;
}