#include "Person.h"
#include "Player.h"
#include <string>

using namespace std;

int Player::nextID = 1000;

Player::Player(string n, int sl, int *list, int m){
	name = n;
	occupation = "player";
	serviceLength = sl;
	personID = nextID;
	nextID++;
	games = m;
	gametime = new int[games];


	for(int i=0; i<m; i++){
		gametime[i] = list[i];
	}

}

int Player::get_salary(){
	if(serviceLength<20){
		return salary;
	}else{
		return 3*salary;
	}
}

int Player::searchGame(int x){
	for(int i=0; i<games; i++){
		if(gametime[i] == x){
			return i;
		}
	}
	return -1;
}