#ifndef HUNTER_H
#define HUNTER_H

#include <string>
#include <iostream>
#include <vector>
#include "Animal.h"

using namespace std;

class Hunter : public Animal
{
public:
	string * kills;
	int n_kills;

	Hunter(string aSpecies);	
	void record_kill(string kill);   // add a new kill to the end of the hunter's list of kills
	int numberOfKills();             // how many kills have been recorded
	string * get_kills();

};
#endif //HUNTER_H