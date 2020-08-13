#include "Player.h"
#include "Referee.h"
#include "Tournament.h"

#include <array>

Tournament :: Tournament(){}

Player* Tournament :: run(std::array<Player *, 8> competitors){
	Player* round1=round(competitors[0],competitors[1]);
	Player* round2=round(competitors[2],competitors[3]);
	Player* round3=round(competitors[4],competitors[5]);
	Player* round4=round(competitors[6],competitors[7]);

	Player* semifinal1=round(round1,round2);
	Player* semifinal2=round(round3,round4);

	Player* grandfinal = round(semifinal1,semifinal2);

	return grandfinal;
}

Player * Tournament :: round(Player* P1, Player* P2){
	Referee Ref;
	int P1score = 0;
	int P2score = 0;
	char result;

	for(int i=0; i<5; i++){
		result = Ref.refGame(*P1,*P2);

		if(result == 'W'){
			P1score++;
		}else if(result == 'L'){
			P2score++;
		}
	}

	if(P2score > P1score){
		return P2;
	}else{
		return P1;
	}
}