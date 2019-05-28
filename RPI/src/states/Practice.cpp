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
}

Practice::~Practice(){
}

void Practice::fire(){
	if (returning_) {
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else {
		sendHitReq(gameTF->getCommMq());
	}
}

void Practice::hit(int field){
	if (field == 0){
		sendMissInd(gameTF->getPrintMq(), menuName_);
	}
	sendUARTCommandInd(gameTF->getCommMq(), '+');
}