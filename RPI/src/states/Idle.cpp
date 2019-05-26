#include <iostream>

#include "states/Idle.hpp"
/* 
class: Idle
Implementation of the Idle State's member functions
*/

Idle::Idle(GameThreadFunctor* gameTF){
	this->gameTF = gameTF;
	menuName_ = "idle1";

	std::cout << "Idle: ctor - onePlayer or twoPlayer to enter new state" << std::endl;
}

Idle::~Idle(){
	std::cout << "Idle: dtor" << std::endl;
}

void Idle::left(){
	std::cout << "Idle: left" << std:: endl;
	changeIdle(false);
	menuName_.at(5) = currentIdle_ + 48; //string.at int to character conversion
	sendShowInd(gameTF->getPrintMq(), menuName_);
}

void Idle::right(){
	std::cout << "Idle: right" << std:: endl;
	changeIdle(true);
	menuName_.at(5) = currentIdle_ + 48; //string.at int to character conversion
	sendShowInd(gameTF->getPrintMq(), menuName_);
}

void Idle::onePlayer(){
	std::cout << "Idle: onePlayer, entering MapSelect with players = 1" << std::endl;
	gameTF->setCurrent(new MapSelect(this->gameTF, false));
	delete this;
}

void Idle::twoPlayer(){
	std::cout << "Idle: twoPlayer, entering MapSelect with players = 2" << std::endl;
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