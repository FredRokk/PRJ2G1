#include <iostream>

#include "states/Results.hpp"
#include "communication/Messages.hpp"

/* 
class: Results
Implementation of the Results State's member functions
*/

Results::Results(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints){
	selectedMap_ = selectedMap;
	this->gameTF = gameTF;
	playerOnePoints_ = playerOnePoints;
	playerTwoPoints_ = playerTwoPoints;

	menuName_ = "results";

	sendShowInd(gameTF->getPrintMq(), menuName_);

	scoreToBeat_ = 100; //Should be initialized through Gamerules::getScoreToBeat(selectedMap_);
}

Results::~Results(){
	sendCleanInd(gameTF->getPrintMq(), menuName_);
}

void Results::fire(){
	if (returning_) {
		std::cout << "Results: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else {
		if (playerOnePoints_ > scoreToBeat_ && playerTwoPoints_ > scoreToBeat_){
			gameTF->setCurrent(new PlayerOneHighscore(gameTF, selectedMap_, playerOnePoints_, playerTwoPoints_));
			delete this;
		} else if (playerOnePoints_ > scoreToBeat_) {
			gameTF->setCurrent(new PlayerOneHighscore(gameTF, selectedMap_, playerOnePoints_, 0));
			delete this;
		} else if (playerTwoPoints_ > scoreToBeat_) {
			gameTF->setCurrent(new PlayerTwoHighscore(gameTF, selectedMap_, playerTwoPoints_));
			delete this;
		} else {
			gameTF->setCurrent(new Idle(this->gameTF));
			delete this;
		}
	}
}