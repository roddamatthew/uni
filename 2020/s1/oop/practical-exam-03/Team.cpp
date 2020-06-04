#include "Person.h"
#include "Player.h"
#include "Coach.h"
#include "Team.h"
#include <string>

Team::Team(){
	int list[4] = {0,1,2,3};

	team_members = new Person*[5];
	team_members[0] = new Coach("C1",0);
	team_members[1] = new Player("P1", 0, list, 4);
	team_members[3] = new Player("P2", 0, list, 4);
	team_members[3] = new Player("P3", 0, list, 4);
	team_members[4] = new Coach("C2",0);
}

Person** Team::get_team(){
	return team_members;
}