#include <iostream>

#include "states/PlayerOneHighscore.hpp"

/* 
class: PlayerOneHighscore
Implementation of the PlayerOneHighscore State's member functions
*/

PlayerOneHighscore::PlayerOneHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints){
	this->gameTF = gameTF;
	selectedMap_ = selectedMap;
	playerOnePoints_ = playerOnePoints;
	playerTwoPoints_ = playerTwoPoints;

	menuName_ = "playeronehighscore";

	sendShowInd(gameTF->getPrintMq(), menuName_);

	std::cout << "PlayerOneHighscore: ctor - fire to enter new state" << std::endl;
}

PlayerOneHighscore::~PlayerOneHighscore(){
	std::cout << "PlayerOneHighscore: dtor" << std::endl;
	sendCleanInd(gameTF->getPrintMq(), menuName_);
}

void PlayerOneHighscore::fire(){
	if (returning_) {
		std::cout << "PlayerOneHighscore: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	} else if (currentChar_ < 2){
		currentChar_++;
		std::cout << "PlayerOneHighscore: fire - increasing char" << std::endl;
	} else if (currentChar_ == 2){
		std::cout << "PlayerOneHighscore: fire - last char reached, post highscore and go to either PlayerTwoHighscore or Idle" << std::endl;
		//Gamerules::PostHighscore(selectedMap_, name_, playerOnePoints);
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
	std::cout << "PlayeroneHighscore: up, cycle currentChar_ in string here" << std::endl;
	cycleCurrentCharIndex(true);
	char newChar = getCharFromList(currentCharIndex_);
	name_.at(currentChar_) = newChar;
	sendHighscoreChangeCharInd(gameTF->getPrintMq(), 1, currentChar_, newChar);

}

void PlayerOneHighscore::down(){
	std::cout << "PlayeroneHighscore: down, cycle currentChar_ in string here" << std::endl;
	cycleCurrentCharIndex(false);
	char newChar = getCharFromList(currentCharIndex_);
	name_.at(currentChar_) = newChar;
	sendHighscoreChangeCharInd(gameTF->getPrintMq(), 1, currentChar_, newChar);
}

void PlayerOneHighscore::cycleCurrentCharIndex(bool increase){
	if (increase){
		currentCharIndex_++;
	} else {
		currentCharIndex_--;
	}

	if (currentCharIndex_ > (int)charList_.length()){
		currentCharIndex_ = 0;
	} else if (currentCharIndex_ < 0) {
		currentCharIndex_ = charList_.length();
	}
}

char PlayerOneHighscore::getCharFromList(int index){
	return charList_.at(index);
}