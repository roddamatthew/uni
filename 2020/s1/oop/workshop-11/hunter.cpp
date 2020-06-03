#include "hunter.h"
#include <string>
#include <iostream>

using namespace std;

int hunter::nextID = 1000;

hunter::hunter(string n, int v){
	name = n;
	volume = v;
	animalID = nextID;
	kills = 0;

	nextID++;
}

void hunter::set_kills(int n){
	kills = n;
}

int hunter::get_kills(){
	return kills;
}

string hunter::get_name(){
	string str;
	str.append("Hunter: ");
	str.append (name);

	return str;
}