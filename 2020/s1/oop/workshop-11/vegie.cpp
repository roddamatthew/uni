#include <string>
#include "animal.h"
#include "vegie.h"

using namespace std;

int vegie::nextID = 100;

vegie::vegie(string n, int v){
	name = n;
	volume = v;
	animalID = nextID;
	favourite_food = "?";

	nextID++;
}

void vegie::set_favourite_food(string n){
	favourite_food = n;
}

string vegie::get_favourite_food(){
	return favourite_food;
}

string vegie::get_name(){
	string str;
	str.append("Safe: ");
	str.append (name);

	return str;
}