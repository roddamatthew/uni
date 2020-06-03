#include "animal.h"
#include <string>

using namespace std;

int animal::currentID = 0;

animal::animal(string n, int v){
	name = n;
	volume = v;
	animalID = currentID;
	currentID++;
}

animal::animal(){}

void animal::set_name(string n){
	name = n;
}

string animal::get_name(){
	return name;
}

void animal::set_volume(int v){
	volume = v;
}

int animal::get_volume(){
	return volume;
}

int animal::get_animalID(){
	return animalID;
}