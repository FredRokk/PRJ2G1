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
}

PlayerOneHighscore::~PlayerOneHighscore(){
	sendCleanInd(gameTF->getPrintMq(), menuName_);
}

void PlayerOneHighscore::fire(){
	if (returning_) {
		if (playerTwoPoints_ > 0){
			gameTF->setCurrent(new PlayerTwoHighscore(gameTF, selectedMap_, playerTwoPoints_));
			delete this;
		} else {
			gameTF->setCurrent(new Idle(gameTF));
			delete this;
		}
	} else if (currentChar_ < 2){
		currentCharIndex_ = 0;
		currentChar_++;
	} else if (currentChar_ == 2){
		std::cout << "Posting highscore with name: " << name_ << ", points = " << playerOnePoints_ << ", selectedMap_ = " << selectedMap_ << std::endl;
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
	cycleCurrentCharIndex(true);
	char newChar = getCharFromList(currentCharIndex_);
	name_.at(currentChar_) = newChar;
	sendHighscoreChangeCharInd(gameTF->getPrintMq(), 1, currentChar_, newChar);

}

void PlayerOneHighscore::down(){
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

	if (currentCharIndex_ > (int)charList_.length()-1){
		currentCharIndex_ = 0;
	} else if (currentCharIndex_ < 0) {
		currentCharIndex_ = charList_.length()-1;
	}
}

char PlayerOneHighscore::getCharFromList(int index){
	return charList_.at(index);
}