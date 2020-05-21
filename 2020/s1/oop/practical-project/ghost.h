#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include "entity.h"

using namespace std;

class Ghost: public Entity
{

// has state inherited from Entity superclass:
// int row;
// int column;

private:
	void pathing(int rowtarget, int columntarget); //Moves the ghost towards a target position
	char lastDirection;	//Stores the last direction moved in

public:
	Ghost();
	// virtual void chase();
	// virtual void scatter();
	void scared(int rowtarget, int columntarget); //Moves the ghost away from pacman
	void eaten(); //Moves the ghost towards the centre of the map.

};
#endif //GHOST_H