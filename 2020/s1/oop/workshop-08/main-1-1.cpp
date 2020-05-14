#include <iostream>
#include "Animal.h"

int main(){
	Animal* barry;
	Animal* larry;

	barry = new Animal("Cheetah");

	barry -> set_name("Barry");

	std::cout << "Animal object of species: " << barry -> get_species() << " has the name: " << barry -> get_name() << " with ID: " << barry -> get_ID() << std::endl;

	larry = new Animal("Cheetah");

	larry -> set_name("Larry");

	std::cout << "Animal object of species: " << larry -> get_species() << " has the name: " << larry -> get_name() << " with ID: " << larry -> get_ID() << std::endl;

	delete larry;
	delete barry;

	return 0;
}