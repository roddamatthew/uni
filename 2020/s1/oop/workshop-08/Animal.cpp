#include <iostream>
#include "Animal.h"

using namespace std;

int Animal::currentID = 0;

Animal::Animal(){
	species = "?";
	name = "?";
	id = currentID;

	currentID++;
}

Animal::Animal(string aSpecies){
	species = aSpecies;
	name = "?";
	id=currentID;

	currentID++;
}

void Animal::set_name(string aName){
	name = aName;
}

string Animal::get_species(){
	return species;
}   
string Animal::get_name(){
	return name;
}

int Animal::get_ID(){
	return id;
}