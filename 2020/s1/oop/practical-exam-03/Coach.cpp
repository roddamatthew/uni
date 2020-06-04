#include "Person.h"
#include "Coach.h"
#include <string>

using namespace std;

int Coach::nextID = 0;

Coach::Coach(string n, int sl){
	name = n;
	occupation = "coach";
	serviceLength = sl;
	personID = currentID;
	currentID++;
}