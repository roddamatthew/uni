#include <iostream>
#include "Animal.h"
#include "Hunter.h"
#include <vector>

int main(){
	Animal* barry;
	Hunter* larry;

	barry = new Animal("Bird");

	barry -> set_name("Barry");

	std::cout << "Animal object of species: " << barry -> get_species() << " has the name: " << barry -> get_name() << " with ID: " << barry -> get_ID() << std::endl;

	larry = new Hunter("Cheetah");

	larry -> set_name("Larry");
	larry -> record_kill("Mouse");

	std::cout << "Hunter object of species: " << larry -> get_species() << " has the name: " << larry -> get_name() << " with ID: " << larry -> get_ID() << std::endl;
	std::cout << "Hunter has killed: " << larry -> numberOfKills() << " Of the animals: " << std::endl;

	for(int i=0; i < larry -> numberOfKills(); i++){
		std::cout << larry -> get_kills()[i] << std::endl;
	}

	delete larry;
	delete barry;

	return 0;
}