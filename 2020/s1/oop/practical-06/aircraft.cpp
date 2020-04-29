#include <iostream>
#include "person.h"
#include "aircraft.h"

using namespace std;

aircraft::aircraft(string callsign, person thePilot,person theCoPilot)
{
	person *pilot, *copilot;
	pilot = new person();
	copilot = new person();

	name=callsign;
	pilot=&thePilot;
	copilot=&theCoPilot;
}

string aircraft::getName()
{
	return name;
}

void aircraft::setPilot(person thePilot)
{
	pilot=thePilot;
}

person aircraft::getPilot()
{
	return pilot;
}

void aircraft::setCoPilot(person theCoPilot)
{
	copilot=theCoPilot;
}

person aircraft::getCoPilot()
{
	return copilot;
}

void aircraft::printDetails()
{
	std::cout << name << std::endl;
	std::cout << pilot.getName() << std::endl;
	std::cout << copilot.getName() << std::endl;
}
