#include <iostream>
#include "person.h"
#include "aircraft.h"	

using namespace std;


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

aircraft::aircraft(string callsign, person thePilot,person theCoPilot)
{
	person *pilot, *copilot;

	name=callsign;
	pilot= new person("John",100);
	copilot= new person("Jim",200);

	setPilot(thePilot);
	setCoPilot(theCoPilot);
}

void aircraft::printDetails()
{
	std::cout << name << std::endl;
	std::cout << getPilot().getName() << std::endl;
	std::cout << getCoPilot().getName() << std::endl;
}
