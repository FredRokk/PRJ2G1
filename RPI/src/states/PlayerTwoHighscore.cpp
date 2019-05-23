#include <iostream>

#include "states/PlayerTwoHighscore.hpp"

/* 
class: PlayerTwoHighscore
Implementation of the PlayerTwoHighscore State's member functions
*/

PlayerTwoHighscore::PlayerTwoHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerTwoPoints){
	selectedMap_ = selectedMap;
	playerTwoPoints_ = playerTwoPoints;
	this->gameTF = gameTF;
	std::cout << "PlayerTwoHighscore: ctor - fire to enter new state" << std::endl;
}

PlayerTwoHighscore::~PlayerTwoHighscore(){
	std::cout << "PlayerTwoHighscore: dtor" << std::endl;
}

void PlayerTwoHighscore::fire(){
	if (returning_) {
		std::cout << "PlayerTwoHighscore: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	} else if (currentChar < 2){
		currentChar++;
		std::cout << "PlayerTwoHighscore: fire - increasing char" << std::endl;
	} else if (currentChar == 2){
		std::cout << "PlayerTwoHighscore: fire - last char reached, post highscore and go to either PlayerTwoHighscore or Idle" << std::endl;
		gameTF->setCurrent(new Idle(gameTF));
		delete this;
	}
}

void PlayerTwoHighscore::up(){
	std::cout << "PlayerTwoHighscore: up, cycle currentChar in string here" << std::endl;
}


void PlayerTwoHighscore::down(){
	std::cout << "PlayerTwoHighscore: down, cycle currentChar in string here" << std::endl;
}