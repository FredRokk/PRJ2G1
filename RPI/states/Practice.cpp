#include <iostream>

#include "Practice.hpp"

/* 
class: Practice
Implementation of the Practice State's member functions
*/

Practice::Practice(GameThreadFunctor* gameTF, int selectedMap){
	selectedMap_ = selectedMap;
	this->gameTF = gameTF;
	std::cout << "Practice: ctor - fire to enter new state" << std::endl;
}

Practice::~Practice(){
	std::cout << "Practice: dtor" << std::endl;
}

void Practice::fire(){
	if (returning_) {
		std::cout << "Practice: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else {
		std::cout << "Practice: fire" << std::endl;
	}
}

void Practice::hit(int field){
	std::cout << "Practice: hit" << std::endl;
}