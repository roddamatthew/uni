#include <iostream>
#include "Musician.h"

int main(){
	Musician *musician1;
	std::string instrument;
	int experience;

	musician1 = new Musician();
	std::cout << musician1->get_instrument() << musician1->get_experience() << std::endl;

	musician1->~Musician();

	musician1 = new Musician("Flute",10);
	std::cout << musician1->get_instrument() << musician1->get_experience() << std::endl;

	musician1->~Musician();

	return 0;
}