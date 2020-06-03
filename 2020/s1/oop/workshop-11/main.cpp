#include "Animal.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	Animal* panda;
	Animal* fox;


	panda = new Animal("Panda", 100);
	fox = new Animal("Fox", 45);

	std::cout << "Animal with ID: " << panda -> get_animalID() << " has the name: " << panda -> get_name() << " and a volume of: " << panda -> get_volume() << std::endl;
	std::cout << "Animal with ID: " << fox -> get_animalID() << " has the name: " << fox -> get_name() << " and a volume of: " << fox -> get_volume() << std::endl;


	return 0;
}