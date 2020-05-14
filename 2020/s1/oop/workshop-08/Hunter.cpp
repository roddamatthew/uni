#include <iostream>
#include <vector>
#include "Hunter.h"
#include "Animal.h"

using namespace std;

Hunter::Hunter(string aSpecies){
	species = aSpecies;
	name = "?";
	id = currentID;
	n_kills=0;
	kills = new string[10];

	currentID++;
}

void Hunter::record_kill(string kill){
	kills[n_kills] = kill;
	n_kills++;
}

int Hunter::numberOfKills(){
	return n_kills;
}

// implement ONE of the following
string * Hunter::get_kills(){
	return kills;
}