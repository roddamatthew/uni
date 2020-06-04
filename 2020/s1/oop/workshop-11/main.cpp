#include "animal.h"
#include "hunter.h"
#include "vegie.h"
#include "zoo.h"
#include "sort_by_animalID.h"
#include "sort_by_name.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	animal* panda;
	hunter* fox;
	vegie* giraffe;
	zoo* monarto;
	animal** numbers = new animal*[10];

	for(int i=0; i<10; i++){
		numbers[9-i] = new animal("Larry", 10);
	}

	animal* current;
	animal** currentarray;

	panda = new animal("Panda", 100);
	fox = new hunter("Fox", 45);
	giraffe = new vegie("Giraffe", 150);
	monarto = new zoo("Monarto", 3, 2);

	std::cout << "animal with ID: " << panda -> get_animalID() << " has the name: " << panda -> get_name() << " and a volume of: " << panda -> get_volume() << std::endl;
	std::cout << "hunter with ID: " << fox -> get_animalID() << " has the name: " << fox -> get_name() << " and a volume of: " << fox -> get_volume() << " has kills: " << fox -> get_kills() <<std::endl;
	std::cout << "vegie with ID: " << giraffe -> get_animalID() << " has the name: " << giraffe -> get_name() << " and a volume of: " << giraffe -> get_volume() << " and a favourite food: " << giraffe -> get_favourite_food() <<std::endl;

	std::cout << "zoo with name " << monarto -> get_name() << " has " << monarto -> get_number_of_animals() << " animals." << std::endl;
	std::cout << "The zoo contains the animals: " << std::endl;

	for(int i=0;i<5;i++){
		current = monarto -> get_animals()[i];
		std::cout << "animal with ID: " << current -> get_animalID() << " has the name: " << current -> get_name() << " and a volume of: " << current -> get_volume() << std::endl;
	}

	currentarray = monarto -> get_animals();

	for(int i=0; i<5; i++){
		std::cout << "animal with ID: " << currentarray[i] -> get_animalID() << " has the name: " << currentarray[i] -> get_name() << " and a volume of: " << currentarray[i] -> get_volume() << std::endl;
	}

	for(int i=0; i<10; i++){
	std::cout << numbers[i] -> get_name() << " " << numbers[i] -> get_animalID() << std::endl;

	}

	for(int i=0; i<10; i++){
	sort_by_animalID::sort(numbers, 10);
	std::cout << numbers[i] -> get_name() << " " << numbers[i] -> get_animalID() << std::endl;
	}


	return 0;
}