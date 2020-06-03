#include "Animal.h"
#include <string>

using namespace std;

int Animal::currentID = 0;

Animal::Animal(string n, int v){
	name = n;
	volume = v;
	animalID = currentID;
	currentID++;
}

void Animal::set_name(string n){
	name = n;
}

string Animal::get_name(){
	return name;
}

void Animal::set_volume(int v){
	volume = v;
}

int Animal::get_volume(){
	return volume;
}

int Animal::get_animalID(){
	return animalID;
}