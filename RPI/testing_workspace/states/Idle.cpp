#include <iostream>

#include "Idle.hpp"
/* 
class: Idle
Implementation of the Idle State's member functions
*/

Idle::Idle(GameThreadFunctor* gameTF){
	this->gameTF = gameTF;
	std::cout << "Idle: ctor - onePlayer or twoPlayer to enter new state" << std::endl;
}

Idle::~Idle(){
	std::cout << "Idle: dtor" << std::endl;
}

void Idle::left(){
	std::cout << "Idle: left" << std:: endl;
}

void Idle::right(){
	std::cout << "Idle: right" << std:: endl;
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