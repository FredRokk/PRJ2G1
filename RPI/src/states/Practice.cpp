#include <iostream>

#include "states/Practice.hpp"

/* 
class: Practice
Implementation of the Practice State's member functions
*/

Practice::Practice(GameThreadFunctor* gameTF, int selectedMap){
	selectedMap_ = selectedMap;
	this->gameTF = gameTF;

	menuName_ = "practice";
	map_ = Gamerules::generateMap(selectedMap_);

	sendMapInd(gameTF->getCommMq(), map_.getMapString());
	sendShowInd(gameTF->getPrintMq(), menuName_);

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
		sendHitReq(gameTF->getCommMq());

		std::cout << "Practice: fire" << std::endl;
	}
}

void Practice::hit(int field){
	if (field == 0){
		sendMissInd(gameTF->getPrintMq(), menuName_);
		sendUARTCommandInd(gameTF->getCommMq(), '+');
	}
	std::cout << "Practice: hit" << std::endl;
}