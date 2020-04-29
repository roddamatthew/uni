#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <iostream>
#include "person.h"

using namespace std;

class aircraft
{
public:
	string name;
	person pilot, copilot;

	aircraft(string callsign,person thePilot,person theCoPilot);
	void setPilot(person thePilot);      // change the pilot
	person getPilot();
	void setCoPilot(person theCoPilot);  // change the co-pilot
	person getCoPilot();
	void printDetails();                 // print the callsign, a new line, the pilot name, a new line, the co-pilot name and a final newline.
};


#endif //AIRCRAFT_H