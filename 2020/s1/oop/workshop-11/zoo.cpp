#include "animal.h"
#include "hunter.h"
#include "vegie.h"
#include "zoo.h"

using namespace std;

zoo::zoo(string n, int cows, int lions){
	name = n;
	number_of_animals = cows + lions;

	animals = new animal*[number_of_animals];

	int i=0;

	for(i = 0; i < cows; i++){
		animals[i] = new vegie("Daisy", 100);
	}

	for(i = cows; i < number_of_animals; i++){
		animals[i] = new hunter("Clarence", 50);
	}
}

void zoo::set_name(string n){
	name = n;
}

string zoo::get_name(){
	return name;
}

int zoo::get_number_of_animals(){
	return number_of_animals;
}

animal** zoo::get_animals(){
	return animals;
}