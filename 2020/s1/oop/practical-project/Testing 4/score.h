#ifndef SCORE_H
#define SCORE_H

#include <iostream>

using namespace std;

class Score
{
private:
	int score;

public:
	Score();
	Score(int currentScore);
	void pellet();
	void ghost();
	int getScore();
	void printScore();
};
#endif //SCORE_H