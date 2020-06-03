#include "animal.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	animal* panda;
	animal* fox;


	panda = new animal("Panda", 100);
	fox = new animal("Fox", 45);

	std::cout << "animal with ID: " << panda -> get_animalID() << " has the name: " << panda -> get_name() << " and a volume of: " << panda -> get_volume() << std::endl;
	std::cout << "animal with ID: " << fox -> get_animalID() << " has the name: " << fox -> get_name() << " and a volume of: " << fox -> get_volume() << std::endl;


	return 0;
}