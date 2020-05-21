#include <iostream>
#include "score.h"

using namespace std;


	Score::Score(){
		score = 0;
	}

	Score::Score(int currentScore){
		score = currentScore;
	}

	void Score::pellet(){
		score = score + 10;
	}

	void Score::ghost(){
		score = score + 200;
	}

	int Score::getScore(){
		return score;
	}

	void Score::printScore(){
		std::cout << "Score: " << score << std::endl;
	}