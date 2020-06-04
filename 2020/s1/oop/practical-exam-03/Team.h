#ifndef TEAM_H
#define TEAM_H
#include "Person.h"
#include "Player.h"
#include "Coach.h"
#include <string>

using namespace std;

class Team
{
private:
	Person** team_members;

public:
	Team();
	Person** get_team();
};
#endif //TEAM_H