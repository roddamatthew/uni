#include "Player.h"
#include "RandomComputer.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

RandomComputer :: RandomComputer(){
	srand((unsigned int)time(NULL));

	for(int i=0; i<10; i++){
		int random=rand()%3;
		if(random < 1){
			moves.push_back('R');
		}else if(random < 2){
			moves.push_back('P');
		}else if(random < 3){
			moves.push_back('S');
		}
	}

	std::cout << "RandComp's moves are: ";
	for(int i=0; i<10; i++){
		std::cout << moves[i] << " ";
	}
	std::cout << std::endl;
}