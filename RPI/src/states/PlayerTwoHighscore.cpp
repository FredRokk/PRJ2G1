#include <iostream>

#include "states/PlayerTwoHighscore.hpp"
#include "communication/Messages.hpp"
/* 
class: PlayerTwoHighscore
Implementation of the PlayerTwoHighscore State's member functions
*/

PlayerTwoHighscore::PlayerTwoHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerTwoPoints){
	selectedMap_ = selectedMap;
	playerTwoPoints_ = playerTwoPoints;
	this->gameTF = gameTF;

	menuName_ = "playertwohighscore";

	sendShowInd(gameTF->getPrintMq(), menuName_);
}

PlayerTwoHighscore::~PlayerTwoHighscore(){
	sendCleanInd(gameTF->getPrintMq(), menuName_);
}

void PlayerTwoHighscore::fire(){
	if (returning_) {
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	} else if (currentChar_ < 2){
		currentCharIndex_ = 0;
		currentChar_++;
	} else if (currentChar_ == 2){
		std::cout << "Posting highscore with name: " << name_ << ", points = " << playerTwoPoints_ << ", map: " << selectedMap_ << std::endl;
		//Gamerules::PostHighscore(selectedMap_, name_, playerOnePoints);
		gameTF->setCurrent(new Idle(gameTF));
		delete this;
	}
}

void PlayerTwoHighscore::up(){
	cycleCurrentCharIndex(true);
	char newChar = getCharFromList(currentCharIndex_);
	name_.at(currentChar_) = newChar;
	sendHighscoreChangeCharInd(gameTF->getPrintMq(), 1, currentChar_, newChar);
}


void PlayerTwoHighscore::down(){
	cycleCurrentCharIndex(false);
	char newChar = getCharFromList(currentCharIndex_);
	name_.at(currentChar_) = newChar;
	sendHighscoreChangeCharInd(gameTF->getPrintMq(), 1, currentChar_, newChar);
}


void PlayerTwoHighscore::cycleCurrentCharIndex(bool increase){
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

char PlayerTwoHighscore::getCharFromList(int index){
	return charList_.at(index);
}