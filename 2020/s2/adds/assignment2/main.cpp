#include "Computer.h"
#include "Human.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
	Human* Matt;
	Computer* Comp;
	Referee* Ref;

	Matt = new Human("Matt");
	Comp = new Computer("Comp");
	Ref = new Referee();

	std::cout << Matt -> getName() << std::endl;
	std::cout << Comp -> getName() << std::endl;

	Ref -> refGame(Matt,Comp);

	return 0;
}