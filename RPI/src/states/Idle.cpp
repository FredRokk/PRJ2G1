#include <iostream>

#include "states/Idle.hpp"
/* 
class: Idle
Implementation of the Idle State's member functions
*/

Idle::Idle(GameThreadFunctor* gameTF){
	this->gameTF = gameTF;
	menuName_ = "idle1";
	sendShowInd(gameTF->getPrintMq(), menuName_);
}

Idle::~Idle(){
	sendCleanInd(gameTF->getPrintMq(), menuName_);
}

void Idle::left(){
	changeIdle(false);
	menuName_.at(4) = currentIdle_ + 48; //string.at int to character conversion
	sendShowInd(gameTF->getPrintMq(), menuName_);
}

void Idle::right(){
	changeIdle(true);
	menuName_.at(4) = currentIdle_ + 48; //string.at int to character conversion
	sendShowInd(gameTF->getPrintMq(), menuName_);
}

void Idle::onePlayer(){
	gameTF->setCurrent(new MapSelect(this->gameTF, false));
	delete this;
}

void Idle::twoPlayer(){
	gameTF->setCurrent(new MapSelect(this->gameTF, true));
	delete this;
}

void Idle::changeIdle(bool increase){
	if(increase){
		currentIdle_++;
	} else {
		currentIdle_--;
	}

	if (currentIdle_ < 1) currentIdle_ = NUMBER_OF_DEFAULT_MAPS + 1;
	else if (currentIdle_ > NUMBER_OF_DEFAULT_MAPS + 1) currentIdle_ = 1;
}