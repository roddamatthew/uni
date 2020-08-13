#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Player.h"
#include <array>

class Tournament
{
private:
	Player * round(Player* P1, Player* P2);
public:
	Tournament();
	Player * run(std::array<Player *, 8> competitors);
};
#endif //TOURNAMENT_H