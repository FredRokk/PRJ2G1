#include <iostream>

#include "states/Results.hpp"
#include "communication/Messages.hpp"

/* 
class: Results
Implementation of the Results State's member functions
*/

Results::Results(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints){
	selectedMap_ = selectedMap;
	playerOnePoints_ = playerOnePoints;
	playerTwoPoints_ = playerTwoPoints;
	this->gameTF = gameTF;
	//Init score to beat here
	std::cout << "Results: ctor - fire to enter new state" << std::endl;
}

Results::~Results(){
	std::cout << "Results: dtor" << std::endl;
}

void Results::fire(){
	if (returning_) {
		std::cout << "Results: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else {
		std::cout << "Results: fire" << std::endl;
		if (playerOnePoints_ > scoreToBeat_ && playerTwoPoints_ > scoreToBeat_){
			std::cout << "Both players made a highscore, going to PlayerOneHighscore, sending playerTwoPoints along" << std::endl;
			gameTF->setCurrent(new PlayerOneHighscore(gameTF, selectedMap_, playerOnePoints_, playerTwoPoints_));
			delete this;
		} else if (playerOnePoints_ > scoreToBeat_) {
			std::cout << "Player one made a highscore, going to PlayerOneHighscore, sending 0 as playerTwoPoints" << std::endl;
			gameTF->setCurrent(new PlayerOneHighscore(gameTF, selectedMap_, playerOnePoints_, 0));
			delete this;
		} else if (playerTwoPoints_ > scoreToBeat_) {
			std::cout << "Player two made a highscore, going to PlayerTwoHighscore" << std::endl;
			gameTF->setCurrent(new PlayerTwoHighscore(gameTF, selectedMap_, playerTwoPoints_));
			delete this;
		} else {
			std::cout << "Noone made a highscore, returning to idle" << std::endl;
			gameTF->setCurrent(new Idle(this->gameTF));
			delete this;
		}
	}
}