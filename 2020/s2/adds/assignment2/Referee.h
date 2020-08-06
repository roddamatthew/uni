#ifndef REFEREE_H
#define REFEREE_H

#include "HumanPlayer.h"
#include "ComputerPlayer.h"

class Referee
{
public:
	Referee();
	char refGame(HumanPlayer* player1, ComputerPlayer* player2);
};
#endif //REFEREE_H