#include <iostream>

#include "states/PlayerOneHighscore.hpp"
#include "communication/Messages.hpp"

/* 
class: PlayerOneHighscore
Implementation of the PlayerOneHighscore State's member functions
*/

PlayerOneHighscore::PlayerOneHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints){
	selectedMap_ = selectedMap;
	playerOnePoints_ = playerOnePoints;
	playerTwoPoints_ = playerTwoPoints;
	this->gameTF = gameTF;
	std::cout << "PlayerOneHighscore: ctor - fire to enter new state" << std::endl;
}

PlayerOneHighscore::~PlayerOneHighscore(){
	std::cout << "PlayerOneHighscore: dtor" << std::endl;
}

void PlayerOneHighscore::fire(){
	if (returning_) {
		std::cout << "PlayerOneHighscore: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	} else if (currentChar < 2){
		currentChar++;
		std::cout << "PlayerOneHighscore: fire - increasing char" << std::endl;
	} else if (currentChar == 2){
		std::cout << "PlayerOneHighscore: fire - last char reached, post highscore and go to either PlayerTwoHighscore or Idle" << std::endl;
		if (playerTwoPoints_ > 0){
			gameTF->setCurrent(new PlayerTwoHighscore(gameTF, selectedMap_, playerTwoPoints_));
			delete this;
		} else {
			gameTF->setCurrent(new Idle(gameTF));
			delete this;
		}
	}
}

void PlayerOneHighscore::up(){
	std::cout << "PlayeroneHighscore: up, cycle currentChar in string here" << std::endl;
}

void PlayerOneHighscore::down(){
	std::cout << "PlayeroneHighscore: down, cycle currentChar in string here" << std::endl;
}