#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Referee.h"
#include "RandomComputer.h"
#include "Avalanche.h"
#include "Bureaucrat.h"
#include "Toolbox.h"
#include "Crescendo.h"
#include "PaperDoll.h"
#include "FistfullODollars.h"
#include "Tournament.h"

#include <iostream>
#include <array>

using namespace std;

int main(){
	// HumanPlayer Matt;
	ComputerPlayer Comp;
	Referee Ref;
	RandomComputer RanComp;
	Avalanche Av;
	Bureaucrat Bur;
	Toolbox Tool;
	Crescendo Cresc;
	PaperDoll PD;
	FistfullODollars Fist;
	Tournament Tourney;

	int numberofgames=10;
	
	for(int i=0; i < numberofgames; i++){
		std::cout << Ref.refGame(Av,Bur) << " ";
	}

	Avalanche* comp1 = new Avalanche();
	Bureaucrat* comp2 = new Bureaucrat();
	Bureaucrat* comp3 = new Bureaucrat();
	Toolbox* comp4 = new Toolbox();
	Toolbox* comp5 = new Toolbox();
	Crescendo* comp6 = new Crescendo();
	Crescendo* comp7 = new Crescendo();
	FistfullODollars* comp8 = new FistfullODollars();

	array<Player*,8> competitors = {comp1,comp2,comp3,comp4,comp5,comp6,comp7,comp8}; 

	std::cout << comp4 << std::endl;
	std::cout << comp5 << std::endl;

	std::cout << Tourney.run(competitors) << std::endl;

	return 0;
}